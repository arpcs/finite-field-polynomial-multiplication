param([switch]$RefreshManifest)
$ErrorActionPreference='Stop'
$root=[IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..')).TrimEnd([IO.Path]::DirectorySeparatorChar)
$issues=[Collections.Generic.List[string]]::new()
function Require([bool]$ok,[string]$message){if(-not $ok){$issues.Add($message)}}
function Hash([string]$p){(Get-FileHash -LiteralPath $p -Algorithm SHA256).Hash.ToLowerInvariant()}
$list=Join-Path $root 'PACKAGE_FILES.txt'
if(-not (Test-Path -LiteralPath $list)){throw 'Explicit package file list missing'}
$names=@(Get-Content -LiteralPath $list|Where-Object {$_ -and -not $_.StartsWith('#')})
Require (@($names|Select-Object -Unique).Count -eq $names.Count) 'Duplicate package path'
$files=[Collections.Generic.List[object]]::new()
foreach($name in $names){
 Require ($name -notmatch '\\' -and -not [IO.Path]::IsPathRooted($name)) ('Nonportable package path '+$name)
 $file=[IO.Path]::GetFullPath((Join-Path $root $name))
 $inside=$file.StartsWith($root+[IO.Path]::DirectorySeparatorChar,[StringComparison]::OrdinalIgnoreCase)
 Require $inside ('Path escapes package '+$name)
 Require (-not $name.StartsWith('build/') -and $name -notmatch '(?i)(^|/)(?:internal|reviews|lean)/|(^|/)compiler\.(?:stdout|stderr)(?:\.txt)?$|\.log$') ('Internal artifact in package '+$name)
 if(-not $inside){continue}
 if($name -in @('MANIFEST.json','verification/package-check.json')){continue}
 $exists=Test-Path -LiteralPath $file -PathType Leaf
 Require $exists ('Missing package member '+$name)
 if(-not $exists){continue}
 $item=Get-Item -LiteralPath $file
 Require ($item.Extension -notin @('.lean','.olean','.ilean','.exe','.dll','.o','.obj','.aux','.out')) ('Excluded binary/object '+$name)
 Require ($item.Length -lt 10000000) ('Unexpected file size '+$name)
 if($item.Extension -in @('.txt','.json','.tsv','.ps1','.cpp','.hpp','.tex','.bib')){
  $data=[IO.File]::ReadAllText($file)
  Require ($data -notmatch '(?i)(?<![A-Z0-9])[A-Z]:[\\/]|[\\/]Users[\\/]|[\\/]home[\\/]') ('Local machine path in '+$name)
  if($item.Extension -notin @('.ps1','.cpp','.hpp')){
   Require ($data -notmatch '(?i)request_user_input|send_user_message|owner requested|chat transcript|conversation ledger') ('Private workflow material in '+$name)
  }
  Require ($data -notmatch 'ghp_[A-Za-z0-9]{36}|github_pat_[A-Za-z0-9_]{40,}|sk-(?:proj-)?[A-Za-z0-9_-]{32,}|-----BEGIN (?:RSA |EC |OPENSSH )?PRIVATE KEY-----') ('Possible credential in '+$name)
 }
 $files.Add([pscustomobject]@{path=$name;bytes=$item.Length;sha256=(Hash $file)})
}
$sources=@($files|Where-Object {$_.path.EndsWith('.tex')})
Require ('MANIFEST.json' -in $names -and 'verification/package-check.json' -in $names) 'Generated receipts missing from file list'
$allTex=($sources|ForEach-Object {[IO.File]::ReadAllText((Join-Path $root $_.path))}) -join "`n"
$labels=@([regex]::Matches($allTex,'\\label\{([^}]+)\}')|ForEach-Object {$_.Groups[1].Value})
Require (@($labels|Select-Object -Unique).Count -eq $labels.Count) 'Duplicate TeX label'
foreach($m in [regex]::Matches($allTex,'\\(?:ref|eqref)\{([^}]+)\}')){Require ($m.Groups[1].Value -in $labels) ('Missing TeX label '+$m.Groups[1].Value)}
$keys=@([regex]::Matches($allTex,'\\bibitem\{([^}]+)\}')|ForEach-Object {$_.Groups[1].Value})
foreach($m in [regex]::Matches($allTex,'\\cite(?:\[[^\]]*\])?\{([^}]+)\}')){foreach($key in $m.Groups[1].Value.Split(',')){Require ($key -in $keys) ('Missing citation '+$key)}}
foreach($m in [regex]::Matches($allTex,'\\(?:input|include)\{([^}]+)\}')){Require ($m.Groups[1].Value -in $names) ('Unpackaged TeX input '+$m.Groups[1].Value)}
Require ($allTex -notmatch '\\(?:write18|includegraphics)\b') 'Unexpected TeX external operation'
Require ($allTex -notmatch 'supporting/|investigation/|\{dossier\}') 'Unbundled proof-note reference'
$build=Get-Content -LiteralPath (Join-Path $root 'verification/build.json') -Raw|ConvertFrom-Json
Require ($build.exit -eq 0 -and $build.untrusted -and $build.offline_only_cached) 'Document build missing or unsafe'
Require ($build.memory_mib -eq 512 -and $build.cpu_seconds -eq 60 -and $build.wall_seconds -eq 120 -and $build.threads -eq 1) 'Unexpected build limits'
Require ($build.overfull_boxes -eq 0 -and $build.undefined_references -eq 0) 'Document warnings unresolved'
Require ($build.pdf_sha256.ToLowerInvariant() -eq (Hash (Join-Path $root 'paper.pdf'))) 'PDF differs from build'
Require ($build.source_files.Count -eq $sources.Count) 'Incomplete built-source closure'
foreach($s in $build.source_files){Require ($s.sha256.ToLowerInvariant() -eq (Hash (Join-Path $root $s.path))) ('Stale built source '+$s.path)}
$layout=Get-Content -LiteralPath (Join-Path $root 'verification/layout.json') -Raw|ConvertFrom-Json
Require ($layout.pdf_sha256.ToLowerInvariant() -eq (Hash (Join-Path $root 'paper.pdf'))) 'Stale PDF layout record'
Require ($layout.all_pages_visually_reviewed -and $layout.layout_defects -eq 0 -and $layout.reviewed_pages.Count -eq $layout.pages) 'PDF visual review incomplete'
foreach($probe in @('finite_certificate','frozen_rectangles')){
 $run=Get-Content -LiteralPath (Join-Path $root ('checks/expected/'+$probe+'.receipt.json')) -Raw|ConvertFrom-Json
 $dataPath=Join-Path $root ('checks/expected/'+$probe+'.json')
 $data=Get-Content -LiteralPath $dataPath -Raw|ConvertFrom-Json
 Require ($run.exit_code -eq 0 -and $data.pass) ('Finite certificate failed '+$probe)
 Require ($run.source_sha256.ToLowerInvariant() -eq (Hash (Join-Path $root ('checks/probes/'+$probe+'.cpp')))) ('Finite source changed '+$probe)
 Require ($run.output_sha256.ToLowerInvariant() -eq (Hash $dataPath)) ('Finite output changed '+$probe)
}
Require ('CLAIM.json' -in $names -and 'VERSION_HISTORY.txt' -in $names) 'Claim metadata or history missing from distribution'
$claim=Get-Content -LiteralPath (Join-Path $root 'CLAIM.json') -Raw|ConvertFrom-Json
Require ($claim.schema -eq 'fastmul-research-claim/1' -and $claim.version -eq '0.2.1') 'Unknown claim metadata version'
Require ($claim.bound.kappa_exact -eq '1/1302' -and $claim.bound.logarithmic_exponent_exact -eq '1301/1302') 'Incorrect exact score or exponent'
Require ($claim.problem.field -eq 'F2' -and $claim.problem.variables -eq 1 -and $claim.problem.product -eq 'ordinary univariate polynomial product') 'Claim changes the problem scope'
Require ($claim.problem.randomization -eq 'none' -and $claim.problem.cost.StartsWith('worst-case')) 'Claim changes the deterministic worst-case model'
Require ($claim.artifacts.paper.sha256.ToLowerInvariant() -eq (Hash (Join-Path $root 'paper.pdf'))) 'Claim metadata names a different PDF'
Require ($claim.artifacts.paper.pages -eq $layout.pages -and $claim.bound.theorem_label -in $labels) 'Claim locator or page count mismatch'
Require ($claim.evidence.independent_human_review -eq $false -and $claim.evidence.end_to_end_formal_proof_supplied -eq $false) 'Unsupported stronger verification status'
Require ($claim.evidence.requested_site_evidence_after_publication -eq 'claimed') 'Incorrect proposed site evidence level'
Require ($claim.predecessor.kappa_exact -eq '1/274877906944' -and $claim.predecessor.source_commit -eq 'fb94421e3e6d9f8348a6e5b963b5a62d9c525e95') 'Listed predecessor provenance changed'
Require ($claim.publication.state -in @('unpublished','published')) 'Unknown publication state'
if($claim.publication.state -eq 'unpublished'){
 foreach($field in @('first_public_statement_utc','public_commit','public_paper_url','public_source_url')){
  Require ($null -eq $claim.publication.$field) ('Unpublished claim has a fabricated publication field: '+$field)
 }
}else{
 Require ($claim.publication.public_commit -match '^[0-9a-fA-F]{40}$') 'Public source commit missing'
 Require ($claim.publication.public_paper_url -match '^https://' -and $claim.publication.public_source_url -match '^https://') 'Public evidence URLs missing'
 Require (-not [string]::IsNullOrWhiteSpace($claim.publication.first_public_statement_utc)) 'First public statement provenance missing'
}
$payload=@($files|Where-Object {$_.path -notin @('MANIFEST.json','verification/package-check.json')})
$manifestPath=Join-Path $root 'MANIFEST.json'
if($RefreshManifest){$payload|ConvertTo-Json -Depth 4|Set-Content -LiteralPath $manifestPath -Encoding utf8}
if(Test-Path -LiteralPath $manifestPath){
 $manifest=@(Get-Content -LiteralPath $manifestPath -Raw|ConvertFrom-Json)
 Require ($manifest.Count -eq $payload.Count) 'Manifest count mismatch'
 foreach($e in $manifest){$current=@($payload|Where-Object path -eq $e.path);Require ($current.Count -eq 1 -and $current[0].sha256 -eq $e.sha256 -and $current[0].bytes -eq $e.bytes) ('Manifest mismatch '+$e.path)}
}else{Require $false 'Manifest missing'}
$report=[pscustomobject]@{
 schema='reader-package-check/1';version='0.2.1';passed=($issues.Count -eq 0);payload_files=$payload.Count
 explicit_allowlist=$true;portable_paths_checked=$true;source_closure_checked=$true
 claim_scope_and_exact_score_checked=$true;publication_url_reachability_checked=$false
 mathematical_correctness_certified=$false;mathematical_program_executed=$false;network_used=$false
 failures=@($issues)
}
$report|ConvertTo-Json -Depth 4|Set-Content -LiteralPath (Join-Path $root 'verification/package-check.json') -Encoding utf8
$report|ConvertTo-Json -Depth 4
if($issues.Count){throw ('Package checks failed: '+$issues.Count)}
