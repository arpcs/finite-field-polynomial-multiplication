# Canonical units and selectors in the cyclotomic host

This note gives a refinement of the written uniform low-precision host
construction. The cyclotomic host already contains a unit parameter with
the four inverses required by the three-C shear construction, so no extra
coordinate satisfying T²=2 is needed. The ordinary coefficient function
and asymptotic bound are unchanged. The cyclotomic and geometric unit
identities used here are classical.

## 1. The unit parameter is already in the host

Let P=p^nu, R=Z/PZ, p odd, and let S=bitlength(P). Take the existing HvdH conductor alpha: an odd
squarefree integer >1, coprime to p, with f=Phi_alpha, D=phi(alpha). Write

    S=R[U]/f(U),   A_P=R[I]/(I²+1),   B=A_P[U]/f(U).

The residue U of the polynomial variable has U^alpha=1 and is primitive
of exact order alpha in every residue field. Thus U and U-1 are units.
Here is an explicit inverse construction, without factoring B. Put
c=f(1), and form the polynomial H(X)=(f(X)-c)/(X-1). Then

    (U-1)*H(U)=-c.

For squarefree alpha, c is its prime factor q if alpha=q, and c=1 if
alpha has at least two distinct prime factors. The alpha factor list is
already supplied by host setup. In the first case q!=p, so c is a unit
modulo P; in the second its inverse is one. Hence -c^-1*H(U) is the
explicit inverse of U-1. Computing H uses cumulative coefficient sums
and O(D) scalar work. Metadata enlargement in the asymptotic branch
forces at least two factors, but the prime case is covered too.
An inverse of U itself can be obtained from U^alpha=1, or directly from
the constant term f(0)=1 by dividing f(X)-1 by X.

Since alpha is odd, for j=1,2 the finite geometric identity gives

    (1+U^j) * sum_(k<alpha) (-U^j)^k
      = 1-(-U^j)^alpha = 2.

Multiplying the sum by h=2^-1 supplies the inverses of U+1 and U²+1.
Therefore uP=U supplies exactly the four admissible-parameter witnesses
needed by the generic three-C construction. There is no p=3 or p=5
exception and no need to adjoin T. The proof uses the actual cyclotomic
host; it is not a claim that the bare Gaussian ring at p=5 can synthesize
a shear. Its F5 quotient obstruction is unchanged.

The geometric sums can be prepared by the binary pair recurrence

    (z^(2a),G_(2a))=(z^a*z^a, G_a+z^a*G_a),
    G_(2a+1)=G_(2a)+z^(2a),

with G_0=0. This uses O(log alpha) S products and charged scalar scans.
Even direct alpha-term evaluation would be polynomial in D in the chosen
host because alpha<=2D eventually; it is one shared parameter preparation,
not a per-global-record computation. Thus it lies in the existing n^o(1)
setup invoice.

An alternative uses the existing Fourier-root witness. The principal
transform root omega has odd order m>1, so
omega-1 is a unit by that witness, while omega+1 and omega²+1 have the
same geometric inverses at odd length m. A binary sum evaluator costs
O(log m) S products. The adapter is algebraic; its recursive sum
definition is not asserted to be the fast evaluator. The finite small
cases with m=1 use the direct branch. The canonical U route works
independently of m.

## 2. Actual native coefficient lanes

The preferred host is B=A_P[U]/Phi_alpha. A record has D coefficients in
the literal basis 1,I over R, occupying 2DS bits. Each native C acts on
D independent A_P lanes. This is the P_gamma interface. There is
no variable field isomorphism, chosen root of -1 in F_p, or searched
root of 2. At p=1 mod4 A_P may split; the literal monic quotient remains
free and the unit/word identities hold in the product algebra.

The residue fields of A_P have degree s=1 or2. A cyclotomic component has
degree r0=ord_alpha(p), with r0|D; after tensoring, component degree is
lcm(r0,s)|D, because D=phi(alpha) is even for odd alpha>1. Consequently
E=(p^D-1)p^nu suffices for exact local unit selectors with nilpotence
bound nu, as shown in [the quotient selector proof](QUOTIENT_INSTANTIATION.md).
The older 2D-degree bound also remains valid.
The universal finite-algebra
selector is available with rank d=2D, at polynomially larger setup cost.
No selector is evaluated on global tensor samples.

General B scalar products still use old carry-free Kronecker arithmetic
and monic f reduction, at O(D*S*polylog L), with the short-precision public-modulus cache and
actual polynomial-reciprocal precision. The lost T coordinate removes
cross-coupling between two A_P lanes; it does not make B multiplication
a unit-cost phase operation.

The unchanged metadata threshold D>=Delta already makes 2DS dominate
the fixed generator polynomial, since S>=2. Every whole-grid phase
invoice now has volume 2MDS, compared with the old conservative 4MDS.
Private binary suffix/rectangle pads are still retained only through
their completed operations. There is no global M-to-power-of-two kernel.

## 3. Arbitrary coefficients and completed-word boundaries

Feed the shared canonical uP and its four inverses into the generic
idempotent/Newton parameter patch for each emitted local coefficient mu.
It returns u,uInv,minusInv,plusInv,c,cInv with u²+1=c*mu, all required
unit witnesses, and the three-positive-C word proved in
[the finite-algebra theorem](OPTIMAL_THREE_C_FINITE_ALGEBRA_THEOREM.md).
Admissibility is the only hypothesis on the shared parameter; it need not
equal 1+T.

The completed shear is U(mu) over the original S. Its intermediate
diagonals may use I, but completed local words restore the S subspace.
Retain all I-helper coordinates and dummy addresses until their specified
completed boundary. The Fourier root, genuine inverse normalizer,
point products, zero-filled valid dummy subspace, both coefficient-CRT
components and final ordinary coefficient prefix remain as in the host
proof. No input/output or coefficient-domain relaxation is made.

The local template count changes from ten C calls to three; the native
record volume changes from 4MDS to 2MDS. These are constant improvements.
The leading exponent gamma, secondary-log allowance, fixed tape count
and all uniformity/setup requirements remain the same. The conditional
uniform odd-modulus theorem follows by the already written acyclic
seed/integer/high-width/prime-power-CRT chain; this refinement introduces
no call to the target algorithm inside its seed scalar backend.

## 4. Scope and formal status

The algebraic word, nilpotent iteration, scalar patch, and selector-to-word
composition have separate checked components. The canonical quotient and
its cyclotomic evaluation facts are established here as written arguments;
they are not a formalization of HvdH's host construction. The native
phase/time services and their fixed-tape source proof remain named
dependencies. This note does not assert a whole-multiplier kernel proof.
