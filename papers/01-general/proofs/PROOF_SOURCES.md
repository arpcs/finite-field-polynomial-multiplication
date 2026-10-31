# Proof source and dependency map

This folder contains the actual sources needed to inspect the odd-field proof. The paper is not advertised as an isolated self-contained derivation of every machine service: the current odd finite-ring source and the named upstream interchange theorem are explicit dependencies, and both are supplied or linked here.

## Local proof sources

- `odd_cyclotomic_host_transfer.tex` contains the full odd-field cyclotomic-host proposition and proof: host enlargement and density, fixed odd-characteristic compiler, arbitrary-dirty replay, exact-width Toeplitz chunking, signed Newton factorization, growing-ring shear implementation, coupled CRT transforms, both coefficient components, ordinary reconstruction, and the final cost inequality.
- `odd_grouped_native_transfer.tex` contains the grouped native service proof used by that transfer: odd-field matching service, five-call generator, grouped padding and wide-record argument, and the fixed-kernel tensor theorem. It is excerpted through the end of `thm:oddgroupedkernel`; later power-log results that the cyclotomic proof does not use are not included.
- `native_odd_source_snapshot.tex.txt` is the complete current monolithic finite-ring proof source. It includes the named native dock, phase, selector, controlled permutation, coupled CRT, CRT Fourier identity, Stage2 phase transfer, parameter proof, and the lower-level router, interchange, phase, and recovery lemmas they reference. It is a separate source snapshot, not included into the general paper as an appendix.
- `PINNED_STAGE2_BINARY_MOVEMENT_BRIDGE_20261030.txt` states exactly how the upstream interchange theorem is adapted to arbitrary-width records. The upstream theorem is linked at its immutable commit and its source hash is given in that bridge.
- The two `ODD_CYCLOTOMIC_*.txt` files are dated derivation/audit records. They support navigation and record bounded evidence; neither is substituted for the TeX proofs above.
- [`finite-unit/README.md`](finite-unit/README.md) maps the fixed finite word, controller and profile checks used by the native phase construction. It supplies the checkers, exact inputs, historical reports, upstream notices and a bounded reproduction command. [`ARTIFACTS.json`](finite-unit/ARTIFACTS.json) records the local hashes and immutable upstream source paths.

## Finite proof premises and how to inspect them

The selected odd-field phase argument reaches the finite unit through
`thm:stage2phase`, `thm:endpointphase`, `thm:mixedphase` and
`prop:recordunit` in the native snapshot. Its scalar endpoint and profile
equalities are proof premises, rather than optional timing examples.
The corresponding artifact bundle separates three checks:

| Checker | Finite premise |
|---|---|
| `native_scalar_record_probe.cpp` | Exact rational basis-column replay of the saved native word, including the main endpoint, independent helpers and cleared owned roles |
| `controller_record_probe.cpp` | The fixed controller and boundary identities, all-forward wrapper geometry and negative controls used to assemble the productive unit |
| `record_rate_probe.cpp` | Every paid/target profile bin and the rational moment inequalities for the stated conservative rate |

The fixture paths, hashes, expected results and contributor credits are in
the artifact manifest and bundle README. The controller input is the exact
historical p16/a7, rank-145 fixture; the differently parameterized p17
controller is not substituted for it. The original native snapshot remains
unchanged, with these records providing the missing artifact map.

The written frame-lifting, lowering and compiler arguments connect these
finite identities to arbitrary column counts and the asymptotic algorithm.
Replaying the checks does not itself prove those general arguments or the
complete multiplication theorem.

## Dependency boundary

The non-elementary external machine input is
[`IntegerMultBounds.MathlibTM2.M8.Stage2Machine.Bound.uniform_bound`](https://github.com/platypii/integer-mult-bounds-lean/blob/fefd699f9389af961046997796261333539e5909/IntegerMultBounds/MathlibTM2/M8/Stage2Machine/Bound.lean), at commit `fefd699f9389af961046997796261333539e5909`. The bundled adapter note records the exact source SHA-256: `97bb4fb5a883e0c90c53173355cf310ac56e2d28860679a13b2854f91cd2ad2a`.

The host/roots are from Harvey and van der Hoeven's primary cyclotomic paper: [author PDF](https://www.texmacs.org/joris/cyclomult/cyclomult.pdf). The proof uses the unconditional fixed-prime host result and does not use their separately conditional finite-field theorem.

## Source-version note

The copied `native_odd_source_snapshot.tex.txt` is the current source byte-for-byte at the time of packaging. Its hash differs from the older completion-audit source binding. Therefore that older 26-item audit is not treated as a hash-matched audit of the current native source. The current cited proof sections were read directly, and the exact current source hash is frozen in `../audit.json`. This bundle does not claim external human proof review, a Lean proof of the complete algorithm, or publication priority.
