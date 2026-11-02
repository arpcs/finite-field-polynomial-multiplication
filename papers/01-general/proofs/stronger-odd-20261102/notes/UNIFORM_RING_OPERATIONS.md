# Quotient selector for the uniform odd-modulus reduction

This note proves the selector identities in the actual odd-modulus
coefficient quotient. The result preserves the uniform reduction's
native-service hypotheses, moderate-precision host restrictions, ordinary
endpoints, exponent, and cost bound.

## The actual quotient and residue identity

Let p be an odd prime, nu>=1, alpha>1 odd and squarefree, and p not divide
alpha. Put D=phi(alpha), Q=p^D, and

    B=(Z/p^nu)[I,U]/(I^2+1,Phi_alpha(U)).

Both relations are monic. Reduction modulo p is exactly

    Bbar=F_p[I,U]/(I^2+1,Phi_alpha(U));

the kernel B -> Bbar is pB. Indeed the monic basis I^epsilon U^j,
epsilon in {0,1}, 0<=j<D, gives unique coefficients before and after
reduction. This also makes p^nu B=0 literal, without a local-factor
decomposition.

D is even. Euler gives Q=1 modulo alpha, and p odd with D even gives
Q=1 modulo 4. In Bbar, U^alpha=1 and I^4=1, so U^Q=U and I^Q=I.
The D-fold Frobenius is a ring endomorphism fixing F_p and these two
generators. Consequently x^Q=x for every x in Bbar.

For any mu in B let y=mu^(Q-1). Its defect satisfies

    y^2-y=mu^(Q-2)*(mu^Q-mu) in pB.                 (A)

The quotient may contain zero divisors; none of this argument cancels a
nonunit or assumes that the quotient itself is a field.

## Power lifting with an exact defect factor

Suppose z^2-z=p^(t+1)b, t>=0. Write d=z^2-z. The exact power Taylor
identity, with its polynomial remainder R_p, gives

    (z^p)^2-z^p = (z+d)^p-z^p
      = p*z^(p-1)*d + d^2*R_p(z,d)
      = p^(t+2)*(z^(p-1)*b + p^t*b^2*R_p(z,d)).    (B)

Thus each p-th power raises the defect precision by at least one.
Starting from (A) and iterating nu times proves that

    f=y^(p^nu)=mu^((p^D-1)*p^nu)

is exactly idempotent: its defect lies in p^(nu+1)B=0. There is no
binomial valuation estimate, irreducible-factor search or computed
Artinian decomposition in this construction.

Modulo p, y is idempotent, hence y^(p^nu)=y, since p^nu>=1. Therefore

    (1-f)*mu = (1-y)*mu = mu-mu^Q = 0 modulo p.

Set v=(1-f)*mu. Then v in pB, so v^nu=0. These are exactly the generic
selector premises used by the checked nilpotent patch and three-C word.
The canonical U and its four explicit inverse witnesses are unchanged.

For nu=1 the stronger direct identity holds in B:
mu^Q=mu. Then f=mu^(Q-1) is idempotent and (1-f)*mu=0 immediately.
No lift or Newton step is needed for the fixed-field theorem.

## Costs and proof status

The general selector exponent has O(D log p + nu log p)=O(DS) bits,
where S=bitlength(p^nu); the looser O(D*S) bound suffices. Binary powering
and the nilpotent patch are polynomial in the public local parameters.
Under the old moderate-precision restriction S<=L^C and its chosen
log D=O_C((log L)^4), the number of local records times this cost is
n^o(1). The selector is prepared per local coefficient record, never per
global sample. This adds no term to the old host invoice.

The root difference interface is supplied by
[the principal-root argument](PRINCIPAL_ROOT_INTERFACE.md) at residue level. Hensel lifting
a simple root preserves those unit differences, because an element of B
whose residue is a unit has inverse a*(1+e+...+e^(nu-1)) when 1-a*x=e
lies in pB. The derivative of the host root equation is a unit since p
does not divide its length. The original uniform proof already charges
that lift and both coefficient CRT components.

The remaining uniform-in-modulus steps are those in Sections 4 and 5 of
the uniform odd-modulus theorem. This selector argument does not replace
them with a fixed-p argument and changes neither coefficient-bit
accounting nor the all-odd-modulus conclusion.

OddPowerSelectorLiftNov02.lean checks (B), its iteration and exact
idempotence under p^nu=0. OddFrobeniusThreeCNov02.lean checks the generic
fixed-field selector-to-word adapter. The nested monic quotient and its
Frobenius identity are proved here in writing, but have not been
instantiated as that actual carrier in Lean. These standard algebraic
identities close an interface in this project; no novelty claim is made
for Frobenius or power lifting themselves.
