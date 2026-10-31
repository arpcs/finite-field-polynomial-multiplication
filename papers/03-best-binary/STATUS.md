# Status: Ordinary Binary Polynomial Multiplication below n log n

**Version:** 0.1.0-preprint, 31 October 2026  
**Scope:** ordinary dense degree-`<n` polynomial multiplication over fixed `F2`; deterministic fixed finite-tape bit model; output is the complete `2n-1` ordinary coefficients.  
**Claim:** `O(n (max{1, ceil(log2 n)})^(1-2^-38))`; author Árpád Csizmadia (`arpad.csizmadia.public@gmail.com`). Fixed extensions `F_(2^s)` follow for each fixed `s`, with machine and constants depending on `s`.

## Proof and dependency status

This release copy uses the integrated controlled-CRT construction in `main.tex` and its four proof appendices. The written proof provides the ordinary input/output reduction, host initialization, coefficient split, balanced controlled CRT tree, literal Fourier convention, local Fourier word and arithmetic, arbitrary-payload native endpoint transform, equal-chunk interchange construction, and fixed-tape/cost composition. Selected supporting derivation records and the machine-composition root are included under `supporting/`.

The proof has no unresolved `P_beta`, `C_rho`, or analogous machine-interface hypothesis identified in the focused source audit. It relies on three cited mathematical results: the unconditional Harvey--van der Hoeven cyclotomic host/root construction, classical fixed-tape integer multiplication, and the equal-chunk SWAP result. These are stated as imported theorem dependencies, not hidden algorithmic suppliers. The manuscript's own appendices reconstruct the additional controlled routing, endpoint, Fourier, and ordinary-I/O interfaces. This assessment comes from a focused internal AI-assisted read-through, not external certification or a recorded personal proof check by the named human author.

## Research and verification status

The manuscript remains a research preprint open for mathematical review. It has not received independent external mathematical review; no novelty or priority claim is made. Substantial generative-AI assistance is disclosed. Lean formalization of the full theorem is unfinished and is intended for a later update. Existing finite witness reports are described as previously recorded evidence and were not rerun for this release copy; they do not establish the growing-size theorem.

The source TeX files are copied from the 30 October 2026 controlled-CRT manuscript. Release metadata, source paths, SHA-256 hashes, and copy hashes are in `audit.json`. Supporting derivation records are included at their referenced relative paths. The cited external papers remain linked in the bibliography.

The PDF has been compiled from this release source with the serialized document guard. Source/PDF hashes and selected-page layout review are recorded under ../../verification/. Compilation is not mathematical certification.


## Final document packaging

The final PDF uses version 0.1.0-preprint, the supplied public contact, and Apache-2.0 for original project material. The compiler/reference checks and selected-page visual inspection are recorded in verification/paper-builds.json and verification/pdf-layout.json at the repository root. No independent mathematical or full Lean verification is implied.
