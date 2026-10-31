# Binary packed shears for the fixed monomial slots

29 October 2026. This is a local routing lemma using the same imported
equal-chunk interchange contract as `exact_ternary_phase_network.md`.
It does not certify that imported machine theorem or solve sector packing.
It prices one class of permutations that occurs in the fixed positive word
in `h2_char2_positive_generation_route.md`. The two-commutator rule below
is a derivation of the packed binary-bit construction also present in
Lemma 13 of the imported source, not a claim of a new general routing
primitive. The application to these tensor monomial slots is the point.

## Exact two-commutator binary word

For integers u,z, let P(a,b,t) apply these operations chronologically,
with parity tests using residues in {0,1}:

```
u += 1  if z == b mod 2
z += t  if u == a mod 2
u -= 1  if z == b mod 2
z -= t  if u == a mod 2.
```

Set p=P(1,1,+1), q=P(1,0,-1). In every translated 2-by-2 tile, write
A=(0,0), B=(1,0), C=(0,1), D=(1,1), adding the fixed even tile origin.
Then p=(B C D), q=(A B D). Consequently chronological p inverse then q
is (A B)(C D). In integer coordinates this is exactly

```
(u,z) -> (2 floor(u/2)+(1-(u mod 2)), z).
```

Mask every one of the eight updates by an independent control bit c.
For c=0 the word is identity; for c=1 it is the displayed bit flip.
Thus this implements a binary CNOT while restoring the auxiliary integer
z, including its quotient by two. It does not merely restore its parity.

## Parallel selected positions, including the exceptional set

Take three k-bit address fields x,y,z. For one residue class modulo K,
select positions j=r+iK whose full K-bit guard segment fits inside x,z.
At each elementary update, replace the unit offset by the signed sum

```
sum_(selected j) 2^j [y_j=1] [other_field_j=required parity].
```

For an x update the offset reads only y,z; for a z update it reads only
x,y. Each is therefore a cyclic integer rotation of its target address
field for every fixed pair of controls. The inverse schedule reverses
the updates and their signs.

The unbounded single-tile word moves either integer coordinate by at
most four at any intermediate time. It is enough that the quotient of
each K-bit guard segment by two lies in

```
8 <= guard quotient <= 2^(K-1)-9.
```

No intermediate selected-segment update then overflows into the next
segment. The actual packed integer rotations coincide with the independent
tile words. At the end x_j is replaced by x_j XOR y_j at every selected
position, all other x bits are unchanged, and the entire z field is restored.
The unused low prefix and any top suffix are unchanged on this safe set.

For f selected positions, the unsafe fraction among complete address
records is O(f 2^(-K)). The ideal CNOT permutation leaves all guard
quotients unchanged, so it preserves this exceptional set. The packed
word is a bijection and equals the ideal permutation on the complement;
therefore it also preserves the exceptional set. Extract its records,
route them by ideal composed with packed inverse, sort on destination,
and reinsert. This gives exact correctness on every address. No unsafe
record is dropped. A selected position lacking its full guard at the top
is handled by an ordinary single-bit controlled swap in O(V) work; there
is at most one such position per residue class.

## Explicit use of the imported tape primitive

Assume interchange of two equal k-bit address fields, with arbitrary
prefix/gap/suffix context, costs O(V(k^tau+1)), tau<1. There are M address
records, each with R payload bits; V=MR and A=ceil(log2(2V)).
The interchange puts a shear target in the innermost address position.
For each fixed control pair, split its contiguous target block at the
computed rotation offset and copy the two intervals in rotated order.
This is a constant number of sequential passes through that block. Sum
over blocks to get O(V) movement. A constant number of interchanges
and these rotations implements the eight-update word. Address arithmetic
and descriptors can be charged conservatively by M A^C for a fixed C.
Standard stable sorting of the exceptional keys and their full payloads
costs O(f 2^(-K) M A(R+A)). Thus one residue class costs

```
O(V(k^tau+1) + M A^C + f 2^(-K) M A(R+A)).
```

This is the same restricted large-payload contract used for the packed
ternary construction. It is not a claim for two-bit data records.
Apply K residue classes to cover all k paired positions. If
A=k^O(1) and R exceeds every fixed polynomial in A, choose
K=ceil((log2(A+2))^2). The exceptional and metadata charges, including
all K classes, are O(V), while their main charge is

```
O(V k^tau (log(k+2))^2) = O(V k^rho),
```

for any fixed tau<rho<1. At the finitely many small k where the guard
choice does not fit, use the ordinary per-position algorithm. All
permutations are exact; their ordinary binary transposes are their
inverses, using the reversed actual routing schedule and the same bound.

## Consequence for tensor powers of four-coordinate monomials

Every permutation of four states is an affine permutation of F2^2:
AGL(2,F2) has 4*6=24 elements and acts faithfully on its four points.
Its linear part is a word of at most three of the CNOT operations
(x,y)->(x XOR y,y) and (x,y)->(x,y XOR x); its translation uses bit
flips. Hence applying the same four-state permutation independently
to k paired address positions uses a constant number of the routines
above. Bit flips can use the same word with control always one.

Choose the paired positions as (x_i,y_i), with the first k-bit field x
and the second k-bit field y already contiguous. This is a choice of
tensor-factor indexing, not an uncharged physical deinterleaving. The
target H2^(tensor 2k) is unchanged by grouping its axes into these pairs.
The sector permutation must subsequently use this same pairing.

Borrow the auxiliary k-bit z field from the INDEX of coefficient columns,
not from the arbitrary scalar values stored in those columns. All z
indices occur and carry arbitrary payloads; the completed address map
restores z exactly. Sufficient conditions on original per-record payload
width W are that it has at least 2^k columns and that the remaining
R=W/2^k payload is superpolynomial in A. Power-of-two column padding
costs less than a factor two. In the balanced Pascal application,
W=2^(a+1)D, b=2k<=a, so R>=2^(k+1)D. For a=O(k) and log D=k^O(1),
A=O(k+log D) is polynomial in k, and the large-payload condition holds.
This is not automatic from only b<=a when a/k is unbounded.

A uniform parent-height variant avoids any unpriced gathering of
coefficient batches. Put P=a+b and assume log D=P^O(1). Choose fixed
tau<rho<1. If b<=P^rho, the ordinary per-position routing costs
O(Vb)<=O(VP^rho). Otherwise P<b^(1/rho), whence A=P^O(1)=b^O(1),
R is superpolynomial in A and the packed bound is O(V b^tau log^2 b).
After increasing rho within (tau,1) if necessary, this is O(VP^rho).
All data remain in their actual row layout. No independently streamed
subbatches are assumed free. If log D is not polynomial in P, retain
the general A-dependent bound rather than assert this specialization.

For a fixed monomial 4-by-4 matrix over a fixed field E, its tensor power
also has a diagonal multiplier: a product of k members of a fixed finite
set. Compute it from the address in polynomial(k) metadata work and apply
the resulting fixed-E scalar to every payload coordinate in O(V) bit
work. Its ordinary binary transpose uses the actual fixed binary matrix
transpose, also O(V), together with the inverse address permutation.
There is no assumption that E embeds into the native growing field:
each binary coefficient column may instead be embedded into a separate
E-coordinate, a fixed-factor expansion. Padding the coefficient-column
index and the constant field representation is explicitly charged.

## Remaining scope

The fixed positive word has only a constant number of monomial slots.
Under the imported interchange/large-payload contract this lemma removes
their individual tensor-permutation cost as an additional linear-in-k
obstacle. It does not implement A4^(tensor k): the active/idle sector
conversion, or an interleaved compiler for its C3 circuits, remains
unproved at sublinear cost. It also leaves the independent FAFFT scalar
and full ordinary multiplication questions open.

The bounded C++ witness `binary_packed_cnot_witness.cpp` compiled
warning-free and passed 2,178 translated/control tile cases, 40,000
packed safe cases, 40,512 packed inverse roundtrips and 512 exceptional
set samples. It enforced 64 MiB process memory and 10 CPU seconds
before checks. Results are in `binary_packed_cnot_witness.json`.
These tests concern the tile word and packed safe/exceptional identities
only. They do not time or verify the imported asymptotic tape primitive.
