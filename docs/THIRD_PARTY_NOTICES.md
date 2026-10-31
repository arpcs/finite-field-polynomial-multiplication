# Sources, attribution and license boundaries

The papers retain their detailed bibliographies and named theorem/algorithm
dependencies. Their presence is not a claim of endorsement or sole originality
for standard towers, cyclotomic hosts, Fourier/CRT maps, finite networks or
proof-assistant machinery.

| Source | Use and boundary |
|---|---|
| OpenAI math preprints, including *Integer multiplication below n log n* (23 September 2026) | Named arbitrary-width interchange and finite-network antecedents. The papers cite the relevant lemma and source pin. The [upstream repository](https://github.com/openai/math) uses Apache-2.0. |
| Harvey and van der Hoeven finite-field multiplication papers | Published polynomial-arithmetic and cyclotomic-host inputs, with their actual hypotheses and machine models. No entire upstream source tree is vendored. |
| Harvey, van der Hoeven and Lecerf; Harvey's October 2026 discussion | Earlier fixed-field bounds and current problem context. The 2019 unconditional bound and 2022 conditional theorem are distinguished; no endorsement or review of these manuscripts is implied. |
| Cantor; Gao and Mateer; Bostan and Schost; Liu | Classical and more recent additive evaluation, Taylor-expansion and structured interpolation background. These are methodological antecedents, not imported fixed-tape power-saving theorems. |
| Karatsuba and Ofman; Schönhage and Strassen; Brent and Zimmermann | Classical recursive multiplication and integer/modular arithmetic used by the local constructions. Books and articles are cited, not vendored or relicensed. |
| Alman; van der Hoeven and Larrieu | Fixed-matrix lookup-table algorithms and the Frobenius FFT. Their actual RAM or finite-tape cost conventions are described individually. |
| CrocSwap integer-mult-bounds contributors | Attributed finite geometry, recursive/compiler and accounting antecedents where used. Its [source repository](https://github.com/CrocSwap/integer-mult-bounds) uses Apache-2.0. Credit is retained in the paper references. |
| platypii/integer-mult-bounds-lean | The named stage-two interchange theorem and exact ordinary-bit boundary at commit fefd699f9389af961046997796261333539e5909. The [repository](https://github.com/platypii/integer-mult-bounds-lean) uses MIT; the reference license text is in LICENSES/MIT.txt. Its complete source/proof tree is not copied here. |
| Other authors listed in each bibliography | Prior algebraic, algorithmic, field, adder and permutation results; use is limited to the cited statement or adaptation identified in the paper |
| J. A. Sussman | Related exact-complex RAM results and recursion ideas recorded in the native supplement. The selected odd transfer imports the separately named stage-two theorem, rather than Sussman's end-to-end bounds. |
| Dehaene and De Moor; community coordinate constructions | Classical linear/quadratic Clifford descriptions are credited separately from the specific community-derived coordinate construction. The native supplement retains the latter's individual attribution, including icekylinx. |
| OpenAI Codex | Known software assistance is identified in each paper and AI_USE.md. Software use is separate from mathematical source dependence; AI systems are not listed as paper authors. |

The native and proof-source supplements retain their original citations
and identify the AI-assisted derivations they document. Historical audit language is not a new external review or
proof-assistant receipt. Paper audit files identify originals and edits;
the released hashes identify the exact current copy.

The citation audit uses OpenAI source revision
`4eaee87548250b2682affda7d05d947c05554bae` and the recorded CrocSwap
revision `2485805a6d47f36ea83ddde6327d453ac82d44dc`. The native snapshot
retains its historical bibliography intact, including sources for separate
RAM and conditional branches. The main papers identify the narrower
dependencies used for the selected claims. A citation revision and a
historical inspected-text hash are separate provenance records.

The general paper's
[finite-unit bundle](../papers/01-general/proofs/finite-unit/README.md)
also copies three fixed mathematical inputs from that exact CrocSwap
revision: `research/p104-helper470-twin-rung-removal/WORD.json.gz` (complete
decompressed payload), that package's `RESULT.json`, and
`research/joint-helper-lattice/CONTROLLER.json`. The latter is the exact
p16/a7/rank145 controller, distinct from the p17 controller in the upstream
query-thinned package. ARTIFACTS.json records original/current hashes,
immutable paths and the compressed/decompressed hash distinction. The
Apache-2.0 license, full upstream NOTICE and three unchanged attribution
README files are retained under the bundle's `upstream/` directory.

Cinna Davis supplied the base productive-controller lineage, and Ali Romman
supplied the forward wrapper and verifier lineage. DreamingOfClouds supplied
the selected helper-470 native-word edit, following PR #5907 and the PR #5827
verifier chain and their earlier contributors. The upstream notes credit
OpenAI Codex assistance to the verifier/wrapper work and Claude Opus 5.5
through Claude Code to the native-word package. These retained credits are
separate from this project's small C++ replays, developed with substantial
OpenAI Codex assistance. The included source notes preserve the fuller
community lineage and its stated framework assumptions.

The fresh [finite replay record](../verification/finite-unit-replay.json)
and text outputs record exact fixed endpoint/controller/geometry/profile
checks. They do not assert independent human approval, acceptance of the
upstream conditional end-to-end claims, or formal verification of this
project's asymptotic multiplication theorem.

Preserve any source-specific copyright, license or NOTICE attached to copied
material. The top-level Apache-2.0 grant covers only rights the relevant
contributors can grant; it does not silently replace upstream terms.
Attribution corrections are welcome through the contact in SUPPORT.md.
