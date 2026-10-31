# Claims selected for the first release

**31 October 2026.** The owner selected four related papers and excluded results
that still rely on unproved machine interfaces. The selected claims have
written proof routes with their suppliers constructed in the paper or
identified as cited prior theorems. This is not independent mathematical
certification or an exhaustive novelty review.

## General finite-field baseline

The O_q(n log(n+2)) companion under `papers/04-general-nlogn` treats each
individually fixed finite field on the deterministic fixed finite-tape bit
model. Its characteristic-two prime-field input is the accessible
Pascal/Taylor binary theorem in `papers/02-simple-binary`. For each fixed odd
prime, it uses Proposition 1 of `papers/01-general`, weakened from exponent
0.9999 to the baseline exponent 1. For a fixed degree-e extension, a fixed
basis uses e^2 prime-field products and linear-cost coefficient conversion
and combination. Constants may depend on the chosen field.

This baseline route does not invoke `papers/03-best-binary` or the strict
characteristic-two saving. It uses only the odd-field branch of the stronger
general paper, not that paper's combined all-field theorem.

## Stronger general finite-field companion

For each fixed odd field, the cyclotomic-host derivation states exponent
0.9999, using the bundled native construction and named stage-two interchange
theorem. Its proof explains the broader native-parameter range instead of
claiming it follows verbatim from the narrower earlier lemma statement.

The principal binary result and constant-cost fixed-extension reduction,
combined with that odd-field branch, yield the common exponent theta=1-2^-38
for every fixed finite field. Since 0.9999<theta, the odd-field bound fits
the common bound. The field is fixed before input length varies. No common
exponent 0.9999 for all fields is asserted by this release.

## Accessible binary baseline companion

The corrected Pascal/Taylor construction states O(n log(n+2)) time over
F2. It separates its exact evaluation/product/decoder reduction from the
binary tensor supplier and includes the cited arbitrary-width interchange
input. The finite witnesses test local algebra and indexing only.

This paper was selected for proof structure and exposition rather than a
claim of a better exponent than the principal binary result.

## Principal characteristic-two paper

The controlled-CRT construction states ordinary F2 multiplication in
O(n (log(n+2))^theta), theta=1-2^-38, on a fixed finite-alphabet machine
with a fixed finite number of sequential tapes. Its fixed-extension
corollary allows constants to depend on the extension degree.

Its main text handles ragged and controlled tensor permutations, balanced
CRT merges, generator costs, coefficient enlargement, Fourier slots and
ordinary coefficient reconstruction. Its appendices supply the finite word,
interchange, native endpoint and local Fourier/compiler arguments. The
external host, classical arithmetic and interchange antecedents are cited
precisely. These are prior theorem dependencies, not an assertion that an
unimplemented new service is available.

The four papers organize baseline and stronger claims and their proof
dependencies; they are not counted as four independent discoveries.

## Excluded research branches

The more aggressive binary E8/orthogonal-tree and partial-bank transfers
still retain uniform Pascal and full-index packing/restoration hypotheses
in the inspected source. Their smaller numerical exponents are not included
as unconditional results. The latest conditional draft is preserved outside
this repository. Its assumptions were not removed while retaining its bound.

Lean remains unfinished for the selected papers. That is distinct from the
open mathematical interfaces that excluded the other branches. Conversely,
a cited prior theorem does not become an unproved hypothesis merely because
this package did not independently rebuild its Lean dependencies.
