# Short-dimension transpose for the ordinary coefficient map

This explicit layout realizes the top isomorphism in HvdH,
[cyclomult, Lemma 2.2](https://www.texmacs.org/joris/cyclomult/cyclomult.pdf).
It removes the need for a fast native tensor/routing service for this
outer map. The later native CRT, dock, and phase services remain separate
dependencies. The argument is a written construction, not a
kernel-checked tape implementation.

Let R=Z/P, S=bitlength(P), N=alpha*m with gcd(alpha,m)=1. Coefficients
are canonical S-bit words. Let c*m=1 modulo alpha. The ring map

    R[X]/(X^N-1) -> R[U,Z]/(U^alpha-1,Z^m-1), X -> U^c Z

sends the ordinary input position k=q*m+r, 0<=q<alpha, 0<=r<m, to

    U^(q+c*r modulo alpha) Z^r.                     (T)

Indeed c*(q*m+r)=q+c*r modulo alpha and k=r modulo m.
The index map is bijective: given r and U exponent j, recover
q=j-c*r modulo alpha, then k=q*m+r. Hence this is a permutation of
coefficient words with a specified inverse, in addition to its ring
interpretation. No arithmetic on data coefficients occurs.

## Explicit fixed-bank transpose

The initial array consists of alpha consecutive rows, each of m words.
First transpose to m rows of alpha words. Pad only the short dimension
to Q=2^ceil(log2 alpha)<2alpha (alpha=1 is direct). Appending Q-alpha
zero rows, and later cropping their positions, costs O(NS) bits.
There is no padding of the m dimension or tensor call on this layout.

At stage k, each adjacent group of 2^k original rows is represented as
m consecutive blocks, each block containing 2^k words in its original
q order. Initially k=0. Zip each adjacent pair of such groups to obtain
the representation for stage k+1: for each r write the first group's
block, then the second group's block. The block length is 2^k*S bits.
After log2 Q stages this is exactly the transposed array, with Q words
per row in increasing original q order.

One zipper stage uses two identical input copies and one output bank.
For a pair of groups, input head A reads the first group and head B the
second; alternating whole blocks writes the required zip. At the end,
A skips the second group and B skips the first group of the next pair.
Both heads move forward at most a constant multiple of the full volume;
their final return, the initial offset of B, and creating the second
input copy are also charged. Each pair's m-block boundaries are given
by binary counters. Increment/decrement and head returns on little-endian
counters have linear amortized cost in the number of copied bits, with
initialization cost dominated by the group length. Thus a stage costs
O(Q*m*S), not O(Q*m*S*log m).

An output copy supplies the two inputs for the next stage. Reuse a fixed
set of banks by exchanging their roles; k and all group/bit counters are
ordinary data. No tape per stage, q group or recursion depth is introduced.
At the end crop the Q-alpha positions in each r row. Total cost is

    O(N*S*(1+log alpha)).                           (Z)

The reverse unzip has the same bound. For each paired group, one input
copy writes all first blocks and the other all second blocks, in the
proper group order; each copy traverses/skips at most a constant volume.
Repeat stages in reverse. Before unzipping pad each alpha-word row back
to Q words, and after unzipping crop the final Q-alpha entire rows.
The reverse construction therefore restores precisely the original
ordinary coefficient order.

## Row rotations, indexing and coefficient CRT

For row r rotate its alpha coefficients by sigma_r=c*r modulo alpha.
Split/copy the two row pieces to scratch banks and concatenate in reversed
piece order. Every read, write and scratch-head return costs O(alpha*S).
Maintain sigma_(r+1)=sigma_r+c modulo alpha in O(log alpha) bit time;
this is dominated by O(alpha*S). The input delimiter/end condition can
control row iteration; a full log m arithmetic operation is not charged
per coefficient. The inverse uses the opposite rotation. Across all m
rows rotations cost O(NS), including producing/cropping the explicit
array endpoints. Computation of c is public shape setup.

Combining rotation with (Z) implements (T) and its inverse on a fixed
finite alphabet and fixed number of ordinary tapes. It does not discard
the psi component: first form the complete alpha-coefficient U rows;
then apply the separately charged coefficient CRT modulo Phi_alpha and
psi=(U^alpha-1)/Phi_alpha. Conversely recombine both components before
inverse rotation/unzip. Dummy Fourier coordinates are unrelated to the
temporary zero rows used only by this layout.

In the preferred HvdH host log alpha=O((loglog N)^4), N=Theta(n).
Consequently the outer top-map cost is nS*polyloglog(n), below the named
native phase invoice for every fixed gamma>0. This proof removes only
the outer alpha-by-m transpose/rotation dependency. It neither implements
the m-to-many-prime-axis CRT permutation nor replaces the source dock,
shuffle, controlled movement or P_gamma service.
