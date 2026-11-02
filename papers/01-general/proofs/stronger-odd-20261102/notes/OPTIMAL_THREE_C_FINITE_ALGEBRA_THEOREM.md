# Three-call diagonal word for shears over finite odd algebras

This note states a constructive finite-ring factorization and bounds its
local preparation algorithm. Its ingredients include finite
Artinian-ring decomposition, power idempotents, Newton--Schulz lifting,
and diagonal conjugation.

Hadamard form: this C is diagonally equivalent to the
unnormalized Hadamard H=[[1,1],[1,-1]]:
C=diag(A,B0)*H*diag(1,-i). All these diagonal entries are units.
Thus the call-count statement is equally a fixed-Hadamard/diagonal result;
it is not specific to this kernel. Any priority claim would require a
separate comparison with the factorization literature. The broad
factorization method and its standard algebraic ingredients are prior art.

The proof only needs an admissible shared uP with uP,uP-1,uP+1,uP²+1
units. The Pell unit below is one concrete choice. In the actual
cyclotomic host the existing U supplies those units, so the extra T
coordinate is unnecessary; see [the canonical host reduction](CANONICAL_HOST_REDUCTION.md). This does
not invalidate the standalone fixed-carrier theorem stated next.

## Statement

Let p be an odd prime, nu,d>=1, and let B be any commutative unital algebra
free of rank d over Z/p^nu. Suppose i,t belong to B with i^2=-1 and t^2=2.
Put h=2^-1, A=(1+i)h, B0=(1-i)h, and

    C = [[A,B0],[B0,A]].

For every mu in B, including zero and zero divisors, there are explicitly
constructible unit diagonals D0,D1,D2,D3 such that

    D0 C D1 C D2 C D3 = [[1,mu],[0,1]].                 (1)

The construction has the same three positive C slots for all mu. It uses
only arithmetic in B, a public exponent with O((d^2+d*nu)log p) bits, and
O(log(d*nu+2)) inverse-square-root iterations. It requires no factorization
of B, residue-field basis conversion, zero test, or branching on mu.
The finite free algebra need not be etale or reduced.

For any nonzero mu, no word with at most TWO calls selected from C,C^-1
and arbitrary intervening unit diagonals equals that shear. Thus three is
the exact optimum for this stated two-coordinate generator model.
Permutations, extra coordinates, extra kernels and additive sums of
operators are outside this lower bound.

## 1. An explicit unit/nonunit projector without factoring the algebra

Let

    E = p^(d*nu) * product_(j=1)^d (p^j-1).

This exponent is positive and has O((d*nu+d^2)log p) bits. Write the finite
Artinian ring B as a product of local rings B_l for the proof only. Its
cardinality is p^(d*nu). If B_l has cardinality p^m_l and residue field
F_(p^s_l), then m_l<=d*nu and s_l<=d: the residue field is a quotient of
the d-dimensional F_p-vector space B/pB. Its unit group has cardinality

    |B_l^x| = p^(m_l-s_l)*(p^s_l-1).

That order divides E, so every local unit has E-th power one by Lagrange's
theorem. The maximal ideal has nilpotence index at most m_l. One way to
see the bound is that each nonzero successive ideal power strictly
decreases cardinality by a factor at least p; equality of two adjacent
powers would give zero by Nakayama's lemma. Thus a local nonunit's E-th
power is zero, since E>=d*nu>=m_l.

Consequently f=mu^E is an exact central idempotent, one on precisely the
components where mu is a unit. Put r=1-f and v=r*mu. Then

    f^2=f, r^2=r, fr=0, f+r=1, and v^(d*nu)=0.       (2)

All algorithmic operations are powers and products in the original B;
the local decomposition is not computed. In the etale cyclotomic host,
the smaller existing exponent (p^(2D)-1)p^nu can replace E, with nilpotence
bound nu. The present larger exponent removes that special residue-degree
assumption and handles ramified algebras too. It changes preparation cost.

## 2. A square root near one using only dyadic operations

Set a=1-v. Starting with x0=1, define

    delta_j = 1-a*x_j^2,
    x_(j+1) = x_j*(1+h*delta_j).

Since 2h=1, direct multiplication gives the exact identity

    delta_(j+1) = h^2*delta_j^2*(3+delta_j).          (3)

For clarity, (1+h*delta)^2=1+delta+h^2*delta^2,
a*x^2=1-delta, and 1-h^2=3h^2 because 4h^2=1. Multiplying these two
polynomials proves (3). Starting with delta_0=v, induction yields
delta_j in the principal ideal (v^(2^j)). Take k with 2^k>=d*nu;
(2) then gives delta_k=0. Put x=x_k and w=a*x. We have

    a*x^2=1,   w*x=1,   w^2=a=1-v.                 (4)

This iteration uses no inversion or division beyond h. Its number of
steps is O(log(d*nu+2)). These are exact nilpotent-ring identities, not
analytic approximations or numerical convergence arguments.

## 3. One parameter whose quadratic expression is associated to mu

Let uP=1+t and qP=uP^2+1. Their explicit inverses are

    uP^-1=t-1, (uP-1)^-1=t*h,
    (uP+1)^-1=(2-t)*h, qP^-1=(2-t)*h^2.

These follow only from t^2=2 and 2h=1. On the other component set
uN=i*w. It is a unit with inverse -i*x, by (4). Also

    (uN+1)(1-uN) = 2-v,
    (uN-1)(-uN-1) = 2-v.

The inverse of 2-v is the explicit finite sum

    J = h * sum_(j<d*nu) (h*v)^j,

because (h*v)^(d*nu)=0. Thus uN+1 and uN-1 have inverse witnesses
(1-uN)J and (-uN-1)J respectively.

Define, in the original ring without componentwise tests,

    u = f*uP + r*uN,
    uInv = f*(t-1) + r*(-i*x),
    plusInv = f*((2-t)*h) + r*((1-uN)*J),
    minusInv = f*(t*h) + r*((-uN-1)*J).

Orthogonality of f,r proves these are the inverse witnesses for u,u+1,u-1.
Put

    c = f*qP*mu^(E-1) + r,
    cInv = f*mu*qP^-1 + r.

Since mu^E=f, multiplication gives c*cInv=1. Moreover

    q := u^2+1 = f*qP+v = c*mu.                     (5)

The crucial point is that c is a unit while q can vanish or be a zero
divisor. Nothing below divides by q, mu, or the desired shear coefficient.

## 4. The actual three-C word

For any u,u-1,u+1 units, put b=(u-1)*plusInv. Direct multiplication gives

    W := C diag(u,1) C diag(b,1) C
       = [[alpha,beta],[0,delta]],

    alpha = -2*i*A*u*plusInv,
    beta  = A*(u^2+1)*plusInv,
    delta = -i*A*(u-1).                             (6)

For example C diag(u,1) C has entries
(i*h*(u-1), h*(u+1), h*(u+1), -i*h*(u-1)). Multiplication by
diag(b,1) and C gives (6), using (u+1)b=u-1. Its four entries are
an algebraic identity over the commutative coefficient ring.

The elements alpha and delta are units because i,A,2,u,u-1,u+1 are
units. Explicit witnesses are

    AInv=1-i,
    alphaInv=h*i*AInv*uInv*(u+1),
    deltaInv=i*AInv*minusInv.

Normalizing W on the left gives U(kappa), where

    kappa = alphaInv*beta = i*h*c*mu*uInv.

Define the unit

    z = -2*i*u*cInv,     zInv=i*h*uInv*c.

Then z*zInv=1 and, by (5), z*kappa=mu. Consequently

    D0=diag(z*alphaInv,deltaInv), D1=diag(u,1),
    D2=diag(b,1), D3=diag(zInv,1)

satisfy (1). Every displayed diagonal is a unit diagonal. In particular,
the construction works at mu=0 with exactly the same three C slots;
there is no cancellation based on a runtime zero test.

For unit mu, the fixed Pell parameter uP already suffices and the
construction reduces to diagonal conjugation of the fixed word

    diag(B0,A*t) C diag(1+t,1) C diag(t-1,1) C diag(i*t,1)=U(1).

For nilpotent mu, u=i*w suffices. The idempotent formula glues these cases
inside one ordinary ring computation rather than branching on factors.

## 5. The two-call lower bound

Here C^-1=[[B0,A],[A,B0]], and A*B0=h, A^2=i*h, B0^2=-i*h.
Both A and B0 are units. After collecting adjacent diagonals, every
two-call word has middle C^eps diag(x,y) C^eta, with x,y units. For
equal signs its off-diagonal pair is

    (h*(x+y), h*(x+y)).

For opposite signs it is (i*h*(x-y), -i*h*(x-y)) or the reversed pair.
Thus one off-diagonal vanishes exactly when the other does. Multiplication
on either side by unit diagonals preserves this zero pattern. A nonzero
upper shear has one zero off-diagonal and one nonzero off-diagonal, so
two calls cannot realize it. A one-call word has both off-diagonals units,
and a zero-call word is diagonal. This proves the lower bound over any
nonzero commutative coefficient ring with the stated dyadic Gaussian
coefficients, including zero divisors. The restriction to unit diagonals
is natural; over a commutative ring, a product equal to an invertible
matrix forces every square diagonal factor to have unit determinant.

## 6. Cost and scope

Computing E takes polynomial time in its bit length. Each local public
mu needs its own binary powers, inverse-square-root sequence, geometric
sum and scalar preparation: O(log E+log(d*nu+2)+d*nu) B operations is
a safe elementary bound. This is not one preparation shared by unrelated
mu values. For the host's polynomially many local coefficients, d=2D,
log D=O((loglog n)^4), and S<=log^C n; all this work is n^o(1).
The global tensor diagonals are still generated from already prepared
local units. The selector or Newton computation is never applied per
global data record. Cross-lane B arithmetic, archives and native routing
retain their separately charged costs.

The construction supplies a three-C local shear template with fixed
topology; applying it does not alter the asymptotic exponents. It does not
prove a faster native phase supplier or discharge the imported Stage2
machine theorem. The written finite-algebra argument, any formalized
special cases, and finite checks establish different scopes and are
reported separately.
