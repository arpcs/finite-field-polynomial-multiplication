# All-fixed-field combination, version 0.2.2

2 November 2026. Internal AI-assisted mathematical interface review.

## Statement and inputs

For every individually fixed finite field F_q and fixed basis, ordinary
multiplication of two degree-less-than-n polynomials returns all 2n-1
coefficients in O_q(n log(n+2)^(1301/1302)) deterministic bit time on a
fixed finite-alphabet, fixed finite-tape machine.

The characteristic-two input is Theorem 1 of the paired-phase binary
preprint, version 0.2.1, at immutable revision
`e85bc1f6ca0ec9c13281c94b6a3e88ec2cdb4fc5`. The odd-characteristic input
is Proposition 1 of the general paper, with its unchanged native
supplement and exponent 319/320. Their cited external dependencies retain
their existing scope.

## Charged reduction

For fixed q=2^s, expand f and g in an F2-basis. Fixed-width sequential
scans form s coordinate streams per operand in O_s(n) time. The s^2
binary products are executed serially using fresh operand copies.
Each complete product stream is added to s coordinate accumulators
according to fixed structure constants. Initialization, copying,
coefficient arithmetic, recombination, temporary-stream erasure,
head returns and writing every ordinary output coefficient cost O_s(n).
The basis and structure constants are fixed finite-control data.

The binary calls charge their own arithmetic and movement. Arbitrary
binary scratch is not assumed to have linear size: marking visited tape
intervals and clearing/resetting them costs O(T(n)+n) per call with
constant simulation overhead. The paired-phase theorem already charges
its own cleanup. The complete extension cost is O_s(T(n)+n), with no
additional logarithmic factor, sorting primitive or growing-width lookup.

For odd q, the existing exponent fits the common bound because
1301/1302 - 319/320 = 491/208320 > 0. The fixed secondary logarithms
have already been absorbed in the two component theorem statements.
The machine, alphabet, tape count and constants are fixed before n varies;
they may depend on the field and basis. No growing-field uniformity or
combined workspace bound is asserted.

## Dependency and evidence boundaries

The odd-field proposition does not invoke the binary multiplication
theorems or the combined conclusion. The paired-phase proof does not
invoke the combined general theorem. The fixed-basis reduction therefore
introduces no circular dependency. The older controlled-CRT theorem is
retained as a separate construction and is outside this composition's
premises.

This review checks the combination and its interfaces. It does not
independently certify either full component proof. Complete formal
verification and independent human mathematical review remain outstanding.
No new mathematical executable, finite replay or Lean build was run for
this consequence. Document compilation, visual inspection and hashes
establish their stated presentation and integrity scopes only.
