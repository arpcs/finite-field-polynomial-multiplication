# Ordinary multiplication over a fixed odd finite field

This theorem gives a written reduction with an explicit coefficient quotient, ordinary endpoints, and charged fixed-tape calls. Its native service assumptions are stated in [the service-contract note](NATIVE_SERVICE_CONTRACTS.md), with source and finite-certificate provenance in [the native finite-source note](FINITE_NATIVE_PREMISES.md). Those imported services remain explicit dependencies.

## Theorem and imported scope

Assume the completed I_tau and P_gamma machines specified in the service
certificate: opaque equal binary-field interchange and literal C tensors
over A_P=(Z/P)[I]/(I²+1), with all widths, complete spectators, lanes,
headers, movement, head returns and cleanup charged. Suppose
0<tau<=gamma<1. Use the constructive native dock/router/CRT proofs reissued
at these tariffs as in that certificate, not an extra permutation oracle.
Use unconditional HvdH cyclotomic host/root constructions (Propositions3.4,
3.8 of the cyclomult paper) and independent classical SS arithmetic.

For each fixed odd prime p and fixed e>=1, there is one
deterministic machine with a fixed finite alphabet and fixed number of
ordinary tapes which, for every n>=1, multiplies two ordinary arrays of n
coefficients in a chosen fixed basis of F_(p^e), returning all 2n-1 ordinary
coefficients including leading/trailing zeros, in

    O_(p,e)(n*log(n+2)^gamma*(loglog(n+4))^K).       (1)

K is fixed. With the stated native-service exponents

    tau=1-859173879734039/250000000000000000,
    gamma=1-3125805/10^9=0.996874195,

the plain consequence is O_(p,e)(n*log(n+2)^(319/320)). The positive gap
319/320-gamma=805/10^9 absorbs the fixed secondary power. Field, basis,
constants and finite machine are selected before n; no growing-field or
uniform-in-e statement is asserted by (1).

## 1. Exact host and its complete ordinary information

It suffices first to treat e=1. Put L0=ceil(log2 N) for the host length.
Apply the unconditional HvdH construction at a target above2n. For fixed p,
its prerequisite target>p² holds eventually. It produces a squarefree
N=Theta(n), p coprime to N, with odd prime factors q_i between L0³ and
R0=2^(ceil(log2 L0)^2), a conductor alpha0 and the necessary principal
root data. All sufficiently small inputs use one fixed direct branch.

Freeze the local shape/permutation generator algorithms and their fixed
polynomial degree FIRST. Append unused host prime factors to alpha0 until
D=phi(alpha)>=(R0+L0+5)^A for a fixed sufficiently large A. Each added
factor has q_i-1>L0³/2, so O(log L0) added factors suffice. The original
plus appended conductor has O((log L0)²) factors, and

    log alpha, log D=O((log L0)^4),
    theta=1-D/alpha=O((log L0)²/L0³),
    m=N/alpha, mD=N(1-theta).                      (2)

The original factor tuple has at least (L0-O(1))/log2R0 axes; deleting
O((log L0)²) conductor factors leaves enough axes for the native dock
blocks h=floor(Ldock/(40*ceil(log2(R0+1)))). Here Ldock=ceil(log2(2M)),
M=product_(q_i|m)(q_i+1), and Ldock=L0-O((log L0)^4)=Theta(L0).
Also M/m=1+O(L0^-2), hence MD=Theta(N). This pays actual data volume,
while the separately chosen D pays per-record route generation.

Write S=F_p[U]/Phi_alpha and B=A_p[U]/Phi_alpha, with A_p as above.
They are literal MONIC quotients: S has D scalar coordinates, B has D
A_p lanes, each two scalar coordinates. No field assumption on S or B,
field-isomorphism search or extra square-root-of-two carrier is used.
The ordinary R-cyclic algebra of degree N maps by X->U^c Z,
c=m^-1 modulo alpha, into

    F_p[U,Z]/(U^alpha-1,Z^m-1).

For k=q*m+r, its coefficient goes to U^(q+c*r modulo alpha) Z^r.
The short-alpha transpose and row rotations, with their inverse, cost
O_p(N(1+log alpha)) on fixed banks; see [the short-dimension transpose proof](SHORT_DIMENSION_TOP_MAP_PROOF.md).

Keep BOTH U-coefficient CRT components f=Phi_alpha and
psi=(U^alpha-1)/f. They are coprime over F_p: p does not divide alpha,
so U^alpha-1 is squarefree. Prepare their extended-Euclid inverses once.
Dropping psi would lose ordinary input information and is not permitted.

## 2. Actual quotient Frobenius and selector — no remaining algebra oracle

D is even, since alpha>1 is odd. Put Q=p^D. Euler gives
Q=1 modulo alpha, and odd p with even D gives Q=1 modulo4. In the actual
quotient B, U^alpha=1 and I²=-1, so U^Q=U and I^Q=I. The D-fold
Frobenius is a ring homomorphism in characteristic p and fixes F_p.
Every B element has the ordinary monic-basis expression
sum_(j<D)(a_j+b_j I)U^j. Thus

    x^Q=x for every x in this B.                   (3)

This proof uses the generators themselves, not a computed irreducible
factorization or an assumed finite-field representation of B.

For each public local coefficient mu, set f_mu=mu^(Q-1), r_mu=1-f_mu.
Since Q>=2,

    f_mu²-f_mu=mu^(Q-2)*(mu^Q-mu)=0,
    f_mu*mu=mu^Q=mu,  r_mu*mu=0.                  (4)

These are exactly the idempotence and nilpotence premises required by
the checked three-C composition, with nilpotence bound 1 and zero Newton
steps. No prime-power Hensel or nilpotent iteration is required for this
fixed-field core. [The quotient instantiation](QUOTIENT_INSTANTIATION.md) also proves the
general Z/p^nu version; that is a separate stronger ring extension.

The actual U supplies all four admissible units. It has inverse
U^(alpha-1). Let c_alpha=Phi_alpha(1), H=(Phi_alpha(X)-c_alpha)/(X-1).
Then (U-1)H(U)=-c_alpha. For squarefree alpha, c_alpha is1 or its single
prime factor, which differs from p, so U-1 has explicit inverse.
Oddness gives (1+U^j)*sum_(k<alpha)(-U^j)^k=2 for j=1,2. Thus U+1
and U²+1 have explicit inverses, computable by geometric doubling.

The patch specializes to

    u=f_mu*U+r_mu*I,
    c=f_mu*qU*mu^(Q-2)+r_mu,
    cInv=f_mu*mu*qU^-1+r_mu.

Orthogonal idempotence and (4) give c*cInv=1 and u²+1=c*mu.
The inverse of u is f_mu*U^-1-r_mu*I. The inverse of u-1 is
f_mu*(U-1)^-1-r_mu*(I+1)/2; that of u+1 is
f_mu*(U+1)^-1+r_mu*(1-I)/2. Hence every required diagonal is a unit,
even when mu or u²+1 is a zero divisor or zero. The generic checked
three-positive-C word now applies with no undischarged selector premise.
Its exact matrices and normalization are in
[the finite-algebra theorem](OPTIMAL_THREE_C_FINITE_ALGEBRA_THEOREM.md); the local call count is a constant
improvement and does not change gamma.

## 3. Actual local Fourier words and native tensor execution

HvdH supplies rho0 of principal order N/q0 in the original host. First
omega0=rho0^(alpha0/q0) has principal order N/alpha0; after the root-only
embedding U0->U^J, J=alpha/alpha0, set omega=map(omega0)^J. It is principal
of order m=N/alpha. These root-only operations are distinct from the
ordinary top map. The usual character-sum definition supplies the stronger
unit-difference interface because (1-z)*J_k(z)=k-z*G_k(z): if G_k(z)=0
and k is invertible, J_k(z)/k inverts 1-z. This holds over a product ring
without field cancellation. [the principal-root argument](PRINCIPAL_ROOT_INTERFACE.md)
gives the proof and charged preparation. For each q_i|m use the
coupled root zeta_i=omega^E_i where E_i is its CRT idempotent. For j<q_i,
H_j=product_(1<=a<=j)(1-zeta_i^a) is a unit. The ring-valid Newton-basis
identity gives its Fourier matrix

    F=A*T*diag(beta_j/H_j)*T^t*A,
    beta_j=(-1)^j*zeta_i^(j(j-1)/2).

[The ring-valid Fourier proof](RING_VALID_FOURIER_TOEPLITZ_PROOF.md) proves this with no field cancellation
or H_(q_i) inverse. The dyadic convolution and displacement/dirty-replay
printer gives O(log^35(R0+2)) local matching rounds; every intermediate,
copy and port is counted and every borrowed position restored. These
are effective polynomial-in-R0 setup lists, not runtime arrays outside
the parent width ([exact-width printer proof](DYADIC_TO_EXACT_WIDTH_PRINTER_PROOF.md)).

Complete each local edge matching on the even q_i+1 axis by pairing its
remaining positions, including the pre-existing dummy, with mu=0. The
number remaining is even. These zero shears are identity on arbitrary
incoming values. Move the pairs to canonical positions by the generated
local permutation and retain all three C/four diagonal slots on every
pair. The intermediate word may mix a dummy or I coordinate; only its
completed identity/shear boundary is used for restoration or cropping.

At a synchronized round the actual tensor product of local words is
three full native K calls and four product-diagonal slots, with separately
charged route-in and route-out. It is multiplication of operator words,
not an additive expansion into 2^t terms. Each C acts independently on
the literal D A_p lanes. Every completed word equals a shear over the
original S, restoring the i-helper subspace. The native CRT and controlled
routes preserve every dummy-pattern class at their completed boundaries.

## 4. Complete invoice and ordinary output

There are O(L0*R0*log^35(R0+2)) local coefficient records. Their selector
exponents have O(D log p) bits, and every power/diagonal/unit preparation
is done once per such record. All preparation, archives, shape lists,
route settings and coefficient arithmetic cost a fixed polynomial in
R0,D,L0 (p fixed), hence n^o(1). None is done per global data sample.

An ordinary B product costs O_p(D*polylog L0): carry-free integer packing uses coefficient slots O(log D) bits, followed by SS multiplication and monic f reduction. Public integer-modulus reciprocals use short precision O(log D) for this work; reversed monic reciprocals have their actual quotient precision. No arbitrary modular inverse is a runtime oracle.

The two transform outputs are multiplied pointwise at the M native-grid positions, including the prescribed zero dummy positions. This is an explicit scan of M ordinary B products, costing O_p(M*D*polylog L0) from the scalar-product bound above. The pointwise phase is not a unit-cost operation.

For one global diagonal slot, prefix products of already prepared local
weights require fewer than2M B products (the sum of all prefix cardinalities
is <2M). Applying that table to M samples is a separate M-product scan.
Copying/inverses/erasure and all head returns have the same secondary cost.
Thus diagonal work per slot is O_p(MD*polylog L0), not O(Mt) B products
and not M new selectors. All round counts are fixed powers of log R0,
hence fixed powers of log L0.

Native phase/routing/CRT calls have volume 2MD*bitlength(p)=Theta_p(n),
cost O_p(n*L0^gamma*polylog L0) after summing their secondary counts.
The fixed D threshold dominates P_*(R0+1,Ldock), so the native generators
and gauges are priced rather than assumed free. All addresses are actual
ordinary/tensor indices at the declared completed boundaries.

For psi put d=alpha-D. Its component has v=dm=N*theta coefficients.
SS computes its product using inner stride2d and long integer-modulus
precision O(L0), preventing both band overlap and coefficient carries.
The full alpha-row monic division by psi uses D+1 reciprocal coefficients,
not a short degree-d product reciprocal. Its total cost is

    O_p(N*theta*L0²*polylog L0)=O_p(N*polylog L0),

by (2). All full coefficient-CRT row maps cost O_p(N*polylog L0) as well.
This complement is computed and recombined, never silently discarded.

Run two completed forwards, pointwise B products and the inverse. Initial
invalid dummy entries are zero and remain zero at those boundaries; their
point products are zero too. The inverse uses the genuine m^-1 on this
reached valid subspace. It is not an inverse assertion for arbitrary
nonzero dummy fibres. Reconstruct f AND psi, invert the top map and crop.
Because N>2n-1, the zero-filled cyclic product is the full ordinary product
of degree<=2n-2. Output all 2n-1 canonical p-residues. Input/output scans,
projection of restored i-helper coordinates and cleanup cost O_p(n).

Combining these costs proves (1) for e=1. The completed services, loop
controllers and metadata algorithms form a fixed finite family. Their
banks can be renamed/reused on a fixed tape set; recursive setup stacks
are ordinary tape data. Joins and return scans are included. There is no
input-dependent tape count, full archive lookup per record, free tensor
transpose or implicit growing-algebra multiplication instruction.

## 5. Fixed extensions

For fixed e choose a fixed F_p-basis of F_(p^e) and its finite structure
constant table. A scan separates the two inputs into e component streams.
Use the prime-field machine for the e² component-pair products, serially
reusing the same call banks. Accumulate the fixed linear combinations in
e output streams and merge them coefficient by coefficient. All table
operations and codecs cost O_(p,e)(n); e² calls and their literal joins
are a fixed constant factor. Leading zeros and all 2n-1 positions are
retained. This is an explicit fixed-field algorithm. Its full machine formalization is a separate verification question.

The reduction proves the stated bound under the named native imports. The quotient selector, ordinary endpoint reconstruction, and host-cost composition are supplied explicitly. The named native services remain external dependencies; this note does not claim a kernel-checked end-to-end multiplier or a new native phase exponent.
