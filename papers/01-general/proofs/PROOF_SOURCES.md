# Odd field proof sources and dependencies

The research preprint is version 0.2.1, dated 2 November 2026.
Its odd-field exponent is 319/320. The complete host-transfer appendix is
compiled into the PDF; the supporting native source and finite premises
are included for review. These written proofs use named external results;
they are not inferred from finite test counts or a Lean component total.

## Current proof path

1. [host-transfer.tex](stronger-odd-20261102/host-transfer.tex) proves the
   stronger ordinary fixed-field transfer: exact quotient selector and
   units, local Fourier words, physical native calls, full cost invoice,
   both coefficient-CRT components, ordinary output and fixed extensions.
2. [The stronger proof package](stronger-odd-20261102/README.md) contains
   the edited `native-source.tex.txt` and a `SOURCE_SELECTION.json` record.
   The latter identifies the original research source, retained proof blocks,
   editorial changes and the distinct hash of the publication supplement.
   Its used path runs through `lem:pr589nativebit`,
   `lem:bitwordstrictification`, `lem:finitebitflow`,
   `thm:finitebitcompiler`, `prop:delayedbitcover`,
   `thm:mixedbitswap`, `lem:strongerphasemoment`,
   `prop:stripedcompiler` and the phase-only statement
   `thm:mixedbitinteger`. The native dock/shuffle/controlled/CRT proofs are
   repriced by the explicit lossless binary-transpose argument. The older
   shuffle exponent alone is not sufficient for this improvement.
3. The same package supplies the ring-valid Fourier factorization,
   exact-width dyadic/DAG printer, short top-map proof, three-C word and
   service contracts. Its supporting arguments fix one moment
   exponent, define zero-rank complements and give the general reserve
   calculation. Its asset manifest records exact source and copy hashes.
4. The PR589 BIT inputs at CrocSwap commit
   `322e0ec764aa7ef7801383feb1f656e460dd8bed` are separate from the raw-CU
   phase family. The package maps both, retaining contributor notices and
   distinguishing written all-column proofs from finite replay results.
   Where exact phase files already occur in [finite-unit](finite-unit/README.md),
   those byte-identical copies can be reused with explicit hashes.

## Named external results

The non-elementary movement input is
[Stage2Machine.Bound.uniform_bound](https://github.com/platypii/integer-mult-bounds-lean/blob/fefd699f9389af961046997796261333539e5909/IntegerMultBounds/MathlibTM2/M8/Stage2Machine/Bound.lean),
at immutable commit `fefd699f9389af961046997796261333539e5909`.
Canonical source SHA256:
`97bb4fb5a883e0c90c53173355cf310ac56e2d28860679a13b2854f91cd2ad2a`.
[The preserved adapter](PINNED_STAGE2_BINARY_MOVEMENT_BRIDGE_20261030.txt)
explains its headers, encodings, q-power pads, complete spectators and
cleanup. It is an existing cited theorem, not an open mathematical
hypothesis because its Lean closure was not rebuilt locally.

The unconditional host/root inputs are HvdH Propositions 3.4 and 3.8:
[author manuscript](https://www.texmacs.org/joris/cyclomult/cyclomult.pdf).
Classical Schönhage–Strassen multiplication and standard monic polynomial
arithmetic pay setup, pointwise coefficient products and the complement.
The new multiplier does not call itself to supply those operations.

## Historical 0.1 sources

The following files remain unchanged and support the older odd exponent
9999/10000: `odd_cyclotomic_host_transfer.tex`,
`odd_grouped_native_transfer.tex`, `native_odd_source_snapshot.tex.txt`,
and the dated `ODD_CYCLOTOMIC_*.txt` derivation/audit records. The old native
snapshot is 380,858 bytes with SHA256
`25d01aad610d4d2c521d3824dd7df534f491b6fdd30d404b149bdedd4b0159041`.
It is not the stronger source used by this draft. The old audit record
is preserved at the [pinned 0.1 source revision](https://github.com/arpcs/finite-field-polynomial-multiplication/tree/14532be8e044c0f6588b9787a842a96da695769f/papers/01-general).

The [phase finite-unit bundle](finite-unit/README.md) and its
[31 October replay receipt](../../../verification/finite-unit-replay.json)
remain exact historical evidence for the stated finite premises. Their
fresh-at-that-time outputs are not relabeled as new runs for this update.

## Verification status

The current argument has internal AI-assisted source review. Complete
Lean verification and independent human mathematical review remain open;
the package asserts neither publication priority nor a practical speedup.
Document builds and hashes establish source association and integrity,
not mathematical acceptance. The separate integer consequence of the
native compendium is outside this paper's selected claim.
