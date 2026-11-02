# Exact-width Toeplitz compiler for dyadic convolution

This note gives a written construction of an exact-width printer for the
local Toeplitz operators used by the host. It uses a rank-three
displacement identity and signed dirty replay. It is not an executable
printer or a proof-assistant-verified tape implementation; the circuit size and depth bounds are established below. The
FFT and circuit specialization are classical constructions.

Let A be a commutative ring with a specified inverse h of 2. The generator
below uses only integer shape data for topology. Coefficients are elements
of A; when A is the actual B_P host, its arithmetic is performed during
public setup by the separately priced scalar backend.

## 1. A finite recursive arithmetic circuit with an effective printer

For v<256, use direct schoolbook convolution. For v>=256, let b be the least power of two with b>=2 and b^2>=4v, put s=b/2 and a=ceil(v/s)=ceil(2v/b), and let t be the least power of two at least 2a-1. Since a<=b/2, one has t<=b and t divides 2b. Minimality gives b<4sqrt(v), so 4b<v for v>=256. Also

    t < 2(2a-1) < 4a <= 8v/b+4,
    t*b < 8v+4b < 9v,       a*b <= 2v+b=O(v).

The coarser bound t*b<16v follows from t<=b and b^2<16v. Moreover b<=v^(3/4), so the recursive point-product length strictly decreases.

For a nonzero commutative ring A with 2 invertible, form the free monic quotient C=A[Y]/(Y^b+1), with y the residue of Y. Its basis is 1,y,...,y^(b-1), and y has exact order 2b: no power y^j with 0<j<b is 1 by basis independence, and y^j=-y^(j-b) is not 1 for b<=j<2b because 2 is a unit. Define omega=y^(2b/t); it has order t. For 0<r<t, set g=gcd(r,t) and t/g=2h. Since r/g is odd,

    (omega^r)^h = y^(b*r/g) = -1.

It follows that

    (1-omega^r)^(-1) = (1/2)*sum_(q=0)^(h-1) omega^(r*q).

Thus every nontrivial DFT root difference is a unit in C. For each 0<r<t, the length-t geometric sum is zero because multiplying it by the unit 1-omega^r gives 1-omega^(rt)=0; the trivial sum is t. Hence the length-t DFT has inverse t^(-1) times its conjugate-sign transform; t is a power of two and hence a unit in A. The inverse scalar is prepared and charged as an ordinary public coefficient.

Write the input polynomials in width-s blocks, f(X)=sum_j f_j(X)X^(js) and g(X)=sum_j g_j(X)X^(js), with deg(f_j),deg(g_j)<s. Embed each block in C by X->y and form outer block polynomials F(Z)=sum_j f_j(y)Z^j and G(Z)=sum_j g_j(y)Z^j. Their product has outer degree at most 2a-2<t, so the length-t DFT has no wrap in Z. Each inner block product has degree at most 2s-2=b-2, so reduction modulo Y^b+1 has no wrap in Y. Inverse transformation recovers the block sums; overlap-add at offsets js restores the exact ordinary product. This costs O(a*b)=O(v) additions and introduces no aliasing in either coordinate.

Above that size, print input blocking and zero padding, both radix-two transforms, the t
recursive length-b point products over the same ring A, their negative folds,
the inverse transform with its genuine t inverse, and overlap-add. A
power of the formal root y is a signed coordinate rotation; it is printed
as a finite list of coefficient-coordinate incidences, not an operation in
an unrepresented extension field. The formal quotient has b explicit
coordinates. Thus every printed gate is an A addition, subtraction,
multiplication, copy, or multiplication by a prepared dyadic scalar.

Assign fresh integer wire identifiers as gates are appended. A fixed
depth-first interpreter with a binary stack and counters prints the
recursion on a fixed number of ordinary tapes. It may rescan its finite
wire lists to compute levels and offsets: polynomial time in the list
size is sufficient here. The generator is not executed once per main
data record. Its setup inputs and output lists have polynomial size in
the maximum local axis R, and R=N^o(1) in the host.

The recurrence T(v)<=t*T(b)+K*v*log(v+2) follows from the t recursive point products and the O(v*log(v+2)) transform, padding, folding, and overlap-add work. Let eta satisfy 9*(3/4)^16<eta<1. Since b<=v^(3/4), the limsup of log(b+2)/log(v+2) is at most 3/4. Thus, beyond a fixed threshold, the recursive coefficient 9*(log(b+2)/log(v+2))^16 is at most eta. If T(b)<=C*b*log^16(b+2), the recursive contribution is at most eta*C*v*log^16(v+2). Choose C to absorb the K*v*log(v+2) toll and increase C for the finite remaining values and direct cases. This proves T(v)=O(v*log^16(v+2)).

For depth, t<8*sqrt(v), while each child size is at most v^(3/4). The recursion has O(log log v) levels; summing O(log t) per level along a path gives O(log(v+2)) total depth. All arithmetic gates have fan-in at most two. The number of input incidences is at most twice the gate count plus the output ports, so it is also O(v*log^16(v+2)). The printer does not inspect values or remove edges whose coefficients happen to vanish in A.

The dyadic supplier is the standard two-fold negacyclic Schönhage–Strassen construction. Cantor and Kaltofen describe the reformulation of Schönhage–Strassen for polynomial multiplication when division by 2 is available, and give more general arbitrary-ring/algebra results. See [Cantor–Kaltofen (1987), author-hosted report](https://kaltofen.math.ncsu.edu/bibliography/87/CaKa87_techrep.pdf), [Cantor–Kaltofen (1991), author-hosted article](https://kaltofen.math.ncsu.edu/bibliography/91/CaKa91.pdf), and [Schönhage–Strassen (1971)](https://doi.org/10.1007/BF02242355). The construction is a specialization of established methods, not a new multiplication algorithm.
## 2. Fixing a kernel without a field assumption


Fix the second convolution vector k. Evaluate each gate in the formal
dual-number algebra A[epsilon]/epsilon^2, with variable input x_j replaced
by (0,x_j), fixed kernel coordinate k_j by (k_j,0), and a scalar c by
(c,0). If the two gate inputs have constant and linear components
(a,l), (b,r), their product has components (ab, a*r+b*l).
The constant components are public: compute them once by the same finite
gate list. The linear-component list is a homogeneous linear DAG over A.
It has at most a fixed number of weighted linear gates per original gate.
The final ordinary convolution is already homogeneous linear in x, so
the extracted linear output equals its actual value for every x. This
uses a formal ring identity, not equality of polynomial functions over a
finite field, Frobenius, division, or a nonzero pivot test.

The only remaining multiplications of runtime variables are multiplication
by the public constant components. Keep a coefficient entry even when its
value is zero. The topology depends only on v and the fixed convolution
construction. A scalar symbol may depend on the kernel; that changes its
prepared A value, never the endpoint list or gate count.

Replace every fanout of degree d by a binary copy tree. The total added
size is O(sum d), hence O(g0), where g0 is the pre-copy circuit size.
Every tree has height O(log(g0+2)). Therefore size remains
g=O(v log^16(v+2)), and the maximum depth is
O(log(v+2)*log(g0+2))=O(log^2(v+2)). Count copies at input wires and
designated output ports too. Gates computing a two-term sum use at most
two weighted additions. Fresh output wires separate the designated ports
from any live internal reuse.

## 3. One composite chunk graph and its physical ports

For the lower-unit-Toeplitz recursion, write the off-diagonal update as C=B*T_a^(-1), where T_a is the target diagonal block and B is the off-diagonal block. Let t_j and s_j be the original and reciprocal Toeplitz sequences. From their defining convolution identity, the interior entries satisfy

    C_(i,j)-C_(i-1,j-1) = -t_i*s_(a-j),   i,j>0.                 (D1)

For any ragged a-by-e rectangle M of this update, let J_a and J_e be the lower shifts, so (J_a M J_e^t)_(i,j)=M_(i-1,j-1) for i,j>0 and is zero on the first row and column. Then

    M-J_a M J_e^t = u*v^t + e_0*r^t + c*e_0^t,                 (D2)

where u_0=v_0=c_0=0, r_j=M_(0,j), c_i=M_(i,0) for i>0, and for the full block u_i=-t_i and v_j=s_(a-j). On a subrectangle, these sequences are shifted by its row and column offsets. The first row and first column are given by the last two terms; every interior entry is the first term by (D1). Since J_a and J_e are nilpotent,

    M = sum_(k=0)^(min(a,e)-1) J_a^k (M-J_a M J_e^t) (J_e^t)^k.

The three shifted outer-product families are lower/upper Toeplitz products. Each is evaluated with two fixed-kernel convolutions, giving six convolutions for the full rectangle. This two-convolution realization is the invoked lower-Toeplitz supplier identity. Equation (D2) is the rank-three displacement identity used in the native host proof; no field or pivot assumption is involved.

Equation (D2) gives the three-term displacement representation of the off-diagonal block on this rectangle. Construct one linear DAG for the full six-convolution sum. Its designated inputs are precisely the e source
entries and its designated additive outputs are precisely the a target
entries. Intermediate vectors between the two
convolutions, copies, zero pads, three summands and their final additions
are all internal gates counted in g. Their addresses are fresh wires in
this composite graph; none is an uncharged external b-array.

For w=max(a,e), this graph still has

    g <= C1*w*log^16(w+2),   H <= C2*log^2(w+2)

for two fixed constants independent of A, p, nu and host dimension D.
Six and three are fixed counts, so composition does not alter either
envelope. A sequential implementation of individual products would have
to count its intermediate vector as an additional external port. This
proof instead uses the single composite graph in the fitting test below.

## 4. Signed dirty replay and matching layers

For a local parent interval of u physical coefficient positions, reserve
a disjoint source and target port set of sizes e,a respectively. Choose the remaining
g distinct positions as internal graph wires. They may contain arbitrary
data; no clean extension is supplied. Execute the graph's forward weighted
additions, read its designated outputs into the target, and undo. Then
execute its source-suppressed graph on the same incoming dirty cells,
SUBTRACT the designated outputs, and undo. The common dirty contribution
cancels. The target receives C_chunk times the source, and every borrowed
position returns to its incoming value. This is the source-suppressed
replay identity; it has checked generic replay components. No unit
assumption on the ring weights is needed.

After copy trees, each level's dependency graph has maximum degree two:
fresh destinations are at this level, their sources are at earlier
levels, and every source has total fanout at most two. It is bipartite,
so its edges split into at most two matchings. A finite deterministic
printer can find these by scanning paths and even cycles. Each matching
is a disjoint collection of weighted shears on the original u positions.
Output-read ports are counted and given bounded fanout in the same way.
The four replay traversals, two signed reads and their level order cost
a fixed multiple of H matching layers. This is not an exponential
recursive recomputation of gates.

All other positions are inactive. Complete the edge matching with the
source's fixed zero-weight pairing rule, including the axis dummy. In the
preferred route convert each emitted shear, including weight zero, by the
direct three-positive-C word in
[the finite-algebra theorem](OPTIMAL_THREE_C_FINITE_ALGEBRA_THEOREM.md).
Prepare its parameters once per local weight in B=A_P[U]/Phi_alpha,
using the existing admissible U (or odd principal root), not an extra
T²=2 carrier. Retain all three C and four diagonal slots even at zero
weight. Each C slot is therefore a full canonical native matching. The
host cost invoice charges route-in, every C slot, and route-out.
The same endpoint/slot list is printed for every coefficient value.

## 5. A fitting rule with counted intermediates

Enumerate candidate chunk widths and actually print the composite graph
for every ragged row/column chunk pair used by that candidate. Use the
largest width for which every actual count has a+e+g<=u; g includes every
object described above. This finite universal scan is polynomial in R.
For a conservative monotone envelope, one may instead select the
largest w with 2w+C1*w*log^16(w+2)<=u and then verify its actual count.
Thus w=Omega(u/log^16(u+2)) eventually. Direct triangular shear words
handle the fixed finite no-fit range, with no coefficient tests.

There are O((u/w+1)^2)=O(log^32(u+2)) rectangular chunk pairs across the
two recursive halves. Run them serially; they all return borrowed cells,
so the same positions can serve later chunks. Every chunk's source and
target lie in different halves, and products of these additive cross-half
updates accumulate the desired off-diagonal block. Their matching depth is
O(log^32 u * log^2 u)=O(log^34 u).

The two child diagonal Toeplitz words run in parallel in their disjoint
halves. At each recursion level, all equal-role child actions share one
matching layer, padding shorter child words with zero edges. The total
depth is bounded by the sum over O(log u) levels of O(log^34(u+2)),
hence O(log^35(u+2)). Uneven halves and ragged final chunks change
constant factors only; no extra local coordinate is added.

## 6. Setup and the separate native execution invoice

All shape tables, wire lists, levels, edge colourings and permutations are
polynomial in R and the binary shape length. Public kernel coefficients,
constant-component evaluations and final scalar weights take polynomially
many A operations. In the actual A=B_P host, each such operation is
performed by the independently priced old scalar backend; D and S are
included. A polynomial number of operations in R,D,S,L is N^o(1) in the
stated host regime. No growing B multiplication is charged as a unit-cost
native phase instruction.

Only the emitted local matching weights receive selector/Newton/three-C
preparation, once in local setup, including zero-weight fillers. Their
number is O(u log^35(u+2)) per axis. The global diagonal entries
are products of these local units and inverses, generated in address order
by prefix expansion with fewer than 2M entries per slot. Multiplying the
assembled table into the M live records is a separate priced scan. The
main execution uses the named source-native C, permutation, and B-scalar
tariffs; these remain explicit service dependencies.
This construction is a local scalar-DAG printer; it performs no hidden
whole-grid coefficient transpose. A fixed-tape metadata printer may keep
its recursive stack and lists on fixed tape banks and use polynomial-time
scans. There is no tape per recursion depth or gate.

Under the named displacement, signed-replay, and native-execution
lemmas, these steps give the mathematical printer interface for the
dyadic supplier. The construction and counts are explicit, but this note
does not provide an executable printer or an end-to-end native machine proof.
