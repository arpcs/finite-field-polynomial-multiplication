# Status: general fixed-field first-release paper

**Revision:** 0.1.0-preprint, 31 October 2026  
**Main source:** `main.tex`  
**Author:** Árpád Csizmadia, arpad.csizmadia.public@gmail.com

## Claims

- All fixed finite fields: for every fixed \(q\), ordinary multiplication takes \(O_q(n(\log(n+2))^{1-2^{-38}})\) deterministic bit time on the fixed finite-tape model. The binary case is imported from the accompanying *Ordinary Binary Polynomial Multiplication below \(n\log n\)* preprint (`../03-best-binary/main.tex`), including its proved fixed-extension corollary. The odd case is stronger and proved in the odd proposition below; the common all-field exponent is the binary exponent.
- Odd characteristic: for each fixed odd prime \(p\) and fixed \(e\), ordinary fixed-basis multiplication over \(\mathbb F_{p^e}\) takes \(O_{p,e}(n(\log(n+2))^{9999/10000})\) bit time. Its host-transfer and grouped-native proof sources are bundled under `proofs/`, with the current native source snapshot and named movement adapter.
- The fixed-extension reduction is proved explicitly in `main.tex`: expand in a fixed basis, use \(s^2\) prime-field products, then combine with the fixed structure constants and linear basis codecs.

The characteristic-two theorem is cited with its accompanying preprint scope; its all-field use is only through the proved fixed-extension corollary. No combined workspace claim, practical speedup, publication priority, or completed end-to-end Lean formalization is asserted. Full Lean formalization remains unfinished.

## Odd-branch proof audit

An internal AI-assisted source-inspection pass read the current host-transfer proof and the cited native proof sections directly. This does not record a personal proof check by the named human author. The transfer keeps the ordinary endpoint: it starts from \(2n<N<4n\), reconstructs both coefficient CRT components, inverts the affine top map, and uses \(2n-1<N\) to rule out aliasing. It enlarges the coefficient host only after freezing the public generator degree, obtains \(m'D'=\Theta(N)\), and uses the stronger complement density \(O(a^2/L_0^3)\) to pay the complement component. The old-root lift and new-input coefficient map remain distinct.

The odd compiler covers commutative \(\mathbb F_p\)-algebras, including nonreduced algebras. It uses radix 3 for \(p\ne3\) and radix 5 for \(p=3\), proves root differences are units by Bezout identities, retains inverse normalization and subtracts the final cyclotomic block. Its recurrence gives quasilinear circuit size \(O_p(v\log^{16}(2v))\), not linear size. The dirty replay subtracts the second \(FUz\) term to restore arbitrary dirty state; exact-width Toeplitz chunks charge six fixed-kernel convolutions and fit every source, target, and gate port in the original parent.

The same AI-assisted inspection also read the current bundled native snapshot at `proofs/native_odd_source_snapshot.tex.txt`, including `lem:nativedock`, `prop:nativephase`, `lem:nativeselector`, `prop:nativecontrolled`, `prop:nativeCRT`, `lem:CRTphase`, `thm:stage2phase`, and the proof of `lem:nativeparameter`. The larger \(R=2^{O((\log L)^2)}\) host shape follows from the transfer's explicit extension of that proof and the wider dock/phase hypotheses; it is not obtained by citing the narrower polynomial-radix statement alone. The record-width allowance is paid by the opaque suffix. Coupled CRT levels are synchronized over the whole grid, dummy patterns are preserved at completed boundaries, and inverse Fourier normalization includes \((m')^{-1}\).

The named external movement theorem is linked in `proofs/PROOF_SOURCES.md`, with its immutable commit and source hash. The current full odd-native source differs by hash from the version bound in the older completion-audit JSON; this package freezes the current source and does not portray the older audit as hash-matched to these bytes. The saved audit and finite witness are corroborating records, not substitutes for the bundled proofs.

## Fresh fixed finite-unit replay

The [finite-unit bundle](proofs/finite-unit/README.md) includes the exact
22,803-event native word, p16/a7/rank145 controller and published profile
result, all tied to immutable CrocSwap paths and hashes at commit
`2485805a6d47f36ea83ddde6327d453ac82d44dc`. It retains the upstream
contributors' notices and separates historical expected outputs from fresh
execution evidence.

Three bounded C++ checks passed on 31 October 2026 at 01:48:05 UTC:
the native scalar endpoint on all 770 public input columns and 799 outputs;
the base/forward 32-column Laurent identities and 104-port direct geometry;
and the exact composition/rational moment calculation, including all 16 paid
bins and 18 target bins of the public result (66,834 paid jobs and 13,444
productive roles). Source/input hashes, relative commands, compiler
identification and fresh stdout/stderr are published in
[verification/finite-unit-replay.json](../../verification/finite-unit-replay.json)
and [verification/finite-unit/](../../verification/finite-unit/).
Compilation was serialized under a bounded Windows launcher; every checker
installed its 64 MiB/10 CPU-second limits and had a 30-second wall limit.

This internal AI-assisted replay establishes the stated fixed scalar,
controller, geometry and numerical premises. Native frame operators and
all-column lowering, chronological tensor construction, uniform fixed-tape
costs, rounding and the complete asymptotic theorem still require the written
proof and its cited results. No full multiplier execution, independent human
proof review or theorem-level Lean certification is implied.

## Packaging and verification

`proofs/PROOF_SOURCES.md` maps each local source and the external dependency. `audit.json` records historical source identifiers and hashes, destination-copy hashes, and copy edits. The earlier copy/source-inspection stage did not compile the paper or execute the supporting proofs. The final PDF was compiled later, as recorded below. The later fresh finite replay is separately recorded above; its ARTIFACTS.json and public replay receipt identify the exact additional source/data closure. No Lean check or full asymptotic multiplier execution was run for this release. External human proof review remains open.

## Final document packaging

The final PDF uses version 0.1.0-preprint, the supplied public contact, and Apache-2.0 for original project material. The compiler/reference checks and selected-page visual inspection are recorded in verification/paper-builds.json and verification/pdf-layout.json at the repository root. No independent mathematical or full Lean verification is implied.
