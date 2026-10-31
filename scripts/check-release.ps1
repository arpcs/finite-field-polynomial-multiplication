param([switch]$RefreshManifest)
$ErrorActionPreference='Stop'
$root=[IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..'))
$utf8=[Text.UTF8Encoding]::new($false)
$failures=[Collections.Generic.List[string]]::new()
function Require([bool]$ok,[string]$message){if(-not $ok){$failures.Add($message)}}
function Hash([string]$path){(Get-FileHash -LiteralPath $path -Algorithm SHA256).Hash.ToLowerInvariant()}
$required=@('README.md','CONTENTS.md','AUTHORS.md','AI_USE.md','VERIFICATION.md','BUILDING.md',
 'CONTRIBUTING.md','REVIEWING.md','SUPPORT.md','ROADMAP.md','AGENTS.md','LICENSE','NOTICE','CITATION.cff',
 '.gitignore','.gitattributes','docs/LICENSING.md','docs/THIRD_PARTY_NOTICES.md','docs/CLAIM_SELECTION.md',
 'docs/RELEASE_STATUS.md','docs/VERSION_HISTORY.md',
 'docs/SUBMISSION_METADATA.json','verification/README.md','verification/paper-targets.json',
 'verification/paper-builds.json','verification/pdf-layout.json',
 'papers/01-general/proofs/finite-unit/README.md',
 'papers/01-general/proofs/finite-unit/ARTIFACTS.json',
 'papers/01-general/proofs/finite-unit/verify-finite-unit.ps1',
 'verification/finite-unit-replay.json')
foreach($name in $required){Require (Test-Path -LiteralPath (Join-Path $root $name) -PathType Leaf) ('Missing '+$name)}
$targets=@(Get-Content -LiteralPath (Join-Path $root 'verification/paper-targets.json') -Raw|ConvertFrom-Json)
Require ($targets.Count -eq 4) 'This focused release must contain exactly four paper targets'
$builds=@(Get-Content -LiteralPath (Join-Path $root 'verification/paper-builds.json') -Raw|ConvertFrom-Json)
$metadata=@(Get-Content -LiteralPath (Join-Path $root 'docs/SUBMISSION_METADATA.json') -Raw|ConvertFrom-Json)
$layout=@(Get-Content -LiteralPath (Join-Path $root 'verification/pdf-layout.json') -Raw|ConvertFrom-Json)
$closureCount=0
foreach($target in $targets){
 $paperRoot=Join-Path $root $target
 foreach($name in @('main.tex','paper.pdf','STATUS.md','audit.json','citation.bib')){Require (Test-Path -LiteralPath (Join-Path $paperRoot $name) -PathType Leaf) ('Missing '+$target+'/'+$name)}
 $main=[IO.File]::ReadAllText((Join-Path $paperRoot 'main.tex'))
 Require ($main.Contains("\author{\'Arp\'ad Csizmadia")) ('Unexpected author '+$target)
 Require ($main.Contains('arpad.csizmadia.public@gmail.com')) ('Missing public email '+$target)
 Require ([regex]::IsMatch($main,'(?i)substantial\s+(?:generative[- ]?AI|generative\s+AI|AI)')) ('Missing significant-AI disclosure '+$target)
 Require ([regex]::IsMatch($main,'(?is)Lean.{0,100}(?:unfinished|incomplete|not yet complete)')) ('Missing incomplete-Lean status '+$target)
 if($target -eq 'papers/03-best-binary'){Require ($main.Contains('2^{-38}')) 'Principal binary manuscript must state the selected saving'}
 $receipt=@($builds|Where-Object paper -eq $target)
 Require ($receipt.Count -eq 1) ('Missing/ambiguous build record '+$target)
 if($receipt.Count -eq 1){
  Require ($receipt[0].exit -eq 0) ('Failed document build '+$target)
  Require ((Hash (Join-Path $paperRoot 'paper.pdf')) -eq $receipt[0].pdf_sha256) ('Stale PDF '+$target)
  foreach($source in $receipt[0].source_files){Require ((Hash (Join-Path $root $source.path)) -eq $source.sha256) ('Source changed after build '+$source.path)}
 }
 $entry=@($metadata|Where-Object directory -eq $target)
 Require ($entry.Count -eq 1) ('Missing/ambiguous metadata '+$target)
 if($entry.Count -eq 1){
  Require ($entry[0].author -eq 'Árpád Csizmadia' -and $entry[0].email -eq 'arpad.csizmadia.public@gmail.com') ('Author metadata mismatch '+$target)
  Require ($entry[0].abstract_tex.Length -gt 0 -and $entry[0].abstract_tex.Length -le 1920 -and $entry[0].abstract_tex -notmatch '[^\x00-\x7F]') ('Invalid arXiv metadata abstract '+$target)
 }
 $pageRecord=@($layout|Where-Object paper -eq $target)
 Require ($pageRecord.Count -eq 1) ('Missing/ambiguous selected-page layout record '+$target)
 if($pageRecord.Count -eq 1){
  Require ($pageRecord[0].pdf_sha256 -eq (Hash (Join-Path $paperRoot 'paper.pdf'))) ('Stale layout record '+$target)
  Require ($pageRecord[0].overfull_boxes -eq 0 -and $pageRecord[0].undefined_references -eq 0) ('Unresolved layout/reference warning '+$target)
 }
 $pending=[Collections.Generic.Queue[string]]::new();$seen=[Collections.Generic.HashSet[string]]::new([StringComparer]::OrdinalIgnoreCase)
 $pending.Enqueue((Join-Path $paperRoot 'main.tex'))
 while($pending.Count){
  $path=$pending.Dequeue();if(-not $seen.Add($path)){continue};$closureCount++
  $text=[IO.File]::ReadAllText($path) -replace '(?m)(?<!\\)%.*$',''
  foreach($match in [regex]::Matches($text,'\\(?:input|include)\s*\{([^}]+)\}')){
   $include=$match.Groups[1].Value;if(-not [IO.Path]::GetExtension($include)){$include+='.tex'}
   $resolved=[IO.Path]::GetFullPath((Join-Path $paperRoot $include))
   $valid=$resolved.StartsWith($paperRoot+[IO.Path]::DirectorySeparatorChar,[StringComparison]::OrdinalIgnoreCase) -and (Test-Path -LiteralPath $resolved -PathType Leaf)
   Require $valid ('Missing/external TeX input '+$include+' in '+$target)
   if($valid){$pending.Enqueue($resolved)}
  }
 }
}
# Verify finite-premise artifacts offline; never execute their checkers here.
$unitRoot=Join-Path $root 'papers/01-general/proofs/finite-unit'
$unitManifest=Join-Path $unitRoot 'ARTIFACTS.json'
$unitCount=0
if(Test-Path -LiteralPath $unitManifest -PathType Leaf){
 $unit=Get-Content -LiteralPath $unitManifest -Raw|ConvertFrom-Json
 Require ($unit.schema -eq 'finite-unit-artifacts/1') 'Unsupported finite-unit artifact schema'
 $unitPaths=[Collections.Generic.HashSet[string]]::new([StringComparer]::OrdinalIgnoreCase)
 foreach($artifact in $unit.files){
  $path=[IO.Path]::GetFullPath((Join-Path $unitRoot $artifact.path))
  $inside=$path.StartsWith($unitRoot+[IO.Path]::DirectorySeparatorChar,[StringComparison]::OrdinalIgnoreCase)
  Require ($inside -and $unitPaths.Add($path)) ('Invalid/duplicate finite-unit path '+$artifact.path)
  if($inside){
   $exists=Test-Path -LiteralPath $path -PathType Leaf
   Require $exists ('Missing finite-unit artifact '+$artifact.path)
   if($exists){
    Require ((Get-Item -LiteralPath $path).Length -eq $artifact.bytes -and (Hash $path) -eq $artifact.sha256) ('Finite-unit artifact mismatch '+$artifact.path)
   }
  }
  $unitCount++
 }
 Require ($unitCount -gt 0) 'Empty finite-unit artifact manifest'
}
$finiteReceipt=Join-Path $root 'verification/finite-unit-replay.json'
if((Test-Path -LiteralPath $finiteReceipt -PathType Leaf) -and (Test-Path -LiteralPath $unitManifest -PathType Leaf)){
 $replay=Get-Content -LiteralPath $finiteReceipt -Raw|ConvertFrom-Json
 Require ($replay.schema -eq 'finite-unit-public-replay/1' -and $replay.result -eq 'pass') 'Invalid finite-unit replay record'
 Require ($replay.artifact_manifest.path -eq 'papers/01-general/proofs/finite-unit/ARTIFACTS.json' -and $replay.artifact_manifest.sha256 -eq (Hash $unitManifest)) 'Stale finite-unit replay artifact binding'
 Require ($replay.public_result_bins_match -eq $true) 'Finite-unit invoice comparison did not pass'
 Require ((@($replay.runs.name|Sort-Object) -join ',') -eq 'controller,native-scalar,rate') 'Unexpected finite-unit replay checks'
 foreach($run in $replay.runs){
  Require ($run.exit -eq 0 -and $run.historical_output_match -eq $true) ('Failed finite-unit replay '+$run.name)
  foreach($output in @($run.stdout,$run.stderr)){
   $path=[IO.Path]::GetFullPath((Join-Path $root $output.path))
   $inside=$path.StartsWith((Join-Path $root 'verification/finite-unit')+[IO.Path]::DirectorySeparatorChar,[StringComparison]::OrdinalIgnoreCase)
   Require $inside ('Invalid finite-unit output path '+$output.path)
   if($inside){
    $exists=Test-Path -LiteralPath $path -PathType Leaf
    Require $exists ('Missing finite-unit replay output '+$output.path)
    if($exists){Require ((Get-Item -LiteralPath $path).Length -eq $output.bytes -and (Hash $path) -eq $output.sha256) ('Finite-unit replay output mismatch '+$output.path)}
   }
  }
 }
}
$files=@(Get-ChildItem -LiteralPath $root -File -Recurse -Force|Where-Object {
 $_.FullName.Substring($root.Length+1) -notmatch '(^|[\\/])(\.build|\.tools|\.git|build)[\\/]'
})
Require ($files.Count -gt 0) 'No release files were enumerated'
foreach($file in $files){
 Require ($file.Length -lt 25000000) ('Oversized file '+$file.Name)
 Require ($file.Extension -notin @('.exe','.dll','.o','.obj','.olean','.ilean')) ('Unexpected generated object '+$file.Name)
 if($file.Extension -in @('.md','.txt','.json','.yml','.ps1','.cpp','.h','.hpp','.tex','.cff')){
  $body=[IO.File]::ReadAllText($file.FullName)
  Require (-not [regex]::IsMatch($body,'ghp_[A-Za-z0-9]{36}|github_pat_[A-Za-z0-9_]{40,}|sk-(?:proj-)?[A-Za-z0-9_-]{32,}|-----BEGIN (?:RSA |EC |OPENSSH )?PRIVATE KEY-----')) ('Possible credential material '+$file.Name)
 }
}
$manifest=Join-Path $root 'SHA256SUMS.txt'
$payload=@($files|Where-Object {$_.FullName -ne $manifest -and $_.FullName -ne (Join-Path $root 'verification/release-check.json')}|Sort-Object FullName)
if($RefreshManifest){[IO.File]::WriteAllLines($manifest,@($payload|ForEach-Object {(Hash $_.FullName)+'  '+$_.FullName.Substring($root.Length+1).Replace('\','/')}),$utf8)}
Require (Test-Path -LiteralPath $manifest) 'Missing checksum manifest'
if(Test-Path -LiteralPath $manifest){
 $entries=@(Get-Content -LiteralPath $manifest|Where-Object {$_});Require ($entries.Count -eq $payload.Count) 'Manifest file count differs'
 foreach($line in $entries){
  if($line -notmatch '^([0-9a-f]{64})  (.+)$'){$failures.Add('Malformed manifest line');continue}
  $expected=$Matches[1];$path=[IO.Path]::GetFullPath((Join-Path $root $Matches[2]))
  $inside=$path.StartsWith($root+[IO.Path]::DirectorySeparatorChar,[StringComparison]::OrdinalIgnoreCase)
  Require $inside 'Manifest path escapes root'
  if($inside){Require ((Test-Path -LiteralPath $path -PathType Leaf) -and (Hash $path) -eq $expected) ('Manifest mismatch '+$Matches[2])}
 }
}
$report=[pscustomobject]@{
 prepared_date='2026-10-31';check='Focused first-release packaging/source-integrity check'
 passed=($failures.Count -eq 0);payload_files=$payload.Count;total_release_files=$files.Count
 papers=$targets.Count;tex_closure_files=$closureCount;finite_unit_artifacts=$unitCount
 mathematical_correctness_assessed=$false;lean_executed=$false;network_used=$false;publishes_or_submits=$false
 failures=@($failures)
}
$report|ConvertTo-Json -Depth 5|Set-Content -LiteralPath (Join-Path $root 'verification/release-check.json') -Encoding UTF8
$report|ConvertTo-Json -Depth 5
if($failures.Count){throw ('Release check failed with '+$failures.Count+' issue(s)')}
