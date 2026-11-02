# Scope and dependencies of the research claims

The manuscripts state ordinary polynomial multiplication bounds on
deterministic fixed finite-tape machines. The field is fixed before the
input length varies. Written proofs and named prior theorems supply the
arguments; independent human review and complete formal verification
remain outstanding.

## General fixed-field theorem

The general preprint, version 0.2.2, states
O_q(n log(n+2)^(1301/1302)) over every individually fixed finite field.
Its two branches are:

- For F_(2^s), Theorem 1 of the paired-phase binary preprint, version
  0.2.1, gives exponent 1301/1302 over F2. The general paper's fixed-basis
  lemma uses s^2 serial binary products and O_s(n) coefficient/stream
  work. Binary scratch restoration is charged in O_s(T(n)+n).
- For each fixed odd field, the independent cyclotomic-host construction
  gives exponent 319/320. The exact inequality
  1301/1302 - 319/320 = 491/208320 > 0 supplies the common bound.

Both branches return all 2n-1 ordinary coefficients. Setup, field
conversions, arithmetic, tape movement, decoding and cleanup are charged.
The machine and constants may depend on the fixed field and basis.
Growing-field uniformity and a combined workspace bound are outside the
statements. The odd-field exponent 319/320 is specific to odd characteristic.

The paired-phase binary proof does not invoke the combined general
conclusion. The odd-field proposition is independent of the binary
multiplication theorems and the combined conclusion. The
[combination review](../verification/all-fixed-field-combination-0.2.2.md)
records this dependency split and the fixed-tape wrapper.

## Odd-field proof package

The [native supplement](../papers/01-general/proofs/stronger-odd-20261102/README.md)
supplies the mixed-BIT interchange and odd-ring phase constructions,
their finite premises and the complete host-transfer appendix. The
quotient selector, three-C word, reserve argument and lossless-transpose
reprice retain their documented source pins and notices. The supplement's
version 0.2.1 identity and historical finite evidence are unchanged.

## Baseline companions

The Pascal/Taylor paper states ordinary F2 multiplication in O(n log(n+2))
with its fixed characteristic-two extension corollary. Its finite witnesses
check local algebra and indexing only.

The general O_q(n log(n+2)) baseline combines that Pascal/Taylor theorem
with the historical odd-field proposition, weakened to exponent 1, and a
fixed-basis reduction. Its exact historical inputs remain at the
[pinned prior revision](https://github.com/arpcs/finite-field-polynomial-multiplication/tree/14532be8e044c0f6588b9787a842a96da695769f/papers/01-general).
The stronger current odd proposition also implies the baseline. The
baseline's source dependency does not invoke the combined all-field theorem.

## Controlled-CRT binary construction

The controlled-CRT paper, version 0.1.0-preprint, states exponent 1-2^-38
for ordinary F2 multiplication. It retains its own proof, fixed-extension
corollary, sources and evidence. It supplies the binary branch of earlier
general-paper versions; the version 0.2.2 composition uses the paired-phase
binary theorem instead. These manuscripts share antecedents and are not
counted as independent discoveries of each consequence.

## Excluded research branches

The earlier conditional E8/orthogonal-tree and partial-bank transfers
retain uniform Pascal and full-index packing/restoration hypotheses.
Their smaller numerical exponents are excluded from the unconditional
claims. Open machine interfaces remain stated as hypotheses. Incomplete
formalization is a separate evidence limitation; finite tests and compiled
target definitions do not establish an all-size multiplication theorem.
