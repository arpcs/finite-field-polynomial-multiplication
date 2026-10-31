#requires -Version 7.0
param(
  [switch]$Replay,
  [string]$Compiler='g++',
  [string]$CompilerGuard=''
)
$ErrorActionPreference='Stop'
$unit=[IO.Path]::GetFullPath($PSScriptRoot)
$manifestPath=Join-Path $unit 'ARTIFACTS.json'
$manifest=Get-Content -LiteralPath $manifestPath -Raw | ConvertFrom-Json
if ($manifest.schema -ne 'finite-unit-artifacts/1') { throw 'Unsupported finite-unit manifest' }
$verified=[Collections.Generic.List[object]]::new()
foreach ($file in $manifest.files) {
  if ($file.path -notmatch '^[A-Za-z0-9_./-]+$' -or $file.path -match '(^|/)\.\.?(/|$)') {
    throw 'Invalid artifact-relative path'
  }
  $path=Join-Path $unit $file.path
  $item=Get-Item -LiteralPath $path
  $hash=(Get-FileHash -LiteralPath $path -Algorithm SHA256).Hash.ToLowerInvariant()
  if ($item.Length -ne $file.bytes -or $hash -cne $file.sha256) {
    throw ('Artifact differs from its reviewed manifest: '+$file.path)
  }
  $verified.Add([ordered]@{path=$file.path;bytes=$item.Length;sha256=$hash})
}
Write-Output ('Verified '+$verified.Count+' finite-unit artifact hashes')
if (-not $Replay) { return }
if (-not $IsWindows) { throw 'The checkers require Windows hard resource limits' }
if (-not $CompilerGuard) { throw 'Replay requires -CompilerGuard for bounded compilation' }
$compilerCommand=Get-Command $Compiler -CommandType Application -ErrorAction Stop | Select-Object -First 1
$compilerPath=$compilerCommand.Source
$guardPath=(Resolve-Path -LiteralPath $CompilerGuard).Path
$compilerName=[IO.Path]::GetFileName($compilerPath)
$guardName=[IO.Path]::GetFileName($guardPath)
$build=Join-Path $unit 'build'
New-Item -ItemType Directory -Force -Path $build | Out-Null
# Invalidate the previous success receipt before starting a new replay.
$receiptPath=Join-Path $build 'replay-receipt.json'
if (Test-Path -LiteralPath $receiptPath) { Remove-Item -LiteralPath $receiptPath }
$commands=[Collections.Generic.List[object]]::new()
$runs=[Collections.Generic.List[object]]::new()
$outputs=@{}

function Invoke-FiniteCheck([string]$Name,[string[]]$InputPaths) {
  $exe=Join-Path $unit ('build/'+$Name+'.exe')
  $info=[Diagnostics.ProcessStartInfo]::new()
  $info.FileName=$exe
  $info.WorkingDirectory=$unit
  $info.UseShellExecute=$false
  $info.CreateNoWindow=$true
  $info.RedirectStandardOutput=$true
  $info.RedirectStandardError=$true
  foreach ($argument in $InputPaths) { $info.ArgumentList.Add($argument) }
  $process=[Diagnostics.Process]::new()
  $process.StartInfo=$info
  try {
    if (-not $process.Start()) { throw ('Could not start '+$Name) }
    $stdoutTask=$process.StandardOutput.ReadToEndAsync()
    $stderrTask=$process.StandardError.ReadToEndAsync()
    if (-not $process.WaitForExit(30000)) {
      # This exact process was created here. The checker creates no child processes.
      $process.Kill($true)
      $process.WaitForExit()
      throw ($Name+' exceeded the 30-second wall limit')
    }
    $stdout=$stdoutTask.GetAwaiter().GetResult()
    $stderr=$stderrTask.GetAwaiter().GetResult()
    [IO.File]::WriteAllText((Join-Path $build ($Name+'.stdout.txt')),$stdout,[Text.UTF8Encoding]::new($false))
    [IO.File]::WriteAllText((Join-Path $build ($Name+'.stderr.txt')),$stderr,[Text.UTF8Encoding]::new($false))
    if ($process.ExitCode -ne 0 -or $stderr.Length) {
      throw ($Name+' failed or refused its limits; exit '+$process.ExitCode+'; see build logs')
    }
    $expectedPath=Join-Path $unit ('historical/'+$Name+'.txt')
    $expected=[IO.File]::ReadAllText($expectedPath)
    $normalized=$stdout.Replace("`r`n","`n").TrimEnd("`r","`n")
    $expected=$expected.Replace("`r`n","`n").TrimEnd("`r","`n")
    if ($normalized -cne $expected) { throw ($Name+' output differs from the historical exact-check receipt') }
    return $normalized
  } finally { $process.Dispose() }
}

$targets=@(
  @{name='native-scalar';source='native_scalar_record_probe.cpp';inputs=@('inputs/native-word.json')},
  @{name='controller';source='controller_record_probe.cpp';inputs=@('inputs/controller.json','inputs/native-word.json')},
  @{name='rate';source='record_rate_probe.cpp';inputs=@()}
)
Push-Location -LiteralPath $unit
try {
  & $guardPath $compilerPath '--version' *> (Join-Path $build 'compiler-version.txt')
  if ($LASTEXITCODE -ne 0) { throw 'Guarded compiler identification failed' }
  $version=(Get-Content -LiteralPath (Join-Path $build 'compiler-version.txt') -TotalCount 1)
  if ($version -match '(?i)([A-Z]:[\\/]|/Users/|/home/|@)') { throw 'Compiler identification contains a personal path or address' }
  foreach ($target in $targets) {
    $arguments=@('-std=c++17','-O2','-Wall','-Wextra','-pedantic',('code/'+$target.source),'-lgmp','-lpsapi','-o',('build/'+$target.name+'.exe'))
    & $guardPath $compilerPath @arguments *> (Join-Path $build ($target.name+'.compiler.log'))
    $compileExit=$LASTEXITCODE
    if ($compileExit -ne 0) { throw ('Guarded compilation failed: '+$target.name+'; exit '+$compileExit) }
    $commands.Add([ordered]@{kind='compile';program=$guardName;arguments=@($compilerName)+$arguments;exit=0})
    $output=Invoke-FiniteCheck $target.name $target.inputs
    $outputs[$target.name]=$output
    $commands.Add([ordered]@{kind='replay';program=('build/'+$target.name+'.exe');arguments=@($target.inputs);exit=0})
    $runs.Add([ordered]@{
      name=$target.name;exit=0;historical_output_match=$true;
      stdout=('build/'+$target.name+'.stdout.txt');
      stdout_sha256=(Get-FileHash -LiteralPath (Join-Path $build ($target.name+'.stdout.txt')) -Algorithm SHA256).Hash.ToLowerInvariant()
    })
    Write-Output ('PASS: '+$target.name)
  }
} finally { Pop-Location }

$sourceInvoice=Get-Content -LiteralPath (Join-Path $unit 'inputs/frontier6030-result.json') -Raw | ConvertFrom-Json
foreach ($pair in @(@('paid','paid_invoice'),@('targets','target_invoice'))) {
  $bins=$sourceInvoice.complete_cost.($pair[0])
  $line=$pair[1]+'='+(($bins.PSObject.Properties | Sort-Object {[int]$_.Name} | ForEach-Object { "$($_.Name):$($_.Value)" }) -join ',')
  if (@($outputs['rate'].Split("`n")) -cnotcontains $line) { throw ('Public RESULT bin mismatch: '+$pair[0]) }
}
$receipt=[ordered]@{
  schema='finite-unit-replay/1';completed_utc=[DateTime]::UtcNow.ToString('o');
  result='pass';scope='Fixed scalar endpoint, Laurent controller, direct geometry and exact invoice/moment checks only; not an end-to-end asymptotic multiplier or Lean proof';
  manifest_sha256=(Get-FileHash -LiteralPath $manifestPath -Algorithm SHA256).Hash.ToLowerInvariant();
  compiler=[ordered]@{name=$compilerName;version=$version;guard=$guardName};
  limits=[ordered]@{checker_process_memory_mib=64;checker_cpu_seconds=10;checker_wall_seconds=30;compiler_guard_required=$true;compiler_jobs_serialized=$true};
  command_paths='Relative to this finite-unit directory; tool locations omitted';
  commands=$commands.ToArray();runs=$runs.ToArray();public_result_bins_match=$true;files=$verified.ToArray()
}
$receipt | ConvertTo-Json -Depth 10 | Set-Content -LiteralPath $receiptPath -Encoding utf8
Write-Output 'PASS: all three fixed finite checks and public invoice bins; receipt build/replay-receipt.json'
