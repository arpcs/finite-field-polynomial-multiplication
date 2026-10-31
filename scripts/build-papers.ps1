param(
  [string]$TectonicPath=$env:CODEX_TECTONIC_PATH,
  [string]$CacheDirectory='',
  [Parameter(Mandatory=$true)][string]$GuardPath,
  [switch]$OnlyCached,
  [string[]]$TargetDirectories=@()
)
$ErrorActionPreference='Stop'
$root=[IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..'))
if (-not $TectonicPath) { $TectonicPath=(Get-Command tectonic -ErrorAction Stop).Source }
$TectonicPath=(Resolve-Path -LiteralPath $TectonicPath).Path
$GuardPath=(Resolve-Path -LiteralPath $GuardPath).Path
if ($CacheDirectory) {
  $env:TECTONIC_CACHE_DIR=(Resolve-Path -LiteralPath $CacheDirectory).Path
}
$env:RAYON_NUM_THREADS='1'
$builds=[Collections.Generic.List[object]]::new()
$receiptPath=Join-Path $root 'verification/paper-builds.json'
if (Test-Path -LiteralPath $receiptPath) {
  foreach ($old in @(Get-Content -LiteralPath $receiptPath -Raw | ConvertFrom-Json)) { $builds.Add($old) }
}
$targets=@(Get-Content -LiteralPath (Join-Path $root 'verification/paper-targets.json') -Raw | ConvertFrom-Json)
if ($TargetDirectories.Count) { $targets=$TargetDirectories }
foreach ($target in $targets) {
  if ($target -notmatch '^(papers|research-notes)/[a-z0-9/-]+$') { throw 'Invalid document target' }
  $paper=Join-Path $root $target
  $build=Join-Path $root ('.build/'+$target)
  New-Item -ItemType Directory -Force -Path $build | Out-Null
  $log=Join-Path $build 'compiler.stdout.log'
  $arguments=@('--untrusted','--keep-logs','--keep-intermediates','--reruns','2','--outdir',$build)
  if ($OnlyCached) { $arguments+='--only-cached' }
  $arguments+=(Join-Path $paper 'main.tex')
  Push-Location -LiteralPath $paper
  try {
    $result=75
    for ($attempt=0; $attempt -lt 120 -and $result -eq 75; $attempt++) {
      & $GuardPath $TectonicPath @arguments *> $log
      $result=$LASTEXITCODE
      if ($result -eq 75) { Start-Sleep -Milliseconds 500 }
    }
  } finally { Pop-Location }
  if ($result -ne 0) {
    Get-Content -LiteralPath $log -Tail 18
    throw ('Paper build failed: '+$target+'; exit '+$result)
  }
  $builtPdf=Join-Path $build 'main.pdf'
  Copy-Item -LiteralPath $builtPdf -Destination (Join-Path $paper 'paper.pdf') -Force
  $sourceFiles=@(Get-ChildItem -LiteralPath $paper -Recurse -File | Where-Object Extension -in @('.tex','.bib','.sty','.cls'))
  $extraFiles=@(foreach ($tex in @($sourceFiles | Where-Object Extension -eq '.tex')) {
    $body=[IO.File]::ReadAllText($tex.FullName)
    foreach ($match in [regex]::Matches($body,'\\VerbatimInput(?:\[[^\]]*\])?\{([^}]+)\}')) {
      $asset=[IO.Path]::GetFullPath((Join-Path $paper $match.Groups[1].Value))
      if (-not $asset.StartsWith($paper+[IO.Path]::DirectorySeparatorChar,[StringComparison]::OrdinalIgnoreCase)) { throw 'Document asset escapes paper directory' }
      Get-Item -LiteralPath $asset
    }
  })
  $dependencies=@(@($sourceFiles)+@($extraFiles) | Sort-Object FullName -Unique | ForEach-Object {
    [pscustomobject]@{path=$_.FullName.Substring($root.Length+1).Replace('\','/');sha256=(Get-FileHash -LiteralPath $_.FullName -Algorithm SHA256).Hash.ToLowerInvariant()}
  })
  for ($index=$builds.Count-1; $index -ge 0; $index--) {
    if ($builds[$index].paper -eq $target) { $builds.RemoveAt($index) }
  }
  $builds.Add([pscustomobject]@{
    paper=$target;source='main.tex';pdf='paper.pdf';exit=$result;
    pdf_sha256=(Get-FileHash -LiteralPath (Join-Path $paper 'paper.pdf') -Algorithm SHA256).Hash.ToLowerInvariant();
    source_files=$dependencies;compiler='Tectonic';untrusted_mode=$true;
    note='Document compilation only; no mathematical proof certification'
  })
  $builds | ConvertTo-Json -Depth 7 | Set-Content -LiteralPath $receiptPath -Encoding UTF8
  Write-Output ('Built '+$target)
  Get-Content -LiteralPath $log -Tail 2
}
$builds | ConvertTo-Json -Depth 7 | Set-Content -LiteralPath (Join-Path $root 'verification/paper-builds.json') -Encoding UTF8
