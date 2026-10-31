# Active-rank recurrence certificate for the ternary role network

30 October 2026. Independent derivation of the finite role/frame input to the
H2 active-rank recurrence. This checks the algebraic frame interfaces, the
exceptional endpoint child, and the exact rank ratio. The fixed-tape routing
and interchange contracts remain imported; this note does not establish an
ordinary multiplication bound.

## Phase factors and nondegenerate frames

Work over `F_4=F_2[w]/(w^2+w+1)`. The three-point Fourier matrix is
`F_(x,y)=w^(xy)`, and with `D=diag(1,w,w)`,

```
C = F^(-1) D F
  = [[1,w^2,w^2], [w^2,1,w^2], [w^2,w^2,1]],
C^3=I,                     F^(-1)=D C D.
```

For a nondegenerate subspace `U` of a ternary dot-product space, define
`C_U=F_m^(-1) diag_x(w^Q_U(x)) F_m`, with
`Q_U(x)=(P_U x).(P_U x)`. Orthogonal direct sums give products of these
operators. An orthogonal line of norm `nu` contributes `C` when `nu=1`
and `C^(-1)` when `nu=2`. Both are explicit F4-coordinate circuits;
`C^(-1)=C^2`, and the source's coordinatewise coefficient-square wrapper
conjugates `C` to `C^(-1)`. Thus mixed norm classes do not require a
uniform-norm frame or a growing-field Frobenius assumption.

For the lifted frame used by the role network, take
`F=F_3^(h+1)` with form `diag(-I_h,1)` and, for each triple
`S subset [h]`, take `t_S=(1_S,1)`. Then

```
<t_S,t_S> = 1-|S| = 1-3 = 1 in F3,
<t_S,t_T> = 1-|S intersect T| = 0 when |S intersect T|=1.
```

The ambient form is nondegenerate. Each `L_S=<t_S>` is therefore a
nondegenerate line, and `F=L_S perp L_S^perp`; adjacent lines split
orthogonally. The phase identity applies to each such split. More generally,
every residual nondegenerate symmetric form over odd-characteristic F3 has
an orthogonal basis with nonzero norms: if all vector norms vanished,
polarization would make the form zero; split one nonisotropic line and
induct. Residual basis changes may therefore have norms 1 and 2, both
handled by the explicit inverse/conjugation wrapper.

The center/side label table and its inclusions are derived in
`ntt_base_five/finite_motif_rank_closed_form_audit.md`. At a stage, if `A`
is the preceding tensor space, `P` its prefix line, and `B=P^perp`, then
`A=B perp P`, while `F=L_t perp L_t^perp`. Hence

```
(P tensor L_t)^perp
  = (B tensor F) perp (P tensor L_t^perp).
```

This gives the center transition and complementary side labels by direct
orthogonal sums. The graph adjacency supplies `L_s perp L_t` for each
side-neighbor label. Thus every frame inclusion needed by the finite role
network follows from the explicit Gram identities, rather than an inferred
rank from a small example.

## Endpoint and child count

Set `v=binom(h,3)`, `z=3 binom(h-3,2)`, `N=v^3`, `I=3v^2`. The graph's
ordered degree is `z`; a three-stage invocation has `N` data pairs and `I`
invocations. Each invocation has `vz` side roles and `h` center roles, and
there are two data banks. Thus

```
W = 2N + I(vz+h).
```

For lifted factor dimension `d=h+1`, the label dimension is `m=d^3`.
The only decreasing label edges are the `h` center roles per invocation;
each drops `d` dimensions. Their total drop is `L=Ihd`. A signed label
dimension telescope plus twice this downward variation gives

```
s_label = Wm - 2N + 2L.
```

There is also one rank-one endpoint correction on each of the `N` routes.
Indeed the uncorrected phase product on the route is
`C_(U^perp) C_U^(-1) = C_full C_U^(-2) = C_full C_U`, since `C_U^3=I`.
Applying the additional child `C_U^(-1)` gives `C_full`. This is a real
extra child, not a free endpoint identity. It adds `N` to the child count,
so the corrected total is

```
s = Wm - N + 2L.
```

The exceptional child uses the same selected frame ranks as the route; it
does not enlarge the frame dimension. Its cost is already present in `s`.

## Exact lifted ratio and strict recurrence exponent

At `h=100`, the fixed integer values are

```
v=161700, z=13968, N=4227952113000000,
I=78440670000, W=177176569091445000000,
d=101, m=1030301, L=792250767000000.
```

They give

```
W/N = 41906 + 1/539,
L/N = 101/539,
(N-2L)/N = 337/539,
alpha := s/W = m - (N-2L)/W.
```

Consequently

```
1-alpha/m = (N-2L)/(Wm)
           = 337/23271753837835 > 20*2^(-50).
```

As `m<2^20`, `ln(m)<20`, and for `epsilon=2^(-50)` we have
`m^(1-epsilon)>m(1-epsilon ln(m))`. The displayed deficit therefore
implies `alpha < m^(1-epsilon)`, so

```
sigma = log_m(alpha) < 1-2^(-50) < 1.
```

This is the strict rank saving used by the recursive tensor layer. The
integer certificate and its scope are recorded in
`ntt_base_five/finite_motif_integer_certificate.json`; the complete role
frame witness reports 26 small framed network runs and 3,113,760 checked
role values, but those finite checks are supplementary to the symbolic
count above.

## How the child volume and recurrence are charged

The scalar role circuit partitions a parent of volume `V` into `W` role
streams, each of volume `V/W`; the `s` child maps therefore contribute
`(s/W) H(e/m)`, not `s H(e/m)` and not `W H(e/m)`. Parking the other
`W-1` streams while visiting one child costs `O(V)` per child. Since `W`
and `s` are fixed constants independent of recursion depth, this is a
fixed `O(V)` node toll and does not multiply a descendant's running time.
The row-role partition is independent of the active mask, so each child
retains the full Cartesian mask distribution and exactly the same role
multiplicity. Zero-padded rows are preserved and can be cropped on return.

With the dirty active-rank router, fixed-width basis batches are a constant
number of disjoint matching row-add batches on the first `e` active ranks.
The residual `e/m`-dimensional frame is moved to the first `e/m` ranks by
a determinant-one basis extension. Coordinate swaps include three SUM
shears and the separately priced active-symbol negation. Role eligibility
depends only on the mask cardinality; off-eligible frames are zero and act
as identity. Base-`m` digit-conditioned groups partition the active ranks
for every cardinality, so no low-active sector is deleted. Every completed
basis/router operation preserves the active set. This is the invariant
that lets prefix-good sectors stay good and lets the exact bad-set repair
be charged on the complete parent volume.

Under those priced router and equal-chunk interchange contracts, the
normalized recurrence has the form

```
H(e; m) <= alpha H(e/m; m)
            + polylog(m+2) * (e^tau + polylog(m+2)),
alpha=s/W, tau<1.
```

Because `sigma=log_m(alpha)<1`, any fixed
`lambda>max(sigma,tau)` with `lambda<1` gives
`H(e;m)=O(e^lambda polylog(m))`. The complete role/frame count, including
the exceptional endpoint child and scratch-row volume, thus supplies the
finite strict exponent required by the active-rank recurrence.

## Boundary

This certifies the ternary role/frame premise and its compatibility with
the active-rank recurrence, relative to the stated fixed-tape interchange,
dirty-selector, exact bad-sector repair, and large-payload contracts. It
does not establish those external machine contracts, the arbitrary-field
FFT scalar ledger, or the input/output bridge to ordinary polynomial
multiplication. In particular it is not an unconditional global
`O(n log n)` result.
