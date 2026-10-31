# Status: general fixed-field n log n baseline companion

**Version:** 0.1.0-preprint, prepared 31 October 2026.  
**Author:** Árpád Csizmadia, arpad.csizmadia.public@gmail.com.  
**Scope:** ordinary dense multiplication over each individually fixed finite field, in a fixed coefficient basis, on a deterministic finite-alphabet machine with a fixed finite number of sequential tapes.

## Exact claim and shared proof sources

For each fixed field F_q, multiplication of two degree-<n polynomials takes O_q(n log(n+2)) bit time and returns all 2n-1 ordinary coefficients, including leading zeros.

The proof uses these existing companion statements:

- For the prime field F2: the Pascal-transform multiplier stated in [the accessible binary companion](../02-simple-binary/STATUS.md), with its stated OpenAI equal-chunk interchange dependency.
- For each odd prime field F_p: **Proposition 1 only** of [the stronger general companion](../01-general/STATUS.md), specialized to extension degree one. Its exponent 9999/10000 is weakened to 1. Its bundled odd-field/native construction and named Stage2 interchange dependency remain visible.
- For fixed q=p^e: e^2 ordinary prime-field products and a fixed-basis recombination, with O_q(n) bit cost for encoding, sequential scans, fixed-constant arithmetic, output and cleanup.

This note does not use the stronger general companion's combined all-field theorem or the controlled-CRT binary result. Its proof is therefore not circular through that combination. It shares the odd-field argument with the stronger companion and is not presented as an independent discovery. No growing-field uniformity, practical speedup, combined workspace bound or novelty certification is asserted.

## Prior work and attribution

The bibliography identifies Harvey–van der Hoeven–Lecerf's earlier Fürer-type bound, Harvey–van der Hoeven's unconditional cyclotomic fixed-prime benchmark, their separately conditional finite-field n log n theorem, and Harvey's 20 October 2026 discussion of the finite-field gap. The published 2022 finite-field theorem retains its Linnik hypothesis; it is not conflated with unconditional integer multiplication. The proof's component algorithms and their dependencies are credited rather than restated as new constructions here.

Substantial generative AI assistance is disclosed. OpenAI Codex is identified as a release/source-inspection tool, with its platform reference; no unsupported historical model/version sequence or AI coauthor is invented.

## Evidence and limitations

This is a written research preprint open for mathematical review. No independent human proof review or complete theorem-level Lean verification is claimed. Full Lean formalization is unfinished and planned for a later update, without a completion-date promise. The full Lean goal remains paused.

The source-authoring pass created this companion without a PDF build, scientific computation or Lean job. Final document compilation, selected-page layout review and source/PDF hashes are recorded separately under [verification](../../verification/README.md) when performed. A package or compilation check does not establish the imported arguments or the complete complexity theorem.

`audit.json` records this new synthesis, its exact current source hashes and the shared proof dependencies. It excludes its own hash to avoid self-reference.
