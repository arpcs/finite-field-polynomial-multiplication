param(
 [Parameter(Mandatory=$true)][string]$TectonicPath,
 [Parameter(Mandatory=$true)][string]$GuardPath,
 [Parameter(Mandatory=$true)][string]$CacheDirectory,
 [ValidateRange(0,300)][int]$WaitForGuardSeconds=0
)
$ErrorActionPreference='Stop'
$root=[IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..')).TrimEnd([IO.Path]::DirectorySeparatorChar)
$build=Join-Path $root 'build'
New-Item -ItemType Directory -Path $build -Force|Out-Null
$engine=(Resolve-Path -LiteralPath $TectonicPath).Path
$guard=(Resolve-Path -LiteralPath $GuardPath).Path
$env:TECTONIC_CACHE_DIR=(Resolve-Path -LiteralPath $CacheDirectory).Path
$env:RAYON_NUM_THREADS='1'
function SourceHashes {
 @(Get-ChildItem -LiteralPath $root -File -Filter '*.tex'; Get-ChildItem -LiteralPath (Join-Path $root 'appendices') -File -Filter '*.tex')|
 Sort-Object FullName|ForEach-Object {[pscustomobject]@{
  path=[IO.Path]::GetRelativePath($root,$_.FullName).Replace([char]92,[char]47)
  sha256=(Get-FileHash -LiteralPath $_.FullName).Hash
 }}
}
$before=@(SourceHashes)
$source=Join-Path $root 'main.tex'
$argsForEngine=@('--untrusted','--only-cached','--keep-logs','--keep-intermediates','--reruns','2','--outdir',$build,$source)
$deadline=[DateTime]::UtcNow.AddSeconds($WaitForGuardSeconds)
$attempts=0
Push-Location -LiteralPath $root
try {
 do {
  $attempts++
  & $guard $engine @argsForEngine 1>(Join-Path $build 'compiler.stdout.txt') 2>(Join-Path $build 'compiler.stderr.txt')
  $code=$LASTEXITCODE
  if($code -ne 75 -or [DateTime]::UtcNow -ge $deadline){break}
  Start-Sleep -Milliseconds 500
 }while($true)
}finally{Pop-Location}
if($code -eq 75){throw 'Shared document guard is busy; no compiler was started'}
if($code -ne 0){throw ('Document compilation failed; inspect the local build directory, exit '+$code)}
$after=@(SourceHashes)
if(($before|ConvertTo-Json -Compress) -ne ($after|ConvertTo-Json -Compress)){throw 'Sources changed during compilation'}
$pdf=Join-Path $root 'paper.pdf'
Copy-Item -LiteralPath (Join-Path $build 'main.pdf') -Destination $pdf -Force
$log=[IO.File]::ReadAllText((Join-Path $build 'main.log'))
$guardLog=[IO.File]::ReadAllText((Join-Path $build 'compiler.stderr.txt'))
$peak=[regex]::Match($guardLog,'peak_job_bytes=(\d+)')
$receipt=[pscustomobject]@{
 version='0.2.1';date='2026-11-02';exit=$code;compiler='Tectonic 0.17.0'
 source_files=$after;pdf='paper.pdf';pdf_sha256=(Get-FileHash -LiteralPath $pdf).Hash
 engine_sha256=(Get-FileHash -LiteralPath $engine).Hash;guard_sha256=(Get-FileHash -LiteralPath $guard).Hash
 untrusted=$true;offline_only_cached=$true;threads=1;memory_mib=512;cpu_seconds=60;wall_seconds=120
 peak_job_bytes=$(if($peak.Success){[long]$peak.Groups[1].Value}else{$null});guard_attempts=$attempts
 overfull_boxes=[regex]::Matches($log,'Overfull \\[hv]box').Count
 undefined_references=[regex]::Matches($log,'(?:Reference|Citation) .+ undefined|There were undefined references').Count
 mathematical_correctness_certified=$false
}
$receipt|ConvertTo-Json -Depth 6|Set-Content -LiteralPath (Join-Path $root 'verification/build.json') -Encoding utf8
$receipt|Select-Object version,exit,overfull_boxes,undefined_references,peak_job_bytes,pdf_sha256|ConvertTo-Json
