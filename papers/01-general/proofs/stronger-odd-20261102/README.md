# Native supplement for the odd-field transfer

Revision 0.2.1, 2 November 2026.

The [compiled host appendix](host-transfer.tex) proves the ordinary
fixed-odd-field transfer. The [native source](native-source.tex.txt)
provides its equal-field interchange and odd-ring phase constructions,
including their finite words, compilers and routing interfaces.

## Selected source and dependencies

The selected conclusions are `thm:mixedbitswap` and the phase-only
`thm:mixedbitinteger`. The latter is restated without the original integer
application. The source retains their required adapters and supporting
proofs, including the pinned Stage2 ordinary-bit wrapper, native dock,
controlled routing, CRT and precision arguments.

[SOURCE_SELECTION.json](SOURCE_SELECTION.json) identifies the original
470,230-byte research source, the retained and omitted spans, restatements,
and the distinct hash of the edited publication source. The supplement
is not a byte-identical copy of that research snapshot. Earlier review
hashes identify the snapshots reviewed at the time.

The [service contracts](notes/NATIVE_SERVICE_CONTRACTS.md),
[compiler and reserve arguments](notes/FINITE_COMPILER_AND_RESERVE.md),
[principal-root interface](notes/PRINCIPAL_ROOT_INTERFACE.md),
[exact-width printer](notes/DYADIC_TO_EXACT_WIDTH_PRINTER_PROOF.md),
[Fourier factorization](notes/RING_VALID_FOURIER_TOEPLITZ_PROOF.md),
[three-C word](notes/OPTIMAL_THREE_C_FINITE_ALGEBRA_THEOREM.md) and
[finite-source scope](notes/FINITE_NATIVE_PREMISES.md)
expand the proof interfaces. [ASSETS.json](ASSETS.json) binds all current
package assets and distinguishes original source hashes from edited bytes.
The [note-selection record](NOTE_SELECTION.json) also identifies the
self-contained proof expansions and explicit cost/rank clarifications.
The [main dependency map](../PROOF_SOURCES.md) identifies the external results.

## Finite premises

The PR589 BIT and raw-CU phase families are distinct.

- [PR589 BIT data](finite-data/pr589-bit/) retain the word, frames,
  249-record stream, 32-wire controller, source manifests, bounded-checker
  sources and saved outputs at CrocSwap commit
  `322e0ec764aa7ef7801383feb1f656e460dd8bed`. The
  [attribution record](finite-data/pr589-bit/ATTRIBUTION.md) preserves the
  confirmed contributor lineage and exact legal-material status.
- [Raw-CU data](finite-data/raw-cu/) retain the phase recipe, lowering
  table, width ledgers, checker sources and saved outputs. The unchanged
  word, base controller and upstream notices are reused from
  [the finite-unit bundle](../finite-unit/README.md) at commit
  `2485805a6d47f36ea83ddde6327d453ac82d44dc` with explicit hashes.

Saved outputs are historical finite evidence. They do not establish the
all-size theorem by testing. All-column lifting and asymptotic costs use
the written proofs. Complete Lean verification and independent human
mathematical review remain outstanding.

## Reproduction and licensing

No executable is included. The C++ finite checkers require their self-only
Windows guard, capped at 64 MiB and 10 CPU seconds before input parsing;
a bounded compiler invocation and a wall limit are separately required.
Document and integrity checks do not run those programs.

Original contributions use Apache-2.0 under the project's
[licensing scope](../../../../docs/LICENSING.md); upstream source-specific
terms and notices remain separate. The pinned PR589-specific LICENSE, NOTICE and README are retained as normalized UTF-8 transcriptions; their source URLs, hashes and original-byte limitation are recorded in [the retrieval record](finite-data/pr589-bit/upstream/RETRIEVAL.json). [Third-party notices](../../../../docs/THIRD_PARTY_NOTICES.md)
record the wider source and attribution boundaries.
