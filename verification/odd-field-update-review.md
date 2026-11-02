# Technical review of the odd-field revision

2 November 2026. Revision 0.2.1.

## Mathematical scope

The reviewed path is ordinary degree-<n polynomial multiplication over
F_(p^e), for each individually fixed odd prime p and fixed positive e,
with all 2n-1 coefficients returned in a fixed basis on fixed finite tapes.
The selected exponent is 319/320; the leading exponent is 0.996874195 with
fixed secondary logarithms. The all-field and binary exponent remains
1-2^-38. No new integer, growing-field or workspace theorem is asserted.

The argument uses the named Stage2 interchange theorem, the unconditional
Harvey–van der Hoeven host and roots, and classical Schönhage–Strassen
arithmetic. Internal AI-assisted source review found no blocking defect
under these imports. This assessment is not independent human mathematical
review or a complete formal proof.

## Explicit additions

1. The root transport now proves that U_0 -> U^J is well-defined. With
   alpha=alpha_0 J squarefree and gcd(J,alpha_0)=1, the identity
   Phi_(alpha_0)(X^J)=product_(d|J) Phi_(alpha_0 d)(X) gives the required
   cyclotomic divisibility. The resulting unital homomorphism preserves
   the principal-root character sums.
2. Shorter local matching schedules are padded by the proved zero-weight
   identity words before tensor composition. All ports and diagonal slots
   remain present through each completed boundary.
3. The pointwise data stage is separately charged: at most M products in B,
   each costing O_p(D polylog L_0), give O_p(MD polylog L_0). Since
   MD=Theta(n) and L_0=Theta(log n), this is
   O_p(n (loglog(n+4))^K) for a fixed K, below the leading term.

Relative to the preceding 0.2 manuscript, these additions make the written
interfaces and invoice explicit without changing its claimed exponent or
introducing a new arithmetic primitive. The complete update improves the
published 0.1 odd exponent from 9999/10000 to 319/320.

## Source and presentation

The selected native supplement retains the phase/interchange proof path
and its required routing, CRT and finite-source arguments. The combined
integer/phase statement is restated as phase-only. SOURCE_SELECTION.json
records the original research hash and the separately hashed edited source.
Earlier review hashes identify their original snapshots, not edited bytes.

The manuscript and publication notes retain mathematical arguments,
source identities and evidence limits. Public author/contact
information and upstream attribution are retained.

## Evidence and verification limits

The general PDF was rebuilt under the serialized document guard and all
16 final pages were visually inspected. The build has no overfull boxes or
undefined references. Source hashes and PDF associations are recorded in
the separate build, layout, asset and manuscript audit records.

No new finite experiment, Lean job or mathematical executable was run for
this revision. Existing finite reports retain their historical dates and
limited scopes. Full theorem-level formalization and independent human
mathematical review remain outstanding. The PR589-specific LICENSE, NOTICE
and README are archived from their pinned GitHub source views as normalized
UTF-8 text, with source URLs, current hashes and an explicit original-byte
limitation. They are separate from the older sibling notice.
