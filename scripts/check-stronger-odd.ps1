param()
$ErrorActionPreference='Stop'
$root=[IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..'))
$paperRoot=Join-Path $root 'papers/01-general'
$proofRoot=Join-Path $paperRoot 'proofs/stronger-odd-20261102'
$proofBoundary=Join-Path $paperRoot 'proofs'
function AssetHash([string]$path){(Get-FileHash -LiteralPath $path -Algorithm SHA256).Hash.ToLowerInvariant()}
$manifest=Get-Content -LiteralPath (Join-Path $proofRoot 'ASSETS.json') -Raw | ConvertFrom-Json
if($manifest.schema -ne 'stronger-odd-update-assets/2'){throw 'Unsupported stronger-odd asset manifest'}
$seen=[Collections.Generic.HashSet[string]]::new([StringComparer]::OrdinalIgnoreCase)
foreach($asset in $manifest.files){
  $path=[IO.Path]::GetFullPath((Join-Path $proofRoot $asset.path))
  if(-not $path.StartsWith($proofRoot+[IO.Path]::DirectorySeparatorChar,[StringComparison]::OrdinalIgnoreCase) -or -not $seen.Add($path)){throw ('Invalid/duplicate stronger-odd asset: '+$asset.path)}
  $file=Get-Item -LiteralPath $path
  if($file.Length -ne $asset.bytes -or (AssetHash $path) -ne $asset.sha256.ToLowerInvariant()){throw ('Stronger-odd asset mismatch: '+$asset.path)}
}
foreach($asset in $manifest.reused_assets){
  $path=[IO.Path]::GetFullPath((Join-Path $proofRoot $asset.package_path))
  if(-not $path.StartsWith($proofBoundary+[IO.Path]::DirectorySeparatorChar,[StringComparison]::OrdinalIgnoreCase)){throw ('Reused asset escapes proof tree: '+$asset.package_path)}
  if((AssetHash $path) -ne $asset.package_sha256.ToLowerInvariant()){throw ('Reused stronger-odd asset mismatch: '+$asset.package_path)}
}
$selection=Get-Content -LiteralPath (Join-Path $proofRoot 'SOURCE_SELECTION.json') -Raw | ConvertFrom-Json
if($selection.original.sha256.ToLowerInvariant() -ne '6cd806c6e52a4883270da6002a4d0c7b0120ca719745033183eb5686b3db6f07'){throw 'Unexpected original native source revision'}
if((AssetHash (Join-Path $proofRoot 'native-source.tex.txt')) -ne $selection.derived.sha256.ToLowerInvariant()){throw 'Edited native supplement selection binding mismatch'}
if($selection.derived.byte_identical -ne $false){throw 'Edited supplement must not be represented as byte-identical research source'}
$main=[IO.File]::ReadAllText((Join-Path $paperRoot 'main.tex'))
if(-not $main.Contains('^{319/320}') -or -not $main.Contains('^{1301/1302}') -or -not $main.Contains('3125805') -or -not $main.Contains('\cite{PairedPhase}') -or -not $main.Contains('\label{cor:paired-phase-extension}')){throw 'Missing odd/all-field tariff or paired-phase dependency statement'}
if(-not $main.Contains('\input{proofs/stronger-odd-20261102/host-transfer.tex}')){throw 'Stronger host proof is not included in the manuscript'}
$audit=Get-Content -LiteralPath (Join-Path $paperRoot 'audit.json') -Raw | ConvertFrom-Json
$previous=$audit.previous_revision
if($previous.git_commit -ne '14532be8e044c0f6588b9787a842a96da695769f' -or $previous.directory -ne 'papers/01-general'){throw 'Unexpected previous-source pin'}
if($previous.source_tree_url -ne ('https://github.com/arpcs/finite-field-polynomial-multiplication/tree/'+$previous.git_commit+'/papers/01-general')){throw 'Previous-source URL does not identify the pinned revision'}
$previousPaths=@($previous.files.path|Sort-Object)
$expectedPaths=@('STATUS.md','audit.json','citation.bib','main.tex','paper.pdf')|Sort-Object
if($previousPaths.Count -ne 5 -or @(Compare-Object $expectedPaths $previousPaths).Count){throw 'Incomplete previous-source identity record'}
foreach($asset in $previous.files){
  if($asset.sha256 -notmatch '^[a-f0-9]{64}$' -or $asset.git_blob_sha1 -notmatch '^[a-f0-9]{40}$' -or $asset.bytes -lt 0){throw 'Invalid previous-source identity'}
}
# The previous bytes remain in the immutable Git revision; this offline check
# validates their identity records without requiring duplicate manuscript files.
foreach($source in $audit.current_sources){
 $path=[IO.Path]::GetFullPath((Join-Path $paperRoot $source.path))
 if(-not $path.StartsWith($paperRoot+[IO.Path]::DirectorySeparatorChar,[StringComparison]::OrdinalIgnoreCase)){throw 'Dated audit path escapes paper'}
 if((Get-Item -LiteralPath $path).Length -ne $source.bytes -or (AssetHash $path) -ne $source.sha256){throw ('Stale stronger-odd source audit: '+$source.path)}
}
$pdfHash=AssetHash (Join-Path $paperRoot 'paper.pdf')
$build=@(Get-Content -LiteralPath (Join-Path $root 'verification/paper-builds.json') -Raw | ConvertFrom-Json | Where-Object paper -eq 'papers/01-general')
$layout=@(Get-Content -LiteralPath (Join-Path $root 'verification/pdf-layout.json') -Raw | ConvertFrom-Json | Where-Object paper -eq 'papers/01-general')
if($build.Count -ne 1 -or $build[0].exit -ne 0 -or $build[0].pdf_sha256 -ne $pdfHash -or $audit.document.sha256 -ne $pdfHash){throw 'Stale stronger-odd PDF/build association'}
foreach($source in $build[0].source_files){if((AssetHash (Join-Path $root $source.path)) -ne $source.sha256){throw ('Stronger-odd build source changed: '+$source.path)}}
if($layout.Count -ne 1 -or $layout[0].pdf_sha256 -ne $pdfHash -or $layout[0].overfull_boxes -ne 0 -or $layout[0].undefined_references -ne 0){throw 'Stale stronger-odd layout/reference record'}
if($audit.version -eq '0.2.2'){
 $combination=Get-Content -LiteralPath (Join-Path $root 'verification/all-fixed-field-combination-0.2.2.json') -Raw | ConvertFrom-Json
 if($combination.schema -ne 'all-fixed-field-combination-review/1' -or $combination.version -ne '0.2.2'){throw 'Missing current combination record'}
 if($combination.review.path -ne 'verification/all-fixed-field-combination-0.2.2.md' -or (AssetHash (Join-Path $root $combination.review.path)) -ne $combination.review.sha256){throw 'Stale combination review binding'}
 if($combination.main.path -ne 'papers/01-general/main.tex' -or (AssetHash (Join-Path $root $combination.main.path)) -ne $combination.main.sha256 -or $audit.review.main_sha256 -ne $combination.main.sha256){throw 'Stale combination source binding'}
 if($combination.document.sha256 -ne $pdfHash -or $combination.document.pages -ne $layout[0].pages){throw 'Stale combination document binding'}
 if($combination.binary_input.path -ne 'papers/03-best-binary/versions/0.2.1/main.tex' -or $combination.binary_input.commit -ne 'e85bc1f6ca0ec9c13281c94b6a3e88ec2cdb4fc5' -or (AssetHash (Join-Path $root $combination.binary_input.path)) -ne $combination.binary_input.sha256){throw 'Incorrect paired-phase input binding'}
 if($combination.independent_human_review -or $combination.complete_formal_verification -or $combination.lean_run -or $combination.new_finite_replay_run){throw 'Unsupported combination evidence status'}
}
Write-Output ('PASS stronger-odd update: PDF/build/layout, dated source audit, '+$manifest.files.Count+' assets, '+$manifest.reused_assets.Count+' reuses and previous-source pins; no math/build/network job')
