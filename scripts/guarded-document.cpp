#define NOMINMAX
#include <windows.h>
#include <filesystem>
#include <iostream>
#include <string>

static std::wstring quote(const std::wstring& s) {
  std::wstring out = L"\"";
  size_t slashes = 0;
  for (wchar_t c : s) {
    if (c == L'\\') { ++slashes; continue; }
    if (c == L'\"') { out.append(2*slashes+1,L'\\'); out += c; slashes=0; continue; }
    out.append(slashes,L'\\'); slashes=0; out += c;
  }
  out.append(2*slashes,L'\\'); out += L'\"';
  return out;
}

// Bounded document compilation, including all children, with a hard aggregate cap.
// This document guard uses 512 MiB, 60 CPU seconds and 120 wall seconds.
// Numerical witnesses and Lean checks use their own separate guards.
int wmain(int argc, wchar_t** argv) {
  if (argc < 2) { std::wcerr << L"Usage: guarded-document.exe executable [arguments...]\n"; return 2; }
  const auto exe = std::filesystem::absolute(argv[1]);
  if (!std::filesystem::is_regular_file(exe)) { std::wcerr << L"Missing executable\n"; return 2; }
  HANDLE mutex = CreateMutexW(nullptr,FALSE,L"Local\\FastMulLeanVerification20261030");
  if (!mutex) return 2;
  const DWORD acquired = WaitForSingleObject(mutex,0);
  if (acquired != WAIT_OBJECT_0 && acquired != WAIT_ABANDONED) {
    CloseHandle(mutex); std::wcerr << L"BUSY: another guarded check is active\n"; return 75;
  }
  auto unlock = [&]() { ReleaseMutex(mutex); CloseHandle(mutex); };
  HANDLE job = CreateJobObjectW(nullptr,nullptr);
  if (!job) { unlock(); return 2; }
  JOBOBJECT_EXTENDED_LIMIT_INFORMATION limits{};
  limits.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_ACTIVE_PROCESS |
    JOB_OBJECT_LIMIT_PROCESS_MEMORY | JOB_OBJECT_LIMIT_JOB_MEMORY |
    JOB_OBJECT_LIMIT_JOB_TIME | JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;
  limits.BasicLimitInformation.ActiveProcessLimit = 8;
  limits.BasicLimitInformation.PerJobUserTimeLimit.QuadPart = 60LL*10000000;
  limits.ProcessMemoryLimit = 512ull*1024*1024;
  limits.JobMemoryLimit = 512ull*1024*1024;
  if (!SetInformationJobObject(job,JobObjectExtendedLimitInformation,&limits,sizeof(limits))) {
    std::wcerr << L"REFUSE: unable to apply job limits\n";
    CloseHandle(job); unlock(); return 2;
  }
  if (!SetEnvironmentVariableW(L"LEAN_NUM_THREADS",L"1")) {
    CloseHandle(job); unlock(); return 2;
  }
  std::wstring command = quote(exe.native());
  for (int i=2; i<argc; ++i) command += L" " + quote(argv[i]);
  STARTUPINFOW si{}; si.cb=sizeof(si);
  PROCESS_INFORMATION pi{};
  if (!CreateProcessW(exe.c_str(),command.data(),nullptr,nullptr,FALSE,
      CREATE_SUSPENDED,nullptr,nullptr,&si,&pi)) {
    std::wcerr << L"REFUSE: process creation failed " << GetLastError() << L"\n";
    CloseHandle(job); unlock(); return 2;
  }
  if (!AssignProcessToJobObject(job,pi.hProcess)) {
    std::wcerr << L"REFUSE: suspended process could not enter job\n";
    TerminateProcess(pi.hProcess,125); WaitForSingleObject(pi.hProcess,2000);
    CloseHandle(pi.hThread); CloseHandle(pi.hProcess); CloseHandle(job); unlock(); return 2;
  }
  if (ResumeThread(pi.hThread)==static_cast<DWORD>(-1)) {
    TerminateJobObject(job,125); WaitForSingleObject(pi.hProcess,2000);
    CloseHandle(pi.hThread); CloseHandle(pi.hProcess); CloseHandle(job); unlock(); return 2;
  }
  const DWORD waited=WaitForSingleObject(pi.hProcess,120000);
  DWORD code=125;
  if (waited==WAIT_OBJECT_0) GetExitCodeProcess(pi.hProcess,&code);
  else {
    code=waited==WAIT_TIMEOUT ? 124 : 125;
    TerminateJobObject(job,code); WaitForSingleObject(pi.hProcess,2000);
    std::wcerr << L"Guard stopped process: timeout or wait failure\n";
  }
  JOBOBJECT_EXTENDED_LIMIT_INFORMATION used{};
  if (QueryInformationJobObject(job,JobObjectExtendedLimitInformation,&used,sizeof(used),nullptr)) {
    std::wcerr << L"[guard] exit=" << code
      << L" peak_process_bytes=" << used.PeakProcessMemoryUsed
      << L" peak_job_bytes=" << used.PeakJobMemoryUsed << L"\n";
  }
  CloseHandle(pi.hThread); CloseHandle(pi.hProcess); CloseHandle(job); unlock();
  return static_cast<int>(code);
}
