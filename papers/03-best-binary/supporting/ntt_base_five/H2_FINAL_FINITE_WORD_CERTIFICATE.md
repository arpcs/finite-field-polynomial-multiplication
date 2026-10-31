# Final finite F16 word certificate for `H2 tensor H2`

Proof-only audit, 30 October 2026. This note rechecks the explicit positive
word in `EXPLICIT_F16_H2_POSITIVE_WORD.md` and states exactly what it proves.
The accompanying C++ witness was inspected but not executed in this audit.

## Algebraic statement and convention

Let `E=F2[t]/(t^4+t+1)`, `eta=t^2+t`, and
`A=(eta I+eta^2 J_3) direct-sum [1]`, where `J_3` is the all-ones
3-by-3 matrix. Let `H2=[[1,1],[1,0]]` over F2. There is a word in
forward `A` and invertible monomial 4-by-4 matrices over E whose matrix,
under column-vector convention and rightmost-first composition, is
`H2 tensor H2`. It contains exactly 384 forward `A` letters and 392
monomial letters (776 letters total). This is an exact finite-dimensional
identity; by itself it is not a tensor-rank saving or a complexity result.

The quartic is irreducible: it has no F2 root and its remainder modulo the
only irreducible quadratic `t^2+t+1` is 1. Thus E has 16 elements.
Reduction by `t^4=t+1` gives `eta=t^5=t^2+t` and
`eta^2+eta+1=0`. Put `a=eta^2`, `b=eta`; then `ab=1`, and

```text
A_3 = [[1,a,a],[a,1,a],[a,a,1]],   A_3^2 = [[1,b,b],[b,1,b],[b,b,1]],
```

so `A^3=I` and `A^{-1}=A^2`. The entries `t`, `t+1`, and `t^2+t+1`
are nonzero, as required by the divisions below.

## Construction, factor families, and A counts

Write `e_i` for standard columns and `E_ij=e_i e_j^T`. Let

```text
u=(1,a,a,0)^T,  v=(1,b,b,0)^T,  P=A E11 A^-1=u v^T.
```

Since `v^T u=1+ab+ab=1`, `P^2=P`. For
`D=diag(t,1,t+1,1)`, set `Q=DPD^-1=x0 y0^T`, where

```text
x0=(t,a,a(t+1),0)^T,  y0=(1/t,b,b/(t+1),0)^T.
```

The dot products are `v^T x0=0` and
`y0^T u=1/t+1+1/(t+1)=kappa`, with
`kappa=(t^2+t+1)/(t(t+1)) != 0`. Therefore `PQ=0` and
`QP=kappa*x0*v^T`.

For idempotents `P,Q` with `PQ=0`, direct expansion gives

```text
[I+cP,I+dQ] = I + cd/(1+c) QP,
```

when the inverses exist. Indeed `(I+cP)^-1=I+c/(1+c)P`; multiply the
four factors and use `P^2=P`, `Q^2=Q`, `PQ=0`, and `QPQ=0`.
Take `c=d=eta^2`, so `cd/(1+c)=eta^4/(1+eta^2)=1`, and define

```text
G=A diag(eta,1,1,1) A^-1=I+eta^2 P,
H=D G D^-1=I+eta^2 Q.
T0=G H G^-1 H^-1=I+kappa*x0*v^T.
```

`G,H,G^-1,H^-1` each use three forward A letters after replacing every
`A^-1` by `A^2`; hence `T0` uses 12.

The remaining exact rank-one identities are:

```text
B=diag(1,eta,eta,1), x=(t,1,t+1,0)^T, w=(1,1,1,0)^T,
T1=B T0 B^-1=I+kappa*x*w^T.                         A count 12

T2=T1 P12 T1 P12^-1
  =I+kappa*(t+1)*(e1+e2)*w^T.                       A count 24

D3=diag(1,1,eta,1),
T3=T2 D3 T2 D3^-1
  =I+kappa*(t+1)*eta*(e1+e2)*e3^T.                 A count 48

D1=diag(eta,1,1,1),
T4=T3 D1 T3 D1^-1=I+kappa*(t+1)*E13.              A count 96

mu=kappa*(t+1),
T5=diag(mu^-1,1,1,1) T4 diag(mu,1,1,1)=I+E13. A count 96
```

For `T2`, the second rank-one row is `w^T P12`; its pairing with `x`
is zero and the two columns sum to `(t+1)(e1+e2)`. For `T3`, both
cross-pairings vanish and the rows sum to
`(1+eta^-1)e3^T=eta e3^T`. For `T4`, the cross-pairings vanish and
the column sum contributes `1+eta=eta^2`, yielding the displayed
coefficient. These verify each commutator identity, not just its
nonvanishing. All conjugating matrices in these steps are invertible
monomial matrices. Permuting coordinates conjugates `T5` to every
`Uij(1)=I+Eij`, without changing its 96-A count.

Now `H2=U S`, with `U=I+E12` and S the 2-coordinate swap. In the
ordered four coordinates `(00,01,10,11)`, let
`Pfirst=(1 3)(2 4)` and `Psecond=(1 2)(3 4)`. The two disjoint
elementary matrices for the first and second tensor axis are respectively
`U13 U24` and `U12 U34`. Rightmost-first composition gives

```text
M4 = U13 U24 Pfirst U12 U34 Psecond
   = (H2 tensor I2)(I2 tensor H2)
   = H2 tensor H2.
```

The first axis uses two 96-A words, as does the second, for 384 A calls.
All other factors are monomial, including the two wire permutations.
This proves the finite word identity and count symbolically.

## Binary map, transpose, and witness scope

The target matrix has F2 entries, so its 16-dimensional binary map is
exactly `H2 tensor H2` in the indicated coordinate order. It is symmetric;
therefore the **complete** word's ordinary binary transpose equals the
same target. The transpose of a product reverses factor order and
transposes each factor; no claim is made that each F16 monomial letter is
itself binary-symmetric. The source witness explicitly constructs the
reversed literal letter transposes, compares against the binary transpose,
and checks all 256 basis input/covector pairings. It also checks the
projectors, successive rank-one identities, all four Uij conjugates,
monomial status of non-A letters, target factor order, and the stated
counts. It contains fixed-size F16 and 16-bit matrices only, with a
64-MiB/10-CPU-second Windows job guard before field algebra. These are
bounded corroborations; the algebra above is the proof for the identity.

## Extension to binary payload lanes

For any D-bit payload lane, identify a fixed number of its bits with
F16-coefficient coordinates (groups of four, padding a final partial
group). Each fixed F16 scalar multiplication is a fixed 4-by-4 binary
linear map, hence costs O(1) per group. More importantly, after composing
the word, its matrix is the F2 matrix `H2 tensor H2`; it acts on each
payload bit by that same matrix and does not mix distinct payload bits.
Thus applying the finite word to F16-valued records implements the desired
binary layer on arbitrary binary payload, with a constant factor in D.
The ordinary transpose on the full binary payload space is the same target
layer, since `M4^T=M4`.

For a tensor power of the local four-coordinate alphabet, the cited
internal-payload argument supplies exponentially wide opaque records from
spectator axes. Its address width remains O(h), while record width includes
the remaining payload; fixed-degree scalar work, record copying, and
whole-record rotations are charged proportional to payload volume. The
monomial letters have the form `D P_pi`: on h digits they route addresses
by the local permutation and multiply each record by the product of h
fixed diagonal scalars. The cited routing ledger prices the address map,
inverse/transpose map, scalar products, and record operations. The A
letters are handled by the separate active/idle sector and ternary-role
router, not by the finite word construction.

Accordingly, the algebraic payload extension is proved for arbitrary D.
The asserted strict-sublinear tensor-height implementation is conditional
on the imported equal-chunk interchange theorem, opaque-record routing
ledger, dirty-selector/prefix correction, and finite ternary role-network
contracts cited in `NEW_LUNA_INTERNAL_PAYLOAD_H2_TENSOR_COROLLARY.md`.
The finite word certificate does not prove those machine/tape contracts,
and it does not close the separate growing-field scalar/convolution
ledger or imply unconditional ordinary finite-field multiplication in
O(n log n).
