# Final packed-router certificate for the H2 tensor layer

30 October 2026. This note closes the packed-mask, dirty-selector, and
prefix-local routing interface used by the H2 tensor construction. Its
machine-cost premise is the imported arbitrary-width interchange of
Lemma 12 in the September 2026 preprint. It does not claim a global
polynomial-multiplication bound.

## 1. Imported tape primitive and opaque-record consequence

The only nonlocal machine primitive used below is the source Lemma 12:
for two equal-width (u)-bit address fields, an arbitrary finite-tape
binary array with any prefix, intervening gap, and suffix can interchange
the fields in (O(Vu^tau)) steps, for one fixed (tau<1). Here (V)
is the *entire* bit volume, including attached payload, and the source
theorem includes parameter handling, padding, unpadding and cleanup. Its
binary-width statement allows (u>=1), including one-bit widths. The
source is the interchange lemma itself, not the integer multiplication
theorem that the paper later proves.

For clarity, this note does not obtain an (O(Vu^tau)) bound for all
following work just by calling the source lemma. The controlled rotations,
guard repair and key sorting are separate record-level tape arguments.
They give the following consequence for an array of (M) complete
records, each with an opaque (R)-bit suffix. Write

```text
V = M R,       p = ceil(log2(2M)).
```

Assume the record boundaries and address fields are in radix order, so
each target fiber consists of consecutive complete records. Assume also
that (R) dominates every fixed polynomial in (p). A guarded
vector-XOR into a disjoint (u)-bit target field, with offset a fixed
polynomial-time function of the (p)-bit address, then costs

```text
O(V u^tau log^2(p+2) + M p^C
  + u 2^(-K) M p(R+p)),       K = ceil((log2(p+2))^2),
```

for a fixed (C). If (u<K), direct bit routing costs (O(Vu)).
The `OPAQUE_RECORD_PACKED_ROUTING_AUDIT.md` proof gives all tape details:
the length-(R) countdown copies a record in (O(R)) total movement,
rotation splits at a number of records rather than a bit displacement,
and stable radix sorting carries only (p)-bit destination keys while
paying for every copied payload bit. In the displayed bound,
(u<= p), so
(u p 2^{-K}=o(1)). The correction is therefore (O(V+Mp^C)), and
the full router is

```text
O(V u^tau log^2(p+2) + M p^C + V).
```

The (Mp^C) term is an explicit metadata allowance, not free random
access. Under (R>> p^C), it is absorbed by (V). If a target fiber
is not contiguous, the required gather/reblock has to be separately
charged; the H2 layout below supplies contiguous records directly.

## 2. Exact generalized mask-XOR oracle

At a routing invocation let the first `u` physical base-four digits
be represented by disjoint bit fields `X,Y in {0,1}^u`, with digit
`d_i=2X_i+Y_i`. Reserve disjoint dirty fields
`Q,Z,W in {0,1}^u`. The full physical fields and all control/role
indices remain in the address key; only designated remaining column
bits and coefficient bits form the opaque record suffix. `W` is the interchange
primitive's tile/rotation workspace; it is arbitrary on entry and is
restored. Neither (Q,Z,W) is assumed zero.

For any fixed polynomial-time address function `g` whose controls
are disjoint from both target `T` and dirty workspace `W_u`, the oracle

```text
T <- T XOR g(controls)
```

is exact on every address and attached payload. The implementation uses
the adapter in `ntt_base_five/generalized_binary_mask_shear_audit.md`.
Place the needed workspace `W_u` in the rightmost `u`-bit dock.
Before each of the eight integer rotations, interchange the currently
updated chunk (target or `W_u`) with the chunk in the dock if needed;
undo this interchange after the rotation. All controls precede the dock,
and `g` excludes both target and `W_u`, so it remains fixed through
the tile word. The interchanges use source Lemma 12 at width `u`, with
arbitrary prefix/gap/suffix. The control tuple is enumerated by `p`-bit
counters. Each fixed-control fiber is rotated as complete records.
Guard-boundary errors are repaired by exact bad-record sorting. Thus the
completed oracle is the intended XOR, fixes every control and suffix
address, and restores (W). The lower-level guard repair is distinct
from the later prefix-sector repair in Section 5. No data bit in the
record payload is an arithmetic control.

The guard construction uses `K=ceil((log2(p+2))^2)` and the `K` target
bit residue classes. In a class, it omits the highest selected target
bit for a direct controlled-bit route; each other selected bit has a
real `K`-bit lane ending before the next selected position, with `K-1`
guard bits. It does not pad the address space to a multiple of `K`.
The tile word is safe when each lane quotient is between `10` and
`2^(K-1)-11`; the exceptional fraction is at most `80u*2^(-K)`.
The ideal XOR preserves every guard quotient. The packed map is a
bijection agreeing with the ideal map off the exceptional set, so it
preserves that set as well. Extract/sort/reinsert applies the exact map
`ideal o packed^(-1)` there and pays for every copied record. This is
the guard correction; the active-prefix exception is a separate
invariant subset corrected in Section 5.

For the active-rank construction the mask

```text
S(d) = { i : d_i < 3 }
```

is read from the original (X,Y) fields. It is an address predicate,
not a field element. Active ranks are obtained by a scan of the (u)
digit pairs; any selected rank, paired source, and output bit of a
selector are computable in polynomial (p) time. This polynomial
address work is included in `M p^C`.

The oracle layouts are concrete. A vertical bar separates the ordered
control prefix from the target, workspace and untouched fields:

| Map | Controls | Target | Workspace | Other fields |
|---|---|---|---|---|
| `Q ^= F_a(X,Y)` | `X,Y` | `Q` | `W` | `Z`, role and suffix |
| `Z ^= J(S) AND Q` | `X,Y,Q` | `Z` | `W` | role and suffix |
| `Y ^= Z AND NOT X` | `X,Z` | `Y` | `W` | `Q`, role and suffix |
| `X ^= Z AND Y` | `Y,Z` | `X` | `W` | `Q`, role and suffix |
| `Y ^= Z AND X` | `X,Z` | `Y` | `W` | `Q`, role and suffix |

At the docked rotation, the relevant local order is `[controls | target
| W]`; for example, `Y ^= Z AND X` uses `[X,Z | Y | W]`, even though
the original physical layout places `Z` after `Y`. Put controls before
the target, dock the target or `W` at the rightmost `u`-bit slot before
each integer rotation, and undo every docking/reordering interchange
afterward. This takes a constant number of width-`u` interchanges.
Only the updated `u`-bit chunk moves. The complete `X,Y` fields,
including bits beyond this prefix, stay in the address key and may be
inspected as controls; they are never absorbed into the record payload.

## 3. Dirty selector identity and the two transposition subgates

Fix one transposition (tau) of two active symbols, fixing the third
active symbol and idle symbol 3. For an arbitrary dirty word (Z), let
(T_Z) apply (tau) at coordinate (i) exactly when (Z_i=1).
Each completed (T_Z) preserves (S), for every value of (Z).
For a mask-only selector (J(S)), the word

```text
Z XOR= J(S);  T_Z;  Z XOR= J(S);  T_Z
```

restores (Z) and equals (T_J): the first completed (T_Z) leaves
the mask, hence (J), unchanged, and the product is
(T_{zXOR J}T_z=T_J). Replacing (J) by (JAND Q), with
(Q) held fixed, gives (T_{JAND Q}) and again restores (Z).
These identities require no clean selector bits.

Use the following binary realizations, with `XOR=` performed
coordinatewise:

```text
tau_A = (0 1):       Y XOR= Z AND (NOT X)

tau_B = (1 2):       X XOR= Z AND Y
                     Y XOR= Z AND X
                     X XOR= Z AND Y
```

For each line, target and controls are disjoint fields. In the second
realization, with `Z_i=1`, the three successive XORs send
`(x,y) -> (x XOR y,y) -> (x XOR y,x) -> (y,x)`; with
`Z_i=0`, they do nothing.
Therefore it is exactly the controlled swap. Each shear is the
generalized packed-mask oracle of Section 2. Its target is a (u)-bit
field and its routing interchanges have width (u), not the full block
height (m). The possibly longer mask/selector calculation is address
metadata on (p=O(m)) bits, charged in (Mp^C). Each completed
transposition preserves (S); its internal three shears need not.

## 4. Paired-source selector and SUM correctness

For a fixed mask (S), choose a matching of selected active target
ranks to selected active source ranks. Require that every paired source
is active and that the set of sources is disjoint from the set of
targets. Let (J(S)) mark the physical targets. For (a in {0,1,2}),
let (F_a(S,d)) mark a target iff its paired source currently contains
symbol (a). It is computable in polynomial (p) address work.

For every dirty (q), the completed operator (L_q=T_{JAND q})
changes only selected targets. It preserves (S) and all paired source
values. Consequently
(F_a(S,L_q(d))=F_a(S,d)) for every (q), not merely for clean
selectors. Hence

```text
Q XOR= F_a(S,d);  L_Q;
Q XOR= F_a(S,d);  L_Q
```

equals (T_{JAND F_a}) and restores (Q,Z,W). This is the
source-value-conditioned selector oracle, built from exact address
shears; selector invariance is only invoked at completed-operation
boundaries.

Chronological (tau_B) then (tau_A) is the active-symbol cycle
(0->1->2->0); reverse order is its inverse. Apply these in the
paired-source cases (a=1) and (a=2), with opposite orientations,
to obtain

```text
target <- target + source (mod 3).
```

Case (a=0) is identity. The source is never altered, so all selectors
remain valid across the fixed sequence. Coefficient (-1) uses the
inverse. A coordinate swap uses three SUM shears and one additional
active-symbol negation (1 2); three shears alone are not a swap.
Thus every fixed-size row-addition batch in the ternary frame program
is a constant number of these routed gadgets. The constant depends on
the finite frame, not (u,m,D).

## 5. Prefix restriction, bad masks, and exact correction

Let the complete physical block have (m) base-four positions, but
consider a recursive frame of width (e). It acts only on the first
(e) active ranks. Set

```text
u = min(m, ceil(C0 * (e + log2(p+2)))),
```

for a fixed sufficiently large (C_0). All physical targets and the
three routing fields use only their first (u) bits. The suffix bits
of (X,Y,Q,Z,W) remain untouched. The selector computation may inspect
the full address, but the chosen source and target ranks, whenever
present, lie among the first (u) physical positions. If the pass is
eligible only for (|S|>= e), set its selector to zero when the
prefix contains fewer than (e) active digits. Such addresses receive
identity.

If (u=m), eligibility implies the prefix contains at least (e)
active digits, so there are no exceptional masks. If (u<m), then
(u>=2e) by the choice of (C_0). In the complete stored address
array each physical digit is independently active with probability
(3/4); writing (B_u) for the active count in the prefix, Chernoff
gives

```text
Pr[B_u < e] <= exp(-u/24).
```

This is a fraction of the complete array, including ineligible masks,
all row roles and all payload columns. Eligibility and the bad predicate
depend only on (S). The ideal selected-rank operation preserves (S);
the exact routed shears also preserve (S) at completed-operation
boundaries. Thus the bad set is invariant. In fact the guarded oracle
repairs its own lower-level exceptional records exactly, so no
uncorrected guard error is propagated into this prefix correction.

If a separate implementation compares a guarded approximation with its
ideal address permutation, it must extract precisely the invariant bad
set before reinsertion: compute full destination keys in polynomial
(p) time, stably radix-sort the extracted complete records, and fill
their marked holes. The correction cost is

```text
O(V + M p^C + exp(-u/24) M p(R+p)).
```

Choosing (C_0) large enough absorbs the fixed number of router calls
per node and all address-polynomial factors. This correction retains
every payload; no low-active sector is discarded.

For (u<K), direct routing costs (O(Vu)), which is
O(V polylog(p+2)). Otherwise, applying the packed
primitive to the (u)-bit prefix gives the local node charge

```text
O(V (e+log(p+2))^tau log^2(p+2) + V + M p^C).
```

This is the required prefix dependence: recursive nodes do not pay
(O(Vm^tau)) merely because the full block has height (m).

## 6. Complete-mask recurrence and row-role division

The fixed ternary role network has constants `M_c,W_roles,s_child`, with
`alpha=s_child/W_roles` and `sigma=log base M_c(alpha)<1`. At node width
(e=M_c f), its fixed basis change is
B_Mc tensor I_f. Gaussian elimination of this *constant-size*
matrix over F_3 expresses it as a fixed number of row-add
batches. Each batch pairs disjoint target and source slots, so the
preceding SUM construction applies. The selected (e) ranks are first
placed at the front by the separately charged top-level active-rank
permutation; within the recursive node the prefix router uses only
u=O(e+log p) physical positions.

The row-role field is independent of (S). Let `q_role=ceil(log base M_c h)`
be the recursion depth bound. Reserve
`r_role=ceil(log2(W_roles^q_role))=O(log h)` bits so the original row count
`N=2^r_role` is at least the number `W_roles^q_role` of rows needed at the
deepest role level. Pad to the next multiple `N'` of `W_roles^q_role`; since
`N>=W_roles^q_role`, `N'<N+W_roles^q_role<=2N`. Each role split partitions all rows
cyclically into `W_roles` streams of equal shape. It does not first filter to
eligible masks. All `s_child` child calls therefore retain the complete
physical mask distribution, and each child volume is the parent volume
divided by `W_roles`. Do not crop or test padded rows inside the recursive
network: a parent pointwise gate can mix genuine and padded role wires
within its final role group. The invariant needed is at the complete
role-network boundary, after undoing the role permutation: that complete
map preserves the row address and acts fiberwise on arbitrary initial
role values. Since the padded row's full input fiber is zero and the
complete map is linear, that row is zero again at this boundary and can
then be cropped. The one top-level padding to `N'` suffices; recursive
row splits divide exactly by `W_roles`, with no new padding. Arbitrary
dirty values in scratch roles are restored by the source network's
transparent schedule; no clean ancilla is assumed.

The normalized width recurrence is

```text
H(e;m) <= (s_child/W_roles) H(ceil(e/M_c);m)
           + O(polylog(p+2) * ((e+log(p+2))^tau + polylog(p+2))).
```

It retains the factor `s_child/W_roles` at every recursion level. For every fixed
lambda>max(tau,sigma), the solution is
O(e^lambda polylog(p+2)). This holds on each complete
mask array; the prefix exception is a repaired subset of that same
array, not a smaller conditional subproblem.

For arbitrary active count (a=|S|), write its base-(M_c)
expansion. The consecutive active-rank intervals of power widths,
repeated according to each digit, partition the active ranks of every
mask. There are O(log m) fixed-width passes, each enabled only
when the corresponding interval exists. The full-width interval
placement is performed once per pass and inverted afterward; its
full-(m)-width charge is
O(V m^rho polylog(p+2)) for a fixed rho<1.
Recursive frame calls use the prefix charge above. The sum over all
interval widths is geometric. Hence the complete-mask role operator
and its exact transpose have strict sublinear tensor-height exponent,
up to fixed polylogarithmic factors.

## 7. Uniform address width and arbitrary payload

For the internal H2 instance, use four logical blocks of (h) A4
digits (the fixed (M_4=H_2tensor H_2) word acts on one block at a
time). The selected block supplies (X,Y), each of width (h). The
other three blocks supply the disjoint dirty fields (Q,Z,W), each
width (h). Reserve the independent row-role field and leave the
remaining index bits as part of the opaque suffix. For one block call

```text
M = 2^(5h + r_role),
R = D * 2^(3h - r_role),
p = ceil(log2(2M)) = O(h),
V = M R = D * 2^(8h).
```

Fixed factors for field-plane encoding and row padding are harmless.
The formula is a radix split of the original address: the high column
bits are record addresses, and the low column bits plus the (D)-bit
coefficient word are the consecutive record suffix. Forming records
requires no gather or transpose. Since r_role=O(log h),
R >= D*2^(3h-O(log h)) dominates every fixed polynomial in
(p) for growing (h), uniformly for every (D>=1). The finitely
many bounded (h) values use direct finite-width routing, costing
(O(V)) with a constant independent of (D).

Each of the four block calls restores the other logical blocks and all
dirty routing fields; they are processed sequentially. A fixed number
of block reorientations uses Lemma 12 on width (h), costing
(O(Vh^tau)) each. The row field is not borrowed as (Q,Z,W), and
the same spectator bits are never counted twice. For external payload
width (D), the entire tape volume is already in (V); neither the
router nor the finite-field word adds a log D multiplier.

The final dependency ledger is therefore precise: the opaque-record
router, dirty-selector identities, prefix concentration/correction,
row division, and arbitrary-(D) H2 layout are locally derived above;
the source equal-chunk interchange and the finite ternary role-network
identities/rank deficit remain named imported contracts. This certifies
the packed-router interface relative to those contracts only.

The short-dock implementation and finite guarded witness are audited in
`ntt_base_five/generalized_binary_mask_shear_audit.md`; its result is
recorded in `ntt_base_five/generalized_binary_tile_check.json`. That
witness is bounded evidence for the integer tile identity and exception
repair only. It does not replace Lemma 12, the opaque-record tape ledger,
or the asymptotic role recurrence above.



