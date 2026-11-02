# Fourier--Toeplitz factorization over a commutative ring

This note derives the local Fourier factorization over the coefficient
ring used by the host. The identity is the classical Gaussian-binomial /
Newton-basis factorization, not a new Fourier factorization. Its
hypotheses require unit root differences; no field or nonzero-pivot
assumption is used.

Let R be a commutative ring, m>=1, and zeta in R. Assume 1-zeta^s is a
unit for 1<=s<m. Define

    H_0=1, H_j=product_(s=1)^j (1-zeta^s),
    beta_k=(-1)^k*zeta^(k*(k-1)/2).

All H_j used below (0<=j<m) are units. Put A=diag(H_j), and let T be
the lower-unit-Toeplitz matrix T_ij=H_(i-j)^-1 for i>=j, zero otherwise.
Then the literal m by m Vandermonde/Fourier matrix V_ij=zeta^(i*j)
satisfies

    V = A T diag(beta_k*H_k^-1) T^t A.              (1)

There is no inverse of H_m, which may be zero for an m-th root. The
matrix transpose in (1) is an algebraic transpose, not an uncharged bit
transpose of the stored array.

## 1. A polynomial Newton-basis expansion

Let P_0(X)=1 and

    P_k(X)=product_(a=0)^(k-1) (X-zeta^a).

The defining identity is X P_k=P_(k+1)+zeta^k P_k. For 0<=k<=j<m
write C(j,k)=H_j*(H_k*H_(j-k))^-1, with values zero outside that range.
The boundary values are C(j,0)=C(j,j)=1. For 1<=k<=j the common unit
denominator H_k H_(j+1-k) gives

    C(j,k-1)+zeta^k*C(j,k)
      = H_j/(H_k H_(j+1-k))
          *[(1-zeta^k)+zeta^k*(1-zeta^(j+1-k))]
      = H_(j+1)/(H_k H_(j+1-k))
      = C(j+1,k),                                (2)

whenever j+1<m. The edge values at k=0 and k=j+1 agree separately.
This calculation multiplies explicit unit inverses; it never cancels an
arbitrary nonzero ring element.

Starting with X^0=P_0, multiply by X and use the P recurrence and (2).
Induction proves the polynomial identity

    X^j=sum_(k=0)^j C(j,k) P_k(X),  0<=j<m.        (3)

It is an identity of formal polynomials over R, so the proof does not
infer polynomial equality from finitely many evaluations.

## 2. Evaluate at the geometric nodes

If i<k then P_k(zeta^i)=0, because one defining factor has a=i. If i>=k,
factor zeta^a out of each term (no inverse of zeta is required):

    P_k(zeta^i)
      = product_(a<k) zeta^a*(zeta^(i-a)-1)
      = beta_k * product_(s=i-k+1)^i (1-zeta^s)
      = beta_k * H_i * H_(i-k)^-1.               (4)

The last equality uses only the prepared inverse of H_(i-k). For k=0
both empty products are one and (4) still holds.

Substitute (4) into (3), evaluated at X=zeta^i. This yields

    zeta^(i*j)
      = H_i H_j * sum_(k=0)^min(i,j)
          beta_k * H_k^-1 * H_(i-k)^-1 * H_(j-k)^-1. (5)

The right side is exactly the (i,j) entry of (1), proving the factorization.

## 3. Units and the actual host application

For the host's q-th root zeta=omega^(E_i), p does not divide the odd
prime q and zeta is principal in every residue field. Thus 1-zeta^s is
a unit for every 0<s<q; unit lifting through the nilpotent ideal gives
the stated R=S_P hypotheses. beta_k is also a unit because zeta is a
unit. Therefore all three outer diagonal factors in (1) have explicit
unit entries, T has unit diagonal, and its inverse sequence exists
without dividing by any nonunit. The formula is valid over Z/p^nu and
the full product of unramified host factors; there is no field elimination.

The exact-width compiler executes T and T^t on the original local
coordinates, with arbitrary-dirty replay and counted intermediate ports.
The transpose word reverses order and reverses each source/target
orientation with the same scalar weight. It does not require a separate
ring-element array transpose. Multiplication by A and the middle diagonal
are separately charged B scalar scans, including their physical I lanes.

At m=1 all matrices in (1) are [1]. At m=2 it gives V_11=1-H_1=zeta
with H_1=1-zeta, matching the two-point case. At a forbidden repeated
node, an H_j need not be a unit; (1) is then outside the theorem's
hypotheses and cannot be justified by a field-style nonzero argument.

This derivation supplies the local ring identity used by the host proof.
It does not price the native matching compiler or establish the imported
phase supplier, root construction, coefficient CRT, or complete
ordinary-output machine on its own.
