PAIRED-PHASE BINARY POLYNOMIAL MULTIPLICATION
Version 0.2.1 - 2 November 2026
Research preprint. Independent mathematical review remains outstanding.

Árpád Csizmadia
Public contact: arpad.csizmadia.public@gmail.com

This paper gives a deterministic fixed-tape algorithm for ordinary
multiplication in F2[X]. For two coefficient lists of length n, it outputs
all 2n-1 coefficients in

    O(n (log(n+2))^(1-1/1302))

worst-case bit operations on a deterministic machine with a fixed finite alphabet and
a fixed finite number of sequential tapes. The theorem and its hypotheses
are stated in main.tex and the mathematical appendices included in paper.pdf.

Contents
  CLAIM.json                Exact problem, kappa, model, proof scope and
                            publication status in machine-readable form
  VERSION_HISTORY.txt       Prior public claim and the unpublished revision
  paper.pdf                 Article and mathematical appendices
  main.tex                  TeX source for the article
  appendices/               TeX sources for the included appendices
  checks/                   Two finite probes, imported source material,
                            and expected JSON outputs
  scripts/build-local.ps1   Bounded, offline document build
  scripts/check-candidate.ps1
                            Allowlist, manifest, and receipt checks
  verification/             Portable build, layout, and package-hash receipts
  MANIFEST.json             Allowlisted files and their SHA-256 hashes
  LICENSE                   Apache License, Version 2.0, for the project
  NOTICE.txt                Project provenance and AI-assistance disclosure
  THIRD_PARTY_NOTICES.txt   Source-specific credits and applicable notices
  SOURCES.tsv               Machine-readable source and attribution map

Reproduction
Run scripts/build-local.ps1 with the documented local Tectonic, guard, and
cache paths. The build runs offline. Then run scripts/check-candidate.ps1
to verify the allowlisted package and portable receipts. The two finite
probes check only their stated finite identities and expected outputs; they
do not execute the asymptotic algorithm or certify its running-time theorem.

Build parameters are -TectonicPath, -GuardPath and -CacheDirectory.
The Windows guard can be compiled from scripts/guarded-document.cpp;
keep its executable in build/. Tectonic 0.17.0 and the prepopulated TeX
cache must be supplied separately. The guard enforces 512 MiB aggregate
memory, 60 CPU seconds, 120 wall seconds and serialized execution.
Run the document engine with one thread and without shell escape.
For an intentionally changed package, run check-candidate.ps1 with
-RefreshManifest only after reviewing the source and PDF changes.

The article's mathematical proof is the basis for the all-size bound.
Classical results are cited as dependencies where used. Source-specific
credits and pinned references are listed in THIRD_PARTY_NOTICES.txt and
SOURCES.tsv. The package license is in LICENSE; third-party rights remain
subject to the terms attached to the relevant upstream material.

Claim history and evidence
The existing Big O Speedrun entry lists kappa=2^-38 as Claimed, with the
first public source commit fb94421e3e6d9f8348a6e5b963b5a62d9c525e95.
This revision states kappa=1/1302 for the same input/output and machine
model. Its publication fields in CLAIM.json are unset: preparation is
not publication, and the existing listing does not verify this revision.
The intended evidence description remains a written claim. The exact
score and proof scope must accompany any eventual version-specific source
link; the earlier claim's date and provenance must be preserved.
