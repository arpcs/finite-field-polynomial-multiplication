# Fixed-tape primitive reconstruction for the SWAP dependency

30 October 2026. Independent constructive audit of the elementary machine
obligations left open in `../LEMMA12_FINITE_CERTIFICATE_CLOSURE.md`.
The model is the objective's fixed finite number of finite-alphabet,
one-dimensional tapes. A head moves at most one cell per step. Every
construction below counts copies, counter resets, work cleanup and returns.
No random-access addresses, extra heads per dimension, or unit-cost large
integer arithmetic are used.

Subsequent composition: `chunk_swap_uniform_completion_audit.md` combines
these implementations with the finite bit motif, role recurrence and
arbitrary-width row/numeric-padding lift. Its local proof is now supplied;
the remaining audit is the whole ordinary-multiplication construction.

This note reconstructs the elementary and matrix-shear interfaces. The full
power-width transfer, internal row supply and numeric padding still need a
final integrated audit with these implementations before declaring the
ordinary multiplication goal complete. In particular a passing finite-word
or role witness alone is not evidence for those asymptotic statements.

## 1. Stream boundary protocol and counters

A formal call receives a fixed number of positive canonical binary shape
parameters, a specified ordered input interval on its I/O tape, and clean
work tapes with their heads at their origins. Adjacent irrelevant dimensions
are collapsed into one numerical range. Its finite state and fixed tracks
can mark record/interval boundaries. The interval's logical volume V counts
all stored payload bits; duplicated streams cost time but do not change V
in a recurrence. The call leaves output in the required lexicographic order
and resets only the work intervals visited by that call.

At most a fixed number of shape parameters are <=V, so their total encoding
length is O(log(2V)). Ordinary schoolbook integer arithmetic on them costs
log(2V)^C, for a fixed C, per call. For every fixed C this is at most C' V
for all V>=1, with one enlarged constant. This is a once-per-call allowance,
not permission to do that work for each individual data bit.

Use a little-endian counter with its head at the low end. Over L consecutive
increments or decrements, bit j is visited O(1+L/2^j) times. Initialization
and exceptional first carries cost O(w), where w is counter width. Thus
updates and returns total O(L+w). For a complete countdown of length L,
the stored width is O(log(2L))<=O(L). A local copy of its length permits
reset without rereading an unrelated larger descriptor. Maintain a terminal
or leading-one flag while updating; no full-width zero test occurs per bit.

For nested batch-counter stacks orient this low end at the RIGHT-hand
stack top; higher bits extend left. Append a child's counter to the right
of the current top delimiter and pop only that child's interval on return.
The head then returns directly to the parent's low end. This avoids a
parent-width traversal on every descent. Compact canonical child arguments
likewise occupy the top of their separate descriptor stack; a tiny coset
child never traverses the full ambient parent descriptor to obtain them.
Carry/borrow work remains amortized by the preceding argument, with fixed
tracks marking the leading one and terminal state.

A nested scan over a fixed number of nonempty ranges is linear in the
volume scanned. At a reset, charge a range's O(log(2L)) initialization to
the ensuing L steps of that range. An outer counter is incremented
amortized, not fully copied at every inner item. The small number of
zero-length pieces in a split can be skipped by explicit flags. The bounds
remain valid for suffix size one.

For an R-bit opaque record, reset an R countdown in O(log(2R)), copy its R
bits and return only over that record's interval. Its complete counter
work is O(R), so copying/moving the record costs O(R), even when log(R) is
much larger than the other address widths. Headers and marks use only
fixed tracks. This is the protocol used by the opaque-record routing note.

## 2. A fixed-radix digit can move in linear volume

Fix the radix q once for the entire machine. To permute the values at two
specified digit positions, split the input into q^2 tapes according to
those two values, keeping relative order on each tape. With those digit
values fixed, all remaining coordinates occur in their original order.
Enumerate output positions with the fixed nested range counters, select
the stream for the two preimage values, and read its next bit. This is a
fixed number of scans and tapes, costing O(V). Stream selection is finite
state because q is fixed, not a growing index lookup.

For a single digit move, split into q streams. The relative order of all
remaining digits is preserved by that move, so the same merge works in the
new positional order. Splitting one digit, doing a fixed pointwise map on
aligned streams and merging also costs O(V). There is no unrestricted
many-digit transpose hidden in this assertion; doing u such individual
digit moves costs O(Vu).

The descriptors of either operation have only the collapsed prefix, gap,
suffix and the one/two fixed digit fields. The preceding counter protocol
handles arbitrary large spectator ranges without reading a full address
on every bit. All streams are rewound or erased over their own visited
intervals, costing another fixed multiple of V.

For a row field R and suffix B, distribute whole B-bit rows cyclically to
W tapes, separately within each earlier prefix. W is a fixed constant.
When W divides R, the W streams have identical remaining shapes and volume
V/W. Merge them in any fixed order of the classes using a finite state
class counter. This includes arbitrary B-bit rows, and all resets/copies
cost O(V). No additional tape appears at each recursive depth.

## 3. Controlled later-field rotations

Suppose a target coordinate y in [Q] follows all controls used in an offset.
For fixed preceding coordinates, the fiber is Q consecutive B-bit blocks.
If its desired shift is a in [Q], send the first Q-a blocks to one tape
and the last a blocks to another. Merge the last portion then the first,
separately for each fiber. The result is y->y+a modulo Q. The block order
and bits within every block are preserved. Each bit is copied a bounded
number of times; counters refer to numbers of blocks rather than a free
bit address. This costs O(V) plus explicitly computed offsets.

For the rational-frame SWAP construction, Q=q^b and only a fixed number of
b-digit control fields are read. Offsets have polynomial(b) preparation
cost, using ordinary integer arithmetic. Every fiber already contains at
least Q=q^b bits, and polynomial(b)<=C q^b. Thus offset preparation per
fiber is absorbed by its own Q*B volume, uniformly in arbitrary spectators.
Only the used b-digit controls are read in full; unrelated large prefix/gap
counters are advanced amortized and are not passed through this calculation.

This restricted linear-time bound is distinct from the generalized dirty
mask router, whose offset may use p>>b address bits. That router explicitly
charges M_records*p^C and absorbs it in its exponential opaque payload.
It is not a use of the present polynomial(b) absorption with b replaced
silently by p.

## 4. Fixed rational units by increasing pieces

Let c be a fixed positive integer prime to the fixed q. For
y->c*y modulo Q, partition the input y range into its c increasing pieces
indexed by j=floor(c*y/Q). On a fixed piece, the output coordinate c*y-jQ
increases with y. For output y' in increasing order, its preimage piece is
the unique j in [c] satisfying y'+jQ=0 modulo c. Since gcd(Q,c)=1, the
required j exists and is unique. A finite residue counter selects that
stream, whose next entry is its correct preimage.

Piece endpoints are computed once in polynomial(b) integer work. There
are c fixed streams; c can be large but is independent of input size.
Empty pieces for small Q are skipped, with constants allowed to depend
on c. Reading the c-piece split and merge costs O(V).

The inverse does not require reversing an arbitrary irreversible Turing
computation: split the supplied output stream by that same finite residue
selector, then merge the pieces back in the original contiguous input-y
interval order. Each piece retains its internal order. This directly
implements y->c^(-1)*y modulo Q in O(V).

Negation fixes block zero and reverses the order of the other Q-1 blocks.
Push those blocks on a stack and pop them; reverse each popped B-bit block
on another work tape before writing it. That second reversal restores its
internal bit order. Each bit is traversed a bounded number of times, so
the operation costs O(V), including returns. A fixed signed rational unit
a/d is the composition of integer multiplication by |a|, the constructed
inverse multiplication by |d|, and possibly negation. Choosing q to avoid
the finitely many numerators and denominators makes every asserted unit
valid modulo q^b for all b. No inverse of a data-dependent scalar is used.

Fixed rational offsets and their reductions modulo Q can be prepared by
ordinary extended Euclid in polynomial(b) work. There are only a fixed
number of them in the program; that setup is included in the same fiber
or once-per-call bounds. Nothing assumes unit-cost rational arithmetic.

## 5. Triangular coordinate changes and rank-many recursive swaps

Let H_1,...,H_m precede D_1,...,D_m, every field having b radix-q digits;
intervening spectators are allowed. m and all rational matrices below are
fixed constants. A nonsingular lower-triangular coordinate change within
H or D can be done in descending coordinate order. Its earlier controls
still have their old values and physically precede the target. First scale
by the fixed diagonal unit and then add the fixed linear combination of
earlier coordinates. Sections 3-4 give O(V) per coordinate; m is fixed.
The inverse matrix is also lower triangular and has the same charge.

For a fixed rational matrix A of rank r, elimination from the topmost
nonzero row using its rightmost nonzero pivot gives

    A=E1*Pi*E2,

with E1,E2 nonsingular lower triangular and Pi a partial permutation with
r ones. To see the direction, clear entries to the left by lower-triangular
column operations, and entries below by lower-triangular row operations.
Remove the pivot row/column retaining the order on active indices. Earlier
pivots remain isolated. Reversing these eliminations gives the stated
factorization; it does not assume A is nonsingular.

Select one fixed odd prime q avoiding all rational denominators and all
numerators of the diagonal units in these finitely many factorizations,
their inverses and frame matrices. The finite matrices can be generated
once by exact elimination and a finite prime search; these are constant
setup computations, independent of b or the eventual input length. For
every b the factors remain valid and their triangular diagonals remain
units modulo q^b.

Transform D by E2 and H by E1 inverse, add Pi*D to H, then undo those
coordinate changes. For each one of Pi, the needed earlier-target shear
H_i+=D_j is implemented by

    D_j+=H_i; swap(H_i,D_j); D_j=H_i-D_j.

On values (h,d) this yields (h+d,d). The first/last steps have later
targets and therefore linear cost. The middle step is one recursive swap
of two b-digit fields; their surroundings have the permitted prefix/gap/
suffix shape. Thus the entire matrix shear uses exactly r child swaps and
O(V) other tape steps. Temporary streams do not multiply r. The lower
factors and coordinate permutations have fixed counts, not b-dependent
numbers of scalar operations.

## 6. Role parking without a child-time multiplier

Use W role tapes, fixed reusable I/O/work tapes, a parking stack and a
descriptor stack. W is fixed even though astronomical. At entry the work
heads are at their origins, and stack heads are at their current tops.
Before a child, append the W-1 inactive current role streams with separators,
copy the active role into child I/O, and erase the parent role tapes over
their current intervals. Push the parent instruction and descriptor.
All these operations cost O(V) at the current parent.

After return write the child output into its designated role. Pop the saved
streams in reverse order; prepare their destinations to the known lengths
and write popped bits from right to left, restoring their original order.
Erase the popped cells as they are left. The stack head ends at the saved
parent boundary. No operation crosses a stored ancestor. Cleanup scans
only the current call's visited work area, not the largest area previously
used by an ancestor.

At a finite-network node there are s children, with s fixed. These current
parent copies therefore add C_s*V, while each recursive child acts on the
single role stream of volume V/W. The resulting recurrence is

    time(V,e) <= s*time(V/W,e/m) + C_s*V,
    F(e) <= (s/W)*F(e/m) + C_s.

It is not s*W times the child, nor s copies of the whole ancestor chain.
The constants multiplying the additive term need not be small for a strict
power saving in e to survive.

There is also a uniform descriptor bound for this particular recursion.
The original two complete chunk ranges stay present in every descendant;
unselected subfields become spectators. For original width e0=m^k and
depth j, V_j>=q^(2e0) and j=O(log(e0)). Also V_0=W^j*V_j. Therefore
log(V_0)=O(log(2V_j)), and any fixed polynomial in an original shape's
bitlength is at most C*V_j. A child lists only its own two selected chunks
and collapsed spectator intervals, so the active descriptor list does not
grow by accumulating all ancestor partitions.

This last argument is specific to retained-range SWAP recursion. The coset
transform actually shrinks coefficient arrays; it uses the separate once-
per-batch parent descriptor and amortized counter protocol proved in
`coset_subquadratic_conditional_closure.md`. The retained-range descriptor
argument must not be substituted for that different interface.

## 7. Status and next verification

The elementary digit operations, later-field rotations, fixed rational
scalings, lower-triangular changes, rank-many swaps and fixed-tape role
parking now have independent constructive implementations with the costs
used in the source. This discharges the elementary primitive/compilation
assumptions identified in the earlier rational-frame audit.

For the final SWAP proof combine them with the independently reconstructed
bit motif, its rational endpoint identity and exact rank budget; then
check the power-width role recurrence and the arbitrary-width/internal-row/
numeric-padding lift as one uniform machine. That composition is the next
completion audit. This note alone does not mark the goal achieved or infer
an unconditional global theorem from the small C++ witnesses.
