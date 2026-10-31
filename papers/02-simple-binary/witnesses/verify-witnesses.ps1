param([string]$Compiler = 'g++')
$ErrorActionPreference = 'Stop'
if (-not $IsWindows -and $env:OS -ne 'Windows_NT') { throw 'The bounded witness job guards require Windows.' }
$build = Join-Path $PSScriptRoot 'build'
New-Item -ItemType Directory -Force -Path $build | Out-Null
$code = Join-Path $PSScriptRoot 'code'
$names = @('bounded_prefix_macro_fft', 'bounded_prefix_macro_parent')
foreach ($name in $names) {
    $source = Join-Path $code ($name + '.cpp')
    $exe = Join-Path $build ($name + '.exe')
    & $Compiler -O1 -std=c++17 -Wall -Wextra -Wpedantic -fno-exceptions -fno-rtti $source -o $exe
    if ($LASTEXITCODE -ne 0) { throw "Compilation failed: $name" }
    $output = (& $exe 2>&1 | Out-String).Trim()
    if ($LASTEXITCODE -ne 0) { throw "Guarded witness failed: $name`n$output" }
    $report = $output | ConvertFrom-Json
    if ($report.status -notlike 'PASS*' -or $report.memory_limit_MiB -ne 64 -or $report.CPU_limit_seconds -ne 10) { throw "Unexpected witness report: $name" }
    [IO.File]::WriteAllText((Join-Path $build ($name + '.json')), $output + "`n", (New-Object System.Text.UTF8Encoding($false)))
    Write-Output ("PASS: " + $name)
}
