# A uniform fast binary H2 tensor theorem

30 October 2026. This assembles the separately proved local lemmas into
the exact H2 interface used by `PREFIX_TAYLOR_F2_NLOGN_PROOF_DRAFT.md`.
The external theorem used is the arbitrary-width interchange lemma in
Section 4 of the September 2026 preprint, *Integer multiplication below
n log n*. Its later integer-multiplication theorem is not used.

The local proof obligations are discharged below; a statement being a
lemma of a different file is not an additional existence hypothesis.
This document concerns the H2 layer. The ordinary multiplication
composition is still a separate theorem with its own requirements.

## The machine primitive

Write V for the entire binary data volume, including suffix records.
The cited interchange theorem swaps two u-bit address fields in

```
[P] x [2^u] x [G] x [2^u] x [B]
```

in O(V u^tau), with tau=1-2^(-50)<1, for every positive P,G,B and u.
Shape processing, fixed-tape parking, temporary padding and cleanup are
included. In particular B can be an arbitrary payload width or 1.
The theorem is independent of H2 and of the finite-field multiplier
under construction. Its finite rational-frame and scalar motif premises
are reconstructed in `SCALAR_MOTIF_SYMBOLIC_AUDIT.md`,
`ntt_base_five/finite_motif_rank_closed_form_audit.md`, and
`LEMMA12_FINITE_CERTIFICATE_CLOSURE.md`.

Primary statement and proof:
[arbitrary-width interchange, Section 4](https://raw.githubusercontent.com/openai/math/main/preprints/Integer-multiplication-below-n-log-n-September-23-2026/build/sections/04-swap.tex).
We use the stated fixed-alphabet, fixed-number-of-tapes model.

## Lemma 1: frozen-control binary mask routing

Suppose M records have R-bit payloads, p=ceil(log2(2M)), and R dominates
each fixed polynomial in p. All bits consulted as controls belong to
the p-bit address key, not the opaque payload. A u-bit target T and
u-bit dirty tile auxiliary W are disjoint from those controls. For any
fixed polynomial-time address function g, the map

```
(controls,T,W) -> (controls,T XOR g(controls),W)
```

has cost O(V (u^tau+1) log^2(p+2)+M p^C), where C is fixed.

Use K=(ceil(log2(p+2)))^2, increased to a fixed small lower cutoff.
Handle positions in K residue classes. In a class, omit its highest
selected bit; every other selected bit has a complete K-bit lane within
the actual u-bit target. Thus no padding of an address chunk by 2^K is
performed. Apply the source's eight signed integer rotations, substituting
the corresponding bit of g as the Boolean control. This is legitimate
because g excludes both T and W and is frozen during the word. At one
lane the exact identity flips the target parity and restores W, while
preserving both lane quotients.

Before each rotation, swap its updated u-bit chunk into W's rightmost
dock and undo that swap afterwards. All controls are then earlier than
the target. Only u-bit chunks move; arbitrary intervening fields are
allowed by the interchange theorem. Full physical mask fields may be
much wider than u and remain address-key context.

Away from guard quotients outside [10,2^(K-1)-11], the packed word equals
the independent lane identities. The bad fraction is at most
min(1,80u*2^(-K)). The ideal XOR preserves all guard bits. Since both
maps are permutations and agree on the complement, their difference is
a permutation supported on the bad set. Extract its records, compute
their exact destination keys, stably radix-sort those p-bit keys and
fill the marked holes. Every moved payload bit on every sort pass is
charged. The missing highest bit uses one direct controlled-bit route;
u<K uses at most K such routes.

Record copying costs O(R), with an amortized ripple down-counter rather
than O(log R) work per payload bit. A rotation splits each fiber at a
number of whole records; its offset and split count cost polynomial(p)
per fiber. No bit displacement proportional to R is calculated.
The correction costs

```
O(V+M p^C+80u*2^(-K)*M*p*(R+p)).
```

There are K residue passes. Enlarging C absorbs their metadata, and
K*u*p*2^(-K) tends to zero. This proves the stated cost with fixed tapes.
Its ordinary binary transpose is the inverse address permutation.
Full routines and invariants are in `OPAQUE_RECORD_PACKED_ROUTING_AUDIT.md`,
`ntt_base_five/generalized_binary_mask_shear_audit.md`, and
`H2_FINAL_PACKED_ROUTER_CERTIFICATE.md`.

## Lemma 2: active-rank ternary matching and prefix routing

Represent h four-state digits by physical bitplanes X,Y, with
d_i=2X_i+Y_i; digit 3 is idle. For each mask S of active positions,
choose a source/target matching with disjoint source and target sets.
Three dirty address fields Q,Z,W have h bits each.

Let tau be a transposition of two active symbols fixing digit 3.
The operation T_z applies tau where z_i=1 and preserves S for every z.
For a mask-only target selector J(S), the chronological word

```
Z XOR=J(S); T_Z; Z XOR=J(S); T_Z
```

restores Z and equals T_J. With Q fixed it also works for J AND Q.
If F_a(d) marks targets whose paired source currently equals a, the
completed operator L_q=T_(J AND q) preserves S and all paired sources.
Consequently

```
Q XOR=F_a(d); L_Q; Q XOR=F_a(d); L_Q
```

restores Q,Z,W and equals T_(J AND F_a). This uses invariance only at
completed-operation boundaries, not during the internal bit shears.

The two transpositions (0 1) and (1 2) have the exact bit circuits

```
(0 1): Y XOR=Z AND NOT X
(1 2): X XOR=Z AND Y; Y XOR=Z AND X; X XOR=Z AND Y.
```

Each elementary shear satisfies Lemma 1. For the Q oracle, full X,Y
controls precede Q; for the Z oracle, full X,Y and Q controls precede Z.
Uniform transposition subgates read only the other physical bitplane and
Z prefixes. Rightmost short-field docking therefore needs a fixed number
of width-u interchanges even if the full mask has h digits. Two oriented
transpositions in the source cases 1 and 2 implement the matching SUM
target<-target+source mod3. A coordinate swap uses three SUMs and a
separate active-symbol negation. These operations preserve the active
mask and restore every borrowed address field.

For a frame acting on the first e active ranks use
u=min(h,ceil(C0*(e+log2(p+2)))). If those ranks are absent from the first
u physical positions, use identity there. In the complete four-state
address array the active indicators have probability 3/4. When u<h,
choosing C0 sufficiently large gives

```
fraction with fewer than e active prefix positions <= exp(-u/24).
```

The predicate is mask-only; both ideal and approximate matching maps
preserve it. Exact exceptional-record sorting repairs those sectors,
separately from Lemma 1's already completed guard repair. Its cost is
O(V+M p^C+exp(-u/24)*M*p*(R+p)). Full-mask controls remain in the key.
This gives a local cost

```
O(V*polylog(p+2)*((e+log(p+2))^tau+polylog(p+2))).
```

No low-active mask or exceptional payload is discarded. Fix C to cover
all polynomial address-work bounds in these routines. For definiteness
choose an integer C0>=240(C+10). The prefix fraction is then at most
`(p+2)^(-C0/(24 ln 2))`. Even summing volume-weighted node calls of
order h^sigma times fixed group/word polylogarithms, this beats the
address-polynomial factors, since p=Theta(h) in every role child.
Thus C0 is one fixed machine constant, independent of h,D and depth;
the correction is charged over the whole recursion as well as locally.

## Lemma 3: finite ternary role recursion

Over F4=F2[eta], eta^2+eta+1=0, let

```
C = eta I_3 + eta^2 J_3,
C^3=I.
```

It is the three-point Fourier conjugate of diag(1,eta,eta). The phase
attached to an orthogonal direct sum is the product of its phases.
An orthogonal line of norm 1 or 2 contributes one C or C^(-1) child.
Coordinatewise F4 conjugation supplies C^(-1) from one forward C child
and linear work. The argument extends to fixed F16 payload lanes by
using their two fixed F4 planes; this does not double normalized volume.

For the fixed triple graph on a ground set of size 100, use lifted
vectors (1_S,1) in F3^101 with form diag(2 I_100,1). Every terminal
line has norm 1 and neighboring lines are orthogonal. Pairing the first
100 coordinates gives an explicit isometry to the ordinary dot product.
All label inclusions and residual decompositions are nondegenerate;
orthogonal bases with norms 1 or 2 exist by splitting a nonisotropic
line and induction in odd characteristic.

Put

```
v=binom(100,3), z=3 binom(97,2), N=v^3, I=3v^2,
M0=101^3,
W_roles=2N+I(vz+100), L=I*100*101,
s_child=W_roles*M0-N+2L.
```

The source's eight-row copy/gather/scatter schedule restores arbitrary
scratch: the target increment is (RG+JV)x=x over characteristic two.
Three invocations exchange its two data banks. A common F4-linear phase
frame commutes with every pointwise XOR gate, so each route applies its
sink frame times its source-frame inverse. The gate-label table has
only I*100 downward edges, each losing 101 dimensions. The dimension
telescope gives W_roles*M0-2N+2L. One additional directional child on
each of N exceptional source routes corrects its endpoint; this gives
the displayed s_child. Scratch routes receive the full target too.

The exact integer identities give

```
1-s_child/(W_roles*M0) = 337/23271753837835 >20*2^(-50),
M0<2^20,
sigma=log_(M0)(s_child/W_roles)<1-2^(-50).
```

These are closed-form finite calculations, not a growing search or
an inferred matrix-rank experiment. `H2_FINAL_TERNARY_ROLE_CERTIFICATE.md`
and `ntt_base_five/finite_motif_rank_closed_form_audit.md` give the gate
inclusions, endpoint algebra, and count derivations.

At width e=M0*f, a fixed residual basis change is a constant-size
matrix on M0 slots, repeated f times. Its determinant can be corrected
by rescaling a directional vector without changing that line's phase.
It therefore factors into a fixed number of matching SUM batches from
Lemma 2. Frame residuals are sent to the first f active ranks. There
are s_child recursive calls, each on volume V/W_roles, giving

```
H(e;h) <= (s_child/W_roles)*H(e/M0;h)
          +polylog(h+2)*((e+log(h+2))^tau+polylog(h+2)).
```

Roles are split independently of S, retaining the complete physical mask
distribution. Parking/restoring the other current streams costs O(V)
per child, hence a fixed O(V) node toll. A descendant never crosses a
parked ancestor.

Reserve one top row field of at least W_roles^ceil(log_(M0) h) rows
and pad it once by less than two. Recursion divides it exactly by
W_roles. Temporary pointwise gates can mix genuine and artificial row
values, so artificial rows need not remain zero internally. No internal
crop or zero promise is used. After the COMPLETE role invocation has
undone its role permutation, it applies the target independently to
each original row, including every arbitrary scratch row. Only then
is cropping zero-padded rows justified.

The recursive base at e=1 is also prefix-local when h is large. The
single selected-rank circulant is `I+eta^2*(X+X^(-1))`, where X increments
that active trit. A mask-only selector implements X and its inverse by
the transposition gadgets above. Restrict to O(1+log p) physical prefix
positions, repair the same exceptional masks, retain a fixed number of
input copies, and perform the fixed-field additions. This costs
O(V*polylog(h+2)), rather than scanning h ranks once per data bit. A
bounded set of e<M0 is handled by a fixed number of these operations.

For lambda>max(tau,sigma), lambda<1, the recurrence is
O(e^lambda polylog(h+2)). Each active cardinality is partitioned by its
base-M0 digits into consecutive power-width groups. A global pass for
each digit/group is mask-eligible exactly when the group exists. Their
widths sum geometrically. The mask-dependent placement at the front
and its inverse use two involutive matching permutations, charged once
per group at the full h-width cost. Their O(log h) number is absorbed
by a slightly larger exponent rho<1. Thus A=C direct-sum [1] satisfies

```
cost(A^(tensor h)) = O(V*h^rho*polylog(h+2))
```

with all masks, restored auxiliaries, inverse wrappers and role padding
included. Fixed small h uses direct finite-width circuits.

## Theorem: H2 with arbitrary binary payload

Let H2=[[1,1],[1,0]]. For every t>=1 and D>=1 there is one deterministic
fixed-alphabet machine with a fixed finite number of tapes computing

```
H2^(tensor t) tensor I_D
```

on 2^t D-bit records in O(2^t D t^beta), for one fixed beta<1.
Its ordinary binary transpose has the same bound; its inverse is
obtained by two forward applications.

Proof. The explicit F16 word in
`ntt_base_five/H2_FINAL_FINITE_WORD_CERTIFICATE.md` equals H2 tensor H2
under the stated rightmost-first convention. It has 384 forward A
letters and 392 invertible monomial letters. Its projector/commutator
construction proves the identity without an unknown finite word or
search. Tensoring the word reduces the target to tensor powers of A
and fixed monomial letters.

Pair H2 axes logically, with fewer than eight remainder axes handled
directly. In the other 8h address bits use four blocks of h four-state
digits, represented by eight contiguous bitplanes. Because all H2
factors are identical, pairing corresponding bits of two bitplanes
requires no physical perfect shuffle. A fixed number of h-bit plane
interchanges and O(log h) role-bit moves prepares each block.

During a selected-block call X,Y use 2h bits; Q,Z,W use 3h disjoint
spectator bits; the role field uses r=O(log h) further bits. The other
3h-r address bits and the external coefficient word are an opaque
suffix. After fixed-factor scalar encoding and row padding,

```
M_records=Theta(2^(5h+r)),
R=Theta(D*2^(3h-r)),
p=O(h), V=Theta(D*2^(8h)).
```

R dominates every fixed polynomial in p uniformly for D>=1. Therefore
Lemmas 1--3 apply with their metadata absorbed by V. The other three
logical blocks are arbitrary spectators restored at each completed
call, and can be transformed later. Process the four blocks sequentially
and undo each layout change. No address axis is appended and no bit is
counted in two borrowed fields.

An S4 monomial permutation is affine on two bits, hence a constant NOT/
CNOT word handled by Lemma 1. Its tensor diagonal multiplies each
record by the product of h fixed F16 scalars; O(h) key work is absorbed
by R and its fixed four-bit scalar action costs O(R). The word has
fixed length. Its A letters use Lemma 3. All layout and word costs are
therefore O(V*h^rho*polylog(h+2)) for a fixed rho<1.

Pad D to four-bit F16 lanes by a factor at most four. The completed word
has F2 entries, so it applies the same binary matrix to each original
payload bit and returns padded lanes to zero. Internal fixed-field
scalar alphabets have constant size, independently of any native growing
coefficient field. Bounded h uses direct scans uniformly in arbitrarily
large D; no log D cost is repeated per payload bit.

Choose lambda=rho=1-2^(-51) above the finite/source exponents, then
absorb the fixed polylogarithms into beta=1-2^(-52). Remainders and all
fixed small heights are included by one constant. This proves the
uniform bound. The completed binary H2 tensor is symmetric, so its
forward algorithm also computes its ordinary transpose without a
generic circuit-transposition simulation. Finally H2^3=I, giving the
claimed inverse. QED.

The dependency graph is acyclic: interchange calls smaller interchange
and ordinary bit operations; active-rank tensors call smaller tensors
and interchange; the fixed word calls those tensors. Separate fixed
tape banks for these finitely many families and local parking stacks
supply one fixed machine.

## Verification scope

The algebraic proof is above and in its explicitly named component
lemmas. Fixed-array C++ reports corroborate the finite F16 word, role
frames, dirty selectors and integer tile identities. In particular the
generalized binary-tile witness was rerun with a hard 64 MiB / 10 CPU-
second Windows job guard and passed 663,552 boundary cases plus 256
nonlinear controls. Those measurements are not used as evidence for
the sublinear tensor-height bound. No enormous role network or growing
tensor was executed.
