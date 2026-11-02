#ifndef FASTMUL_BOUNDED_CHIRP_PROCESS_LIMITS_HPP
#define FASTMUL_BOUNDED_CHIRP_PROCESS_LIMITS_HPP
// Apply limits to THIS process before algebra. Never touches other processes.
#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
inline bool install_chirp_process_limits(){
 static HANDLE retained_job=nullptr;
 if(retained_job)return true;
 HANDLE job=CreateJobObjectW(nullptr,nullptr);if(!job)return false;
 JOBOBJECT_EXTENDED_LIMIT_INFORMATION info{};
 info.BasicLimitInformation.LimitFlags=JOB_OBJECT_LIMIT_PROCESS_MEMORY|JOB_OBJECT_LIMIT_PROCESS_TIME;
 info.ProcessMemoryLimit=64u*1024u*1024u;
 info.BasicLimitInformation.PerProcessUserTimeLimit.QuadPart=10ll*10000000ll;
 if(!SetInformationJobObject(job,JobObjectExtendedLimitInformation,&info,sizeof(info))
    ||!AssignProcessToJobObject(job,GetCurrentProcess())){CloseHandle(job);return false;}
 retained_job=job;return true;
}
#else
inline bool install_chirp_process_limits(){return false;}
#endif
#endif
