# General fixed-field polynomial multiplication

**Revision:** 0.2.1, 2 November 2026  
**Status:** research preprint  
**Author:** Árpád Csizmadia, arpad.csizmadia.public@gmail.com

## Statements

For each fixed odd prime p and fixed e>=1, the written construction gives
ordinary degree-<n polynomial multiplication over F_(p^e) in
O_(p,e)(n log(n+2)^(319/320)) deterministic bit operations on a fixed
finite-tape machine. It returns all 2n-1 ordinary coefficients in a fixed
basis. The more precise bound has leading exponent 0.996874195 and a
fixed secondary power of loglog n. The positive margin 805/10^9 absorbs
that power in the stated bound.

The common all-fixed-field exponent remains 1-2^-38, using the accompanying
characteristic-two theorem and its fixed-extension corollary. The sharper
odd-field exponent is not asserted in characteristic two. Constants may
depend on the fixed field and basis. Growing-field uniformity and a combined
workspace bound are outside the statements.

## Proof dependencies

The PDF contains the [host-transfer appendix](proofs/stronger-odd-20261102/host-transfer.tex).
The [native supplement](proofs/stronger-odd-20261102/README.md) supplies the
interchange and odd-ring phase proofs, their supporting arguments and the
distinct PR589 BIT and raw-CU finite premises. Its source-selection record
distinguishes the edited publication supplement from the original research
source. The [dependency map](proofs/PROOF_SOURCES.md) identifies the named
external results and their exact interfaces.

The external movement input is the pinned
`IntegerMultBounds.MathlibTM2.M8.Stage2Machine.Bound.uniform_bound` theorem.
Harvey and van der Hoeven supply the unconditional cyclotomic host and roots;
classical Schönhage–Strassen arithmetic supplies small-ring and complementary
products. These operations do not use the new multiplier recursively.

The transfer accounts for the actual quotient selector and unit witnesses,
three-C shear, Fourier factorization, exact-width printer, complete-rectangle
routing, both coefficient-CRT components, diagonal preparation and application,
pointwise ring products, inverse normalization, ordinary reconstruction, and
serial fixed-basis reduction.

## Evidence and limitations

Internal AI-assisted source review identified no blocking defect under the
named imports. Revision 0.2.1 makes the cyclotomic root map's well-definedness,
identity schedule padding and pointwise-product invoice explicit. Complete
Lean verification and independent human mathematical review remain outstanding.

Saved finite-check outputs establish only their stated finite premises. They
are historical records, not fresh runs or tests of the complete asymptotic
algorithm. Document-build and layout receipts associate the PDF with its
sources and record presentation checks; they do not certify the mathematics.

The PR589-specific LICENSE, NOTICE and README are archived from their pinned
GitHub source views as normalized UTF-8 text. The retrieval record identifies
the source URLs, archived hashes and normalization; original network-byte
identity was not verified. The older sibling notice remains a separate source.

The published 0.1 sources and PDF remain preserved at the
[immutable earlier revision](https://github.com/arpcs/finite-field-polynomial-multiplication/tree/14532be8e044c0f6588b9787a842a96da695769f/papers/01-general).
