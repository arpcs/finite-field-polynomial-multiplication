# Symbolic audit of the finite scalar bank-exchange motif

29 October 2026. Independent algebra check of the scalar operations in
§3.1 and Lemma 5 of the 23 September 2026 preprint. This proves the
invocation and three-stage signed routing identities from the stated
incidence maps. It does not reproduce the separate subspace-label/rank
certificate of Lemma 6 or its very large numeric rank totals.

## One invocation as a block-linear map

Let `T` be the triples from `[h]`. A forward invocation has data source
`x=(x_T)`, data target `y=(y_S)`, one side scratch `a_(S,T)` for each
ordered neighboring pair, and a central scratch vector `c`. Scratch values
are arbitrary. Write the four fixed linear maps as

```text
copy:       a <- a + Vx
gather:     c <- c + Gx
scatter:    y <- y + Rc
side:       y <- y + Ja.
```

The side and central scratch registers are controls in their corresponding
updates, and therefore are unchanged by those updates. In the source's
eight-row forward schedule, rows 0 and 1 subtract `Ja` and `Rc` using the
old scratch. Rows 2 and 3 add `Vx` and `Gx` into scratch. Rows 4 and 5
scatter and side-inject the updated scratch. Rows 6 and 7 undo gather and
copy. If the initial scratch was `(a0,c0)`, then the total target increment
is

```text
-J a0 - R c0 + R(c0+Gx) + J(a0+Vx) = (RG+JV)x,
```

and the final scratch is exactly `(a0,c0)`. This is an identity for all
initial scratch values, not a promise that scratch starts at zero.

### Bit construction

Neighbors are triples with intersection size one. Put

```text
V_(S,T),T' = 1[T=T'] 1[|S intersect T|=1],
J_S,(S,T)  = 1[|S intersect T|=1],
G_i,T      = 1[i in T],
R_S,i      = 1[i in S].
```

Then `(JV)_(S,T)` is one exactly when `|S intersect T|=1`, and
`(RG)_(S,T)=|S intersect T| mod 2`. For S=T, the intersection is three,
so the central term is one and there is no side edge. For distinct S,T with
intersection one, both terms are one and cancel in F2. For intersection
zero or two, both terms are zero. Thus `RG+JV=I` over F2, and one forward
invocation is exactly `y <- y+x`, with every side and central scratch value
restored.

### Complex construction

The scalar ring is `Z[i,1/2]`; side neighbors are distinct triples with
even intersection size zero or two. Use central coordinates indexed by
`[h]` plus `*`, and set

```text
V_(S,T),T' = 1[T=T'] 1[S,T are neighbors],
J_S,(S,T)  = -(|S intersect T|-1)/2,
G_i,T      = 1[i in T],       G_*,T = 1,
R_S,i      = 1[i in S]/2,    R_S,* = -1/2.
```

For `k=|S intersect T|`, `(RG)_(S,T)=(k-1)/2`. If S=T, k=3 and
this is one, with no side edge. For distinct triples, k can be 0, 1, or 2:
k=0 and k=2 are exactly the side-neighbor cases, where J is the negative
of the central coefficient; k=1 has zero central coefficient and no side
edge. Therefore `RG+JV=I` over `Z[i,1/2]`. The same scratch cancellation
shows one forward invocation is `y <- y+x` and restores every scratch
value.

## Three stages and the complete role permutation

For stage j, fixing the other two triple coordinates partitions each data
bank into disjoint invocation fibers. Every data role `X_a` and `Y_a`
participates once in that stage; invocations have disjoint scratch roles.
Since each invocation acts as the identity-paired bank addition, the
whole-stage map is the same bank addition on every `a in T^3`.

Stage 1 is forward from X to Y. Stage 2 is the inverse schedule from Y to
X, so it performs `X <- X-Y`. Stage 3 is forward from X to Y. On arbitrary
initial data `(x,y)`, the successive bank states are

```text
(x,y) -> (x,y+x) -> (-y,y+x) -> (-y,x).
```

Every invocation's scratch is restored within its own schedule, including
stage 2 because it is the exact inverse schedule. The source explicitly
allocates distinct scratch roles for all invocations and all three stages,
so no later invocation can alter a previously restored scratch value.

Let N=|T|^3 and I=3|T|^2. The complete scalar network has two data banks
of N roles. In the bit construction each invocation has
`z_b=3*binom(h-3,2)` ordered side roles and h central roles. In the complex
construction it has
`z_c=binom(h-3,3)+3(h-3)` ordered side roles and h+1 central roles.
Consequently

```text
W_b = 2N + I(v*z_b+h),
W_c = 2N + I(v*z_c+h+1),        v=|T|.
```

With the convention that rho maps an input role to the output role carrying
its value, the entire routed network has

```text
rho(X_a)=Y_a,       sign(X_a)=+1,
rho(Y_a)=X_a,       sign(Y_a)=-1,
rho(scratch)=scratch, sign(scratch)=+1.
```

Thus every scratch wire is a fixed role under rho, not an omitted or
zero-initialized wire. Over F2 the minus sign is plus, so the bank action is
an ordinary exchange. This verifies the scalar endpoint role permutation
used by the frame argument independently of the label/rank argument.

## What this does not certify

The scalar routing proof is explicit in the source's incidence operations
and schedule; no finite search result is needed for this identity. The
separate label proof still needs its stated neighbor geometry, nondegenerate
residuals, orthonormal-basis assertion over F2, and exact dimension-loss
counts to establish the address-rank budget. This note does not independently
verify the large numerical values of W, `s_b`, or `s_c`, and does not imply
the global multiplication theorem without that strict rank inequality and
the later tape-cost arguments.
