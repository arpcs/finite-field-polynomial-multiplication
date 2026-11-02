# Principal roots provide explicit unit differences

HvdH §2.2 defines a principal root by its order relation and vanishing
nontrivial character sums, with the transform length invertible in the
ring. Proposition 3.8 supplies such roots in its cyclotomic algebra. The
Fourier modules used here require explicit inverses of each nontrivial
root difference. The identity below derives those inverses without a
domain or field assumption.

Let G_n(z)=sum_(0<=j<n) z^j and
J_n(z)=sum_(0<=j<n)(n-j)z^j. Direct telescoping gives

    (1-z)*J_n(z)=n-z*G_n(z).

For example J_1=1, J_2=2+z; at general n, induction uses
J_(n+1)=J_n+G_(n+1) and (1-z)G_(n+1)=1-z^(n+1).
Thus if G_n(z)=0 and n*nInv=1, then J_n(z)*nInv is an explicit
inverse of 1-z. Apply this with z=omega^r for every 0<r<n. The
traditional principal-root definition therefore implies the exact
PrincipalRootWitness used by the checked Fourier/three-C adapters.
Invertibility of n is essential: over Z/4, omega=-1 has zero length-two
nontrivial character sum but 1-omega=2 is not a unit.

Root transport can now be stated without silently changing definitions.
The HvdH root rho0 has order N/q0 in S0=F_p[U0]/Phi_alpha0, where
q0 divides alpha0. First set omega0=rho0^(alpha0/q0), of principal
order m0=N/alpha0. If J=alpha/alpha0 is the appended conductor factor,
map U0->U^J and set omega=map(omega0)^J, of principal order m=m0/J.
Unital ring maps preserve the character-sum identities and explicit
inverses; taking the divisor-order power preserves principality.
For q_i|m the local root omega^E_i is principal of order q_i.
All lengths are prime to p, so their cast inverses exist in F_p.

Preparation is still charged. The recursive weighted sum is a proof of
unit existence, not a declaration of a free inverse or fast evaluator.
For the ACTUAL local Fourier roots, q_i<=R0, direct weighted sums take
polynomial(R0) B operations per local root and hence n^o(1) total setup.
Alternatively an extended Euclidean calculation in F_p[U] computes the
inverse of each public unit polynomial modulo Phi_alpha in polynomial(D)
time. The identity guarantees coprimality. The host's shared canonical U
parameter has the independent explicit divided-difference/geometric
inverses already proved, so no length-m linear sum is run per record.

This is an algebraic adapter for the principal-root interface; it does
not formalize HvdH's host construction or the full tape program. The
primary source is [HvdH, cyclomult, §2.2 and Proposition 3.8](https://www.texmacs.org/joris/cyclomult/cyclomult.pdf).
