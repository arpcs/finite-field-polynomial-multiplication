# Building and checking

From this release root in PowerShell 7:

```powershell
.\scripts\check-release.ps1
```

This checks the four document targets, source/PDF receipts, local source
closure, author/AI metadata, recorded hashes, the finite-unit artifact manifest
and focused credential patterns.
It does not compile Lean, run witnesses, use the network, publish or commit.

## Rebuild PDFs

The release uses Tectonic in untrusted mode. On Windows, build the small
resource guard with MinGW-w64, then invoke the paper build script:

```powershell
New-Item -ItemType Directory -Force .tools | Out-Null
g++ -std=c++17 -O2 -municode -static -static-libgcc -static-libstdc++ `
  scripts/guarded-document.cpp -o .tools/guarded-document.exe
.\scripts\build-papers.ps1 -TectonicPath 'path\to\tectonic.exe' `
  -GuardPath .tools/guarded-document.exe
```

The guard serializes runs and caps each document job at 512 MiB aggregate,
60 CPU seconds and 120 wall seconds. It stops only its own child job. Use
`-CacheDirectory path\to\cache -OnlyCached` for an offline build after the
standard TeX package/font cache is populated. Toolchains and caches are not
committed; logs stay in ignored `.build/`.

Review the new PDF, unresolved references and layout warnings after source
edits. Only after deliberate review, refresh and verify the checksum manifest:

```powershell
.\scripts\check-release.ps1 -RefreshManifest
.\scripts\check-release.ps1
```

The two optional small algebra witnesses have their own instructions under
`papers/02-simple-binary/witnesses/`. Their self-installed resource guard is
mandatory; a compile or package check does not execute them. Historical JSON
receipts are preserved as historical results, not new runs for this revision.

The odd-field finite scalar/controller/profile checks have a separate
[artifact map and reproduction guide](papers/01-general/proofs/finite-unit/README.md).
Their default script invocation checks hashes only. An explicit guarded
`-Replay` compiles and runs the three small checks serially; it does not
execute a full multiplier or Lean. The release includes the successful
[31 October replay record](verification/finite-unit-replay.json) and text outputs.
