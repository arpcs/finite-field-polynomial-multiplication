# H2 from equal-chunk interchange: integrated finite-field audit

Editorial note (31 October 2026): Workflow wording has been made neutral; mathematical statements, proof arguments and review qualifications are unchanged.
30 October 2026. This consolidates the earlier active-rank, role, payload,
and positive-word notes. The conclusion below is relative to **one**
machine primitive, equal-chunk interchange with a strict saving. H2 is no
longer a second independent hypothesis in the ordinary coset reduction.
The remaining certification boundary is the standalone proof of that
machine primitive, not the global integer multiplier in its source paper.

Subsequent completion of the local dependency:
`chunk_swap_uniform_completion_audit.md` reconstructs SWAP from the explicit
bit motif and ordinary tape primitives, including its arbitrary-width lift.
Thus the proposed global proof has no remaining named oracle at this
interface. `full_binary_multiplication_completion_ledger.md` records the
still-pending final whole-construction audit.

The earlier derivation supplied the subquadratic native
tower scalar routine, conditional ordinary-product reduction, and bounded
algebra witnesses. This note audits the H2 premise itself and adds
the complete finite role/frame witness described in Section 8.

## 1. Exact conclusion and sole external interface

Assume a fixed finite-tape, finite-alphabet machine can swap two u-bit
address chunks in a complete array of V stored bits in O(V(u+1)^tau),
for one fixed tau<1. Its interface permits arbitrary prefix, gap and suffix
lengths, and includes descriptors, padding and cleanup. In particular all
opaque suffix payload bits move within that bound. Call this SWAP.

Then for some fixed beta<1 there is an exact deterministic fixed-tape
algorithm applying

    H2^(tensor k), H2=[[1,1],[1,0]],

to 2^k records of D arbitrary binary coordinates in
O(2^k D (k+1)^beta) bit steps, uniformly in D. The output order is the input
order. The same algorithm computes its ordinary binary transpose because
the target matrix is symmetric. No generic circuit-to-tape transpose rule
is required for that conclusion.

The following proof uses constructive fixed ternary labels, native binary
address permutations, and the explicit constant F16 word now present in
`EXPLICIT_F16_H2_POSITIVE_WORD.md`. The general positive-generation search
and its unspecified field extension are no longer needed for this target.

## 2. Fixed ternary kernel and an explicit positive word

In F4 let eta^2+eta+1=0 and

    C=[[1,eta^2,eta^2],[eta^2,1,eta^2],[eta^2,eta^2,1]],
    A=C direct-sum [1].

The ternary Fourier matrix diagonalizes C with quadratic phase eta^(x^2).
C^3=I. For a nondegenerate ternary direction v, norm nu in {1,2}, the
directional kernel is

    I + eta^(-nu)*(T_v+T_(-v)).

Its Fourier eigenvalue is eta^((v.z)^2/nu). Orthogonal sums of subspaces
give commuting products of these kernels. Reversing a sign or using norm
2 changes C to C inverse; a single coefficientwise F4 Frobenius wrapper
on each side implements the inverse, with no extra recursive child.

The workspace now contains a concrete F16 word, rather than only a
positive-generation existence proof. Work in F16=F2[t]/(t^4+t+1), eta=t^5.
An explicit sequence of rank-one commutators gives I+E13 with 96 forward A
letters. Permutation conjugation gives the four elementary matrices in

    H2 tensor H2 = U13 U24 Pfirst U12 U34 Psecond.

Here Pfirst=(1 3)(2 4), Psecond=(1 2)(3 4), using column vectors and
rightmost-first application. The expanded word has 384 forward A letters
and 392 invertible monomial letters, all over this one fixed F16.
I independently rebuilt and ran the current guarded C++ word witness;
it passed the field, commutator, target-matrix and all 256 binary-basis
transpose pairings. These constants are already explicit; no runtime
extension search or positive-word search is charged to a variable input.

For E-valued coefficient records use E=F16=F4 direct-sum t*F4. Every C
slot acts separately on the two F4 coefficient planes. Its inverse wrapper
is the fixed binary map sigma_hat(a+t*b)=a^2+t*b^2. This is NOT a claim
that ordinary F16 squaring fixes t. The complete C slot is E-linear even
though its internal inverse wrapper is only F2-linear. Intervening
monomial E-scalars are fixed 4-by-4 binary maps. Thus each word identity
is applied E-linearly as a whole.

Embed a binary coefficient bit as the 0/1 element of E. Since the target
H2 tensor H2 has F2 entries, its output returns to that binary subspace.
Embedding and extraction change bit volume by only the fixed factor four.
Use D independent such words per coordinate for arbitrary D-bit payloads.

## 3. The finite role network, including the source correction

Here is a convenient fixed even ground-set size H=48. Let T be its triples,
v=binom(H,3), and connect distinct triples whose intersection has size one.
Their degree is z=3*binom(H-3,2). An invocation uses v data values in each
bank, one side role per ordered neighbor pair, and H center roles.
Incidence gather/scatter contributes intersection parity; the side roles
cancel exactly the intersection-one contributions. Thus the eight-step
copy/gather/scatter schedule adds one bank to the other and restores every
arbitrary initial scratch value. Three stages exchange the two data banks.
The symbolic scalar proof is `../SCALAR_MOTIF_SYMBOLIC_AUDIT.md`.

There are N=v^3 data pairs, I=3v^2 invocations, and

    W=2N+I(vz+H)

roles. Give the factor space dimension F=H+1 over F3, with Gram matrix
diag(2 I_H,1). The vector (indicator_T,1) has norm one; neighbor vectors
are orthogonal. On pairs of its first H coordinates the map
(a,b)->(2a+2b,2a+b) is an isometry to the ordinary dot product, so the
whole F-dimensional factor has standard coordinates. Its third tensor
power has dimension M=F^3. All triple tensor lines U have norm one.

Use the explicit comparable nondegenerate gate labels reconstructed in
`finite_motif_rank_closed_form_audit.md`. At a stage write the earlier
factor space as B perpendicular-direct-sum P, where P is the prefix line,
and suppress the suffix line. The eight gate labels are

    B tensor L, B tensor F,
    (B tensor F) perpendicular-sum (P tensor L), A tensor F,
    B tensor F,
    (B tensor F) perpendicular-sum (P tensor L_perp),
    A tensor F, A tensor F.

Neighbor orthogonality supplies the side inclusions. The only decreasing
edges are center edges 3->4, losing F dimensions on each of the H center
roles per invocation. Let L=I*H*F. The signed dimension telescope gives
W*M-2N, and total absolute variation is W*M-2N+2L.

Choose the X-source frame to be C_U inverse, other source frames identity,
and the usual positive phase frames at gates and sinks. The endpoint on
the X-to-Y route is then

    C_(U_perp) * C_U = C_full.

All other endpoints are also C_full. At the first X edge the head frame
is C_U, so the edge is C_U^2=C_U inverse: one directional child despite
equal source/head label dimensions. There are N such corrected source
edges. Therefore the total child count is exactly

    s=W*M-N+2L.

This source choice is equivalent to the earlier note's one-child
precorrection. It does not eliminate or hide those N children. A shared
frame commutes with the pointwise XOR gates, so the framed scalar exchange,
followed by undoing the role exchange, applies C_full on *every* original
row, including scratch rows with arbitrary input values.

All nondegenerate residuals have orthogonal bases with norms 1 or 2 in F3.
Extend the residual basis to a full coordinate basis. Negating one column
if needed makes its determinant one without changing its translation
kernel. A fixed product of ternary row additions implements the basis
change; norms of either sign use the preceding one-child wrappers. At
selected width e=M*f, every basis update is a fixed M-slot matrix tensored
with I_f. Thus each elementary addition is a matching of disjoint source
and target coordinate sets among the first e selected ranks.

More explicitly, a rank-a residual is handled by a orthogonal basis
directions in the fixed M-slot space, each tensored with f coordinates.
One such direction needs one width-f child. If that direction has norm
2, the coefficientwise conjugation wraps that one whole child; mixed
norms do not require splitting a child into extra norm planes or calls.
Thus the rank-a edge uses exactly a children. Both F4 coefficient planes
of each existing F16 word are carried together by every such child.

The H=48 exact ratios, cancelled before forming large products, are

    W/N = 9633881/1081,
    L/N = 441/1081,
    1-s/(W*M) = 199/(9633881*117649), M=117649.

Since M<2^17 and ln(2)<7/10, ln(M)<12. The exact integer inequality

    199*2^36 > 12*9633881*117649

and exp(-x)>1-x show s/W<M^(1-2^-36). This is a fixed rational certificate,
not a floating-point estimate. The same calculation for the rational
address-frame network gives dimension 110592 and relative deficit
217/(9633881*110592); that optional reparameterization of SWAP is separate
from assuming the source's already stated tau=1-2^-50.

## 4. Apply those frames on all active/idle sectors without packing them

An A digit has active states 0,1,2 and idle state 3. Write its binary
address as the two bitplanes X,Y. A sector is its active mask S. All masks
remain explicitly present in the full [4]^h array; no sector is extracted
or granted free random scatter. On sector S, A tensor h equals C tensor |S|.

Use the dirty selector construction in
`../DIRTY_ACTIVE_RANK_ROUTING_AND_PREFIX_LIFT.md`. Mask-only transpositions
are implemented by toggling the dirty selector, applying its uniform
controlled transposition, untoggling, and applying that transposition again.
A second dirty selector adds a condition on the value of a paired source.
The source and target matching sets are disjoint, so the source predicate
is stable at each completed inner call. This gives ternary SUM, inverse
SUM, negation, and disjoint coordinate swaps on rank-selected active axes.
Every dirty selector index is restored; it never has to start at zero.

The short-prefix tape realization is supplied by
`generalized_binary_mask_shear_audit.md`: its controls exclude the target
and dirty tile auxiliary, its updated short field is docked after all
controls by a constant number of SWAP calls, and guards use existing bits
without widening the address. All exceptional records are corrected by
destination-key sorting. For p address bits and R-bit opaque records,
the bound is

    O(V (u^tau+1) log^2(p+2) + M_records*p^C).

The metadata uses p=log(M_records), not log(V). Record copying/reset costs
O(R) amortized, rotations use record counts, and keys omit the opaque
payload offset. This independently charges arbitrary external D; it does
not strengthen a source rectangle lemma by silently replacing log(V).

For operations on the first e active ranks, use only a physical prefix
u=min(h,ceil(C0(e+log(p+2)))). In the complete [4]^h address set, active
indicators have density 3/4. The fraction with fewer than e active prefix
positions is at most exp(-u/24) when u<h; for u=h it is empty on eligible
masks. Correct it exactly by sorting that invariant mask set. A sufficiently
large fixed C0 absorbs the key factors. Consequently one local basis batch
costs

    O(V polylog(h+2) [e^tau+polylog(h+2)])

when p=O(h) and R is exponential in h. The density bound is a count of
stored addresses and is valid for every payload; no randomness is used.

The base selected kernel uses a rank-selected cyclic trit permutation T:
C=I+eta^2(T+T inverse). If a mask is ineligible, T is identity, so the
formula is also identity there in characteristic two. The priced selector
routes therefore supply the base C call with polylogarithmic prefix cost.

## 5. Role recursion and all active cardinalities

For a selected e=M^r group, reserve enough independent rows for W^r and
split those rows cyclically into W roles. Each child still contains the
complete [4]^h address space, all dirty fields and the same opaque payload,
but only 1/W of the rows. Eligibility is a mask-only predicate, shared at
every gate. All frames are identity on ineligible masks, so the completed
role exchange is also undone there. Each child's residual axes can be
placed on its first f=e/M active ranks by the fixed local basis change.

With time normalized by that child's logical volume,

    F(e;h) <= (s/W) F(e/M;h)
              + O(polylog(h+2)[e^tau+polylog(h+2)]).

For any fixed lambda>max(tau,log_M(s/W)), lambda<1, this is
O(e^lambda polylog(h+2)). There really are s calls; the factor 1/W is
their physical role-volume reduction, not a count of unique child types.

For arbitrary a=|S| decompose its active-rank list into base-M power-width
intervals, with at most M-1 groups of each size. Use digit-conditioned group
passes: move the relevant interval to the first e active ranks, apply its
role circuit, and undo placement. On masks where that digit/group is absent
the pass is identity. These groups partition the active ranks separately
for each mask, including small a. They do not repeatedly transform the
first e ranks under the weaker overlapping predicate a>=e.

An arbitrary mask-dependent active-coordinate permutation is a product
of two involutions, each a disjoint swap matching. Its full-width placement
cost is O(V h^tau polylog(h+2)), incurred once per top-level power group.
Summing the geometric e^lambda costs and the logarithmically many full-width
placements gives O(V h^beta) for some beta strictly between
max(tau,log_M(s/W)) and one, with room to absorb fixed polylogarithms.

## 6. Supply all independent index fields from the input tensor

For H2 height k, first handle its fewer than eight remainder binary axes
directly. The remaining 8h axes form four blocks of h A digits. During one
block's complete constant word, the other three blocks are spectators.
Choose the logical digit pairs to fit eight contiguous h-bit planes:
pair bit i of a block's X plane with bit i of its Y plane. These two bits
need not be adjacent on tape. Since all H2 factors are identical,
conjugating their tensor product by this logical axis relabeling leaves
the requested H2 tensor unchanged in the original input/output order.
No physical perfect shuffle into individual adjacent pairs is required.
Their 6h binary indices supply dirty Q_h,Z_h,W_h, an independent role field
of r=ceil(log_2(W^ceil(log_M(h)))) bits, and 3h-r opaque index bits.
No spectator bit is reserved twice. For all sufficiently large h,
r=O(log h)<3h and the remaining payload is exponential in h.

With D binary coefficient columns embedded as fixed E words,

    M_records=Theta(2^(5h+r)),
    R=Theta(D*2^(3h-r)),
    V=Theta(D*2^(8h)), p=O(h).

Initially move the eight h-bit planes by a fixed number of equal-width
interchanges and move the r role bits individually to the leading row
position. This costs O(V h^tau+V log(h+2)). The opaque suffix is then
contiguous. Later promotion of another block reverses the old layout and
uses the same charged operations; it is not a free reinterpretation of
previous opaque columns. Finitely many smaller h use direct tensor passes,
with one enlarged constant independent of D.

Pad the row field from 2^r to the next multiple of W^ceil(log_M(h)).
The volume increase is less than two. Keep that one padded field throughout
all top groups and the whole fixed word. Each completed role circuit and
monomial slot preserves its row address, so a padded zero row returns to
zero and can be cropped once at the end. There is no repeated padding
factor at each recursive depth.

Likewise extend to E=F16 only once for a block. Recursive C calls carry
the same fixed-width E words (both F4 coefficient planes) as payload.
Their volume is V/W, not twice V/W followed by a second re-embedding.
Coefficientwise wrappers and all fixed scalars are linear scans of that
existing volume. Thus neither the extension degree nor row padding
multiplies the recursive s/W coefficient.

A monomial slot on one block has an affine permutation of its four states,
because AGL(2,F2)=S4. A constant NOT/CNOT circuit implements its tensor
permutation by the priced width-h shears. Its diagonal is the product of
h fixed F16 constants determined by the address. Compute it in polynomial(h)
address work per record, absorbed by R, and apply it to every E word in
the suffix in O(R). Monomial slots can change active masks but preserve the
complete address set and independent row field. All subsequent exact mask
corrections remain valid. There are precisely 776 fixed word letters;
this length is an absolute constant, not a function of h or D.

## 7. Fixed tapes and explicit exponents

At a role node keep W role tapes, a fixed number of work tapes, a parking
stack and a descriptor stack. For each child park only the current inactive
streams, copy the active stream into the child I/O area, and erase current
parent work tapes. On return restore the current streams from the stack
top, reversing their stored direction while writing them back. Each call
leaves both stack heads at the parent boundary. Descendants never scan
parked ancestors. There are s children, but s is fixed: parent parking,
return travel and cleanup add C_s V at this node. They do not multiply
the child's time by W or s. Only the currently visited work interval is
cleared, not an ancestor's prior maximum extent.

The physical h-axis ranges remain at all depths, so each role child still
has p=O(h), exponentially large payload R, and at least one complete row.
Polynomial(h) descriptors and loop work fit its own logical volume. The
number of tapes is fixed, though its astronomical constant is impractical.
The description is a uniform finite machine: finite labels/basis changes
can be generated once by finite-field elimination; runtime dimensions and
stack instructions are ordinary finite-alphabet bit strings.

Using the stated source SWAP exponent tau=1-2^-50, the H=48 certificate
has log_M(s/W)<1-2^-36<tau. Choose lambda=1-2^-51 and then

    beta=1-2^-52.

All fixed polylogarithmic routing factors fit this last gap. If instead
the same rational rank-transfer proof is instantiated with the H=48 bit
certificate, tau=1-2^-36 is permitted; taking lambda=1-2^-37 gives the
optional beta=1-2^-38. That optional faster SWAP is a re-instantiation of
the general construction, not an inference from its original fixed tau.
The weaker original exponent already suffices for the global n log n bound.

## 8. Evidence and exact remaining certification boundary

`ternary_role_frame_check.cpp` directly executes the full finite role
network at H=4 and H=6 on six sampled Fourier characters each, two arbitrary
F4 input patterns each, and one endpoint negative control per H. Projector
phases are computed by tensor contractions of explicit unit label vectors.
All 26 runs, 3,113,760 role values and 26 complete wire-dimension tallies
passed. Omitting the inverse source frame produced the expected wrong
endpoint phase in both negative controls. The dimension tallies use the
proved comparable-label rank rule; they are not numerical ranks of huge
matrices. The H=48 and H=100 rational deficits are independently checked
by cancelled exact 64-bit inequalities. No exponential address array is
constructed; largest wire bank is 239,200 values, label dimension 343.
The executable enforces its own 64 MiB and 10 CPU-second limits and ran
below one second. One intermediate H=48 cancellation check failed and was
corrected to retain its factor nine; the final report includes that factor
and passed. It was a certificate arithmetic repair, not a withdrawn bound.

The current explicit F16 word was independently rebuilt under a separate
review executable and passed its guarded fixed-size checks. This newly
available workspace artifact replaces the earlier unexecuted existence
search; it is not a word discovered by this role-frame check.

The finite scalar identity, label comparability, corrected child count,
rank routing, payload fields and fixed-word costs have now been integrated
above. Thus **SWAP implies H2**, and by
`coset_subquadratic_conditional_closure.md`, **SWAP implies exact ordinary
F2 multiplication in O(n log n)**. The formerly imported SWAP machine
dependency is reconstructed in `chunk_swap_uniform_completion_audit.md`
and `fixed_tape_primitive_reconstruction.md`. The subsequent
`../GLOBAL_FINITE_FIELD_CROSS_INTERFACE_AUDIT.md` supplies explicit outer
size bounds, native/coset and padding checks, logical plane pairing and
the counter-stack orientation. The complete proposed algorithm is now in
`../COMPLETE_BINARY_MULTIPLICATION_CANDIDATE.md`. The remaining task is its
final whole-construction audit, not a second independent H2 hypothesis or
the source's whole integer multiplier. The whole construction remains under
review; finite tests do not replace that review, and no novelty claim is made.
