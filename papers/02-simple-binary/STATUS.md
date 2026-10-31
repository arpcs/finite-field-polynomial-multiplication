# Status: focused first-release SIMPLE characteristic-two paper

**Selected source:** `output/finite-field-polynomial-multiplication/papers/03-binary-pascal-taylor/` (corrected Pascal/Taylor binary branch), not the Artin–Schreier alternative. Release edits, including the selector proof correction below, are described in `audit.json`.

## Exact claim

For each input length n, ordinary multiplication of two degree-<n polynomials in the fixed field F2, in ascending binary coefficient representation, outputs 2n-1 coefficients in O(n log(n+2)) steps on one deterministic finite-alphabet multitape Turing machine with a fixed finite number of one-dimensional tapes. The tape count and constants are fixed independently of n, although the source explicitly makes no practical-speed or two-tape claim. The manuscript also gives a constant-coordinate reduction for every individually fixed F_(2^s), with s fixed independently of n. It does not claim a uniform varying-field theorem or an odd-characteristic theorem. For either fixed binary operand, the ordinary binary transpose is included.

## Why this branch

The written proof has a clean two-theorem dependency chain. First, the exact reduction theorem builds evaluation, pointwise products, a residue decoder, ordinary transposes, and the complete bit-cost boundary from a uniform binary tensor bound. Second, the tensor theorem proves the needed strict height saving with an explicit finite F16 word and locally proved routing/role machinery. This isolates the sole external algorithmic premise. The Artin–Schreier paper instead integrates a quadratic tower, native scalar arithmetic, a recursive coefficient-one evaluation recurrence, sparse boundary charts and endpoint products into its main proof, with more interfaces to audit. Selection is based on dependency structure and cost proof, not manuscript length.

## Proof obligations and observed limits

The reduction’s central obligations are the explicit cyclotomic field/chart construction; prefix flag and sparse radix extraction; sibling Taylor evaluation; child-field scalar multiplication and its actual binary transpose; the balanced normalized recurrence; and the quotient-ring residue decoder with its degree cutoff, field trace Grams, affine-grid conjugates, raw input/output representation changes and fixed-operand adjoint. Its cost accounting prices evaluator/transposes at O(b D K), pointwise products/scalar actions at O(N_K K^rho), Grams at O(bD), and representation changes at O(N_K K^gamma), where K=Theta(log n), D=Theta(K), and N_K=Theta(n). These fit O(n log n).

The tensor obligation is a uniform H2^(tensor t) action on arbitrary D-bit payload, including shape descriptors, layouts, role routing, dirty scratch, setup and cleanup, in O(2^t D t^beta) for a fixed beta<1. The finite-word appendix derives the specific F16 word; the role appendix supplies the local scalar schedule, frame invariant, role labels, directional-child count and fixed-tape stack implementation. Bounded C++ witnesses corroborate finite identities only and do not implement the asymptotic machine.

The source’s final internal verification record reports no remaining local mathematical gap after its listed repairs. This is an audit statement, not an independent certification by this packaging pass. The precise external dependency is OpenAI, *Integer multiplication below n log n*, 23 September 2026, Lemma 12 (arbitrary-width equal-chunk interchange), Section 4; the source’s exact GitHub source pin is retained in `references.tex`, with a local inspected-text SHA-256 recorded in `evidence.tex`. No other external multiplication algorithm is used as an oracle. The external lemma itself, the manuscript’s adaptation, and the full asymptotic construction have not been externally validated here. There is no external peer review, proof-assistant certification, or priority claim. Lean formalization remains unfinished and is planned for a later update.

## Packaging and provenance

`main.tex` is self-contained relative to its local TeX inputs. Two bounded finite witness programs, their fixture/header, historical JSON receipts and a guarded reproduction script are included under `witnesses/`. `evidence.tex` identifies the receipt dates and limits their role. The other finite witnesses, review packet, archived drafts and PDFs were not copied. `audit.json` lists every copied file, its original workspace-relative path, destination, original SHA-256, and any editing scope. The original paper directory remains intact. The final release PDF is compiled separately; source/PDF hashes are recorded under ../../verification/. These simple-binary witnesses were not rerun for this release, and no Lean check was run.

## AI-assisted adversarial reading performed for this release

An internal AI-assisted source-inspection pass directly checked the main displayed interfaces: the radix/Taylor proof’s boundary identities; the decoder’s coefficient cutoff and three-conjugate residue pairing; the formula converting it to the ordinary binary transpose; the finite F16 projector/commutator word and its final H2 tensor factor order; and the finite role appendix’s eight-update scalar schedule, dirty-scratch restoration, signed endpoint correction, and the distinction between direction norm and signed phase type. It also read the packed opaque-record shear’s key invariant/correction construction and the top-level tensor recurrence and payload layout. This pass reported no concrete local algebraic counterexample or sign inconsistency in those inspected interfaces. It does not record a personal proof check by the named human author.

This is a focused AI-assisted adversarial reading, not a fresh exhaustive proof of every routing sublemma or tape simulation, independent human peer review, or formal verification. The inspection did not independently establish the external OpenAI Lemma 12 interchange theorem; the argument relies on the cited prior theorem and the written local tape-cost arguments. The saved `review/FINAL_VERIFICATION.md` is the source packet’s internal audit record and should not be described as independent human verification.

## Final document packaging

The 31 October PR review corrected the dirty-selector proof in `tensor.tex`:
each completed `T_Z` preserves the active mask, while paired-source values
are preserved at completed target-only `L_Q` boundaries. Temporary source
changes inside the inner cancellation do not affect the outer argument.
The lemma and complexity bound are unchanged. The PDF was rebuilt and its
corrected proof page was visually inspected.

The final PDF uses version 0.1.0-preprint, the supplied public contact, and Apache-2.0 for original project material. The compiler/reference checks and selected-page visual inspection are recorded in verification/paper-builds.json and verification/pdf-layout.json at the repository root. No independent mathematical or full Lean verification is implied.
