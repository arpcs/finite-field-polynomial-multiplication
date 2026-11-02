# Moment compilation and root-reserve estimates

This note records detailed inequalities for the finite precompiler and the root reserve in the compiled rank-one word, followed by the charged native-routing reconstruction. The arguments supplement the source-level service proofs; they do not replace the cited Stage2 theorem.

## Fix one moment parameter and define the zero rank convention

Fix a real t with 0<t<1 and assume P_t<=T_t for this t. Then for every
rational z with t<z<1, ... No bound for every moment t in (0,1) is
required. The application fixes t=1-173/50000 and z=1-3459/10^6>t.

Define B(0)=1, F(0)=0 and ell(0)=0 for the induction. A rank-zero
complement is identity and may simply be omitted, including from the
batching divisibility list. For positive rank, the recipes have positive
productive count. Thus there is never division by a zero productive count.

The flow has at least one source. When its height is G, the class at
depth G has empty target word and column count at most J^G. It is
admissible because m J^G<=m L^G<=n. Choose the smallest depth having
an admissible unit. If depth zero, that unit's target slots are sources;
otherwise no admissible parent exists at the previous depth, so its
target slots are unfed sources. Hence the averaging denominator S is
positive, even if the lower bound L is not attained by a target rank.

With source weights w_s and exit multiplicities x_e normalized by S,
the exact recurrence is

    ell(n)=sum_s w_s ell(n-s)+sum_e x_e ell(e),
    sum_s w_s=1,  sum_e x_e e^t<=sum_s w_s s^t.

For t<z0<z, s>n/m and e<=E(n), the two estimates are

    sum_e x_e e^z0
      <=(m E(n)/n)^(z0-t) sum_s w_s s^z0,

    n^z0-(n-s)^z0 >= z0 m^(z0-1) s^z0.

E(n)<=J(n/m)^(log J/log L)=o(n), so the first coefficient eventually
is less than half the fixed positive coefficient in the second. Strong
induction gives ell(n)<=A n^z0. Some finite N therefore has ell(N)<N^z.
For rational z=p/q the stopping test is the exact integer comparison
F(N)^q<B(N)^q N^p. This is a terminating finite construction before
later input widths vary; it is not a compiler oracle or an input-sized
advice table.

## General root reserve for the compiled rank one word

After precompilation, fix ambient dimension N0>=2, productive count B0,
the finite owned/route inventory, and an eligible odd address prime q.
All paid projectors have rank one. Put

    Lcov=B0*|GL_(N0)(F_q)|,
    A_w=q^(N0^2*(w-1)),  W_w=Lcov*A_w.

In the good-child lemma a rank-one request uses width floor(n/N0).
The fallback children have no larger width. Apart from the nonrecursive
base-supplier leaves, every child therefore has at most half the parent's
atom count. A safe path budget is

    D0=2*(ceil(log2(E+1))+1).

This bound applies to the compiled rank-one word under the stated contraction and cover assumptions.

Fix w=ceil(E^(1/250)) at the root. Choose the least r0 with
q^(2r0)>=W_w^D0, then increase it by fewer than w digits to r so that
w divides E-r. Since N0,B0,q are now constants,

    log_q W_w=log_q Lcov+N0^2*(w-1)=O_(N0,B0,q)(w),
    r=O_(N0,B0,q)(w log(E+2))=o(E).

The finitely many E for which r>=E use the direct branch. Exchange
the two high r-digit fields and place the right high field before the
low head field, as in the ordinary-swap wrapper.
Those short moves cost O(Vr). Their joined q^(2r) row values are padded
ONCE to

    R'=W_w^D0*ceil(q^(2r)/W_w^D0)<2*q^(2r).

They supply an outer factor and D0 consecutive W_w cover slots. This
is grouping a complete numeric range, not entrywise radix conversion.

A child fixes only a productive role and a low matrix type, consuming
one fresh cover slot. It retains all A_w high matrices as complete
earlier spectators. At depth d, retained-high multiplicity A_w^d times
unused-stock size R'/W_w^d is exactly R'/Lcov^d. Thus child volume is
divided by Lcov, not by W_w. There is no second high-matrix saving.
Sibling children reuse the restored stock. Parent inactive banks stay
below their stack tops; the finite owned-bank inventory travels with
the active stream and is cleared at its prescribed boundary. Only the
completed root endpoint restores the padded row support for cropping.

The density calculation and the full fallback give the fixed profile

    mu_sigma <= (F0/B0)*N0^(-sigma)*(1+64*N0^5/q)<1,
    mu_1<=mu_sigma,  sigma=1-C1.

Ports cost a constant times G(w)=(w+1)^tau_L polylog(w+2) per active
volume; generated later-target adapters cost a constant times n. Hence

    T(n,w)<=sum_j c_j T(b_j,w)+C*n+C*G(w)

has the bound A*n+B*n^sigma G(w), by induction using the two strict
moment gaps. Both constants depend on the fixed finite winner; neither
depends on E. Ancestor coefficient evaluation is polynomial in E and
is absorbed by the complete q^w target fibers, as in rootdecoder with
E<=w^250. This generalizes the detailed reserve argument without an
unpriced extra row reservoir or a pad at every child.

The complete wrapper costs

    O(V*(E/w+(E/w)^sigma G(w)+w log(E+2))).

Its leading saving is a_B=(1-1/250)C1+(1/250)a_L. The inequalities
a_B<1/250<1-a_B make both other root terms smaller. Thus making the
general reserve explicit does not alter the claimed exponent.

## Native routing cost

The routing cost follows from the whole-range transpose construction in [the native service reconstruction](NATIVE_SERVICE_CONTRACTS.md):

For every aggregate relocation, the moved objects are two contiguous
complete numeric ranges [A],[B]. Pad them separately to binary powers,
at combined volume factor below four; apply losslessbinarytranspose
from I_tau; crop only after its completed rectangle permutation. Since
A*B<=M, the total address width is at most ceil(log2 M)+2. The cost is

    O(V*L^tau*polylog(L+2)),  L=ceil(log2(2M)).

The remaining native phase costs use P_gamma, with tau<gamma; the
O(log R), global ragged levels and balanced CRT merge depths are only
secondary powers when log R=O((log L)^2). Per-record generator work is
paid by W>=P_*(R,L), as enforced by the chosen coefficient degree D.
This establishes the claimed O(V L^gamma polylog L) native service.
It uses whole-rectangle padding rather than independently padding all
native axes. The original ordinary support is restored before cropping.

The source-level native argument still relies on the exact finite-word identities, source certificates, and the cited Stage2 theorem.
