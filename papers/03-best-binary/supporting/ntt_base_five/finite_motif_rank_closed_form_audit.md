# Finite motif rank totals: closed-form audit

29 October 2026. Proof-only reconstruction of the imported finite motif label and rank count used by the rational-frame interchange and its lifted ternary phase version. This note derives the counts from the generic graph parameters and gate labels; it does not replay the fixed scalar-routing certificate or prove the global multiplication theorem.

## Graph and dimensions

Let the graph vertices be the triples in \(\binom{[h]}3\), adjacent when their intersection has size one. Write

\[
 v=\binom h3,\qquad z=3\binom{h-3}{2}.
\]

For each triple, choose the shared element in 3 ways and the two elements of the other triple outside it in \(\binom{h-3}{2}\) ways, so its ordered degree is \(z\). The three-stage network has \(N=v^3\) data pairs and \(I=3v^2\) invocations. Each invocation has \(vz\) side roles (one ordered role for each vertex-neighbor pair) and \(h\) center roles. There are two data banks. Thus its total wire count is

\[
 W=2N+I(vz+h).
\]

The formula counts role wires with multiplicity; it does not identify equal labels on different wires.

The factor dimension is \(d=h\) for the rational construction and \(d=h+1\) for its lifted \(\mathbb F_3\) realization. The number of center roles stays \(h\) in both. In the lifted case, the extra coordinate changes the factor dimension and every full-factor rank, but creates no new scalar-network role.

## Common-label inclusion certificate

For the rational frame, take \(F=\mathbb Q^h\) with Gram matrix \(B_0=I-J/9\), and for a triple \(S\), let \(t_S=\mathbf1_S\). Then

\[
 \langle t_S,t_T\rangle=|S\cap T|-1,\qquad
 \langle t_S,t_S\rangle=2.
\]

So every line \(L_S=\langle t_S\rangle\) is nondegenerate and adjacent triples give orthogonal lines. (At the fixed value \(h=100\), the eigenvalues of \(B_0\) are 1 on the sum-zero subspace and \(1-h/9=-91/9\) on the all-ones line, hence the ambient form is nondegenerate.)

For the lifted frame, take \(F=\mathbb F_3^{h+1}\) with form \(\operatorname{diag}(-I_h,1)\), and \(t_S=(\mathbf1_S,1)\). Its norm is \(-2\equiv1\pmod3\), and

\[
 \langle t_S,t_T\rangle=1-|S\cap T|,
\]

which is zero for adjacent triples. These equalities are exact in the stated fields; no rank assertion is inferred merely from reduction modulo 3. Each selected line is unit-norm, so its orthogonal complement is a direct summand of codimension one. For adjacent \(S,T\), the pair of unit lines is an orthogonal direct summand and their joint orthogonal complement has rank \(d-2\).

Here is the uniform stage inclusion argument, valid in either frame. At a fixed stage let \(A=F^{j-1}\), let \(P\) be the prefix tensor line and \(Q\) the suffix tensor line. Set \(B=P^\perp\). Then \(A=B\perp P\), and for the current graph vertex \(t\), \(F=L_t\perp L_t^\perp\). The next stage's center space is

\[
 B'=(P\otimes L_t)^\perp=(B\otimes F)\oplus^\perp(P\otimes L_t^\perp).
\]

The last equality uses the orthogonal direct decomposition \(A=B\perp P\) and the unit line \(L_t\). Side labels involving a neighbor \(s\) use \(L_s\perp L_t\), supplied by the graph edge. This proves every inclusion in the gate table from direct sums and orthogonal complements, without enumerating graph instances:

| Gate role | Label |
|---|---|
| t0, Y-side | \(B\otimes L_t\) |
| t1, Y-center | \(B\otimes F\) |
| t2, X-side | \((B\otimes F)\oplus^\perp(P\otimes L_t)\) |
| t3, X-center | \(A\otimes F\) |
| t4, Y-center | \(B\otimes F\) |
| t5, Y-side | \((B\otimes F)\oplus^\perp(P\otimes L_t^\perp)\) |
| t6, X-center | \(A\otimes F\) |
| t7, X-side | \(A\otimes F\) |

Here X and Y mean the physical banks throughout, including stage 2. In
stage 2 the chronological gate is the inverse of row 7-r of the forward
schedule with its logical source/target banks exchanged. Its physical
wire order is consequently still Y-side, Y-center, X-side, X-center,
Y-center, Y-side, X-center, X-side. Merely exchanging the physical bank
names in the forward order would not have the claimed interstage labels.
The incoming physical X label is (A tensor L_t) tensor Q and its outgoing
label is (A tensor F) tensor Q; the incoming physical Y label is (B tensor L_t) tensor Q
and its outgoing label is (P tensor L_t)^perp tensor Q. The latter is
exactly the next stage's B' tensor next-line tensor Q'. These identities
account for the interstage edges as well as the within-invocation edges.

The table also makes the rank changes explicit. The only decreasing label
edges are the center transition t3 to t4. With a=dim(A), each central
wire drops from rank a*d to (a-1)*d, losing d dimensions; there are h
such wires in an invocation, so the loss per invocation is h*d. The
side residuals have ranks given by the indicated direct summands; in
particular, the complementary side construction uses the neighbor-pair
complement of rank d-2. Thus the total dimension loss is

\[
 L=Ihd.
\]

All other edge ranks telescope with the signed label dimensions. Including the role routing and both data banks, the sum of absolute label-dimension changes is therefore

\[
 s_{\rm label}=Wm-2N+2L,\qquad m=d^3.
\]

This identity is the signed dimension telescope plus twice the total downward variation: a downward change contributes negatively to the signed sum but positively to the absolute sum.

## Endpoint correction and total rank

In the rational-frame version, the source assigns \(-P_{U_a}\) to the X source role, while the first X gate has label \(U_a\) and projection \(P_{U_a}\). The first edge is therefore \(2P_{U_a}\), rank one, even though its label dimensions agree. There are \(N\) such edges. Every other source role is zero and the endpoint label differences have the prescribed full-rank identity. Hence

\[
 s_{\rm rational}=Wm-2N+2L+N=Wm-N+2L.
\]

The lifted phase network has the corresponding one-rank endpoint correction on each of its \(N\) X-to-Y routes: the uncorrected phase product differs from the target by the rank-one phase on \(U_a\); applying the specified single child corrects it. So its total child rank is also \(Wm-N+2L\), with its own \(d,m,L\). This correction is a circuit operation, not a change in the label-dimension telescope. In particular, the rational signed source projection must not be silently counted as an ordinary label edge.

## h=100 closed form and deficit

For \(h=100\),

\[
 v=161700,\quad z=13968,\quad N=4{,}227{,}952{,}113{,}000{,}000,
\]
\[
 I=78{,}440{,}670{,}000,\quad
 W=177{,}176{,}569{,}091{,}445{,}000{,}000.
\]

For the rational frame, \(d=100,m=1{,}000{,}000,L=I\cdot10{,}000=784{,}406{,}700{,}000{,}000\), and

\[
 s_{\rm rational}=W\cdot1{,}000{,}000-N+2L.
\]

For the lifted frame, \(d=101,m=1{,}030{,}301,L=I\cdot10{,}100=792{,}250{,}767{,}000{,}000\), and

\[
 s_{\rm lifted}=W\cdot1{,}030{,}301-N+2L
 =182{,}545{,}196{,}308{,}841{,}424{,}366{,}000{,}000.
\]

For either case,

\[
 \frac{W}{N}=2+3z+\frac{3h}{v}=41906+\frac1{539},
\]

and (N-2L)/N equals 339/539 in the rational case and 337/539 in the
lifted case. Therefore the exact relative deficits are

\[
 \Delta_{\rm rational}=\frac{339}{22587335000000},\qquad
 \Delta_{\rm lifted}=\frac{337}{23271753837835}.
\]

The common denominator factor is 22587335<2^25 and m<2^20,
while each numerator exceeds 2^8. Hence both deficits exceed 2^-37,
and in particular exceed 20*2^-50. For epsilon=2^-50,
1-m^(-epsilon)<epsilon*log(m)<20*epsilon<Delta. Consequently
s/(Wm)<m^(-epsilon), equivalently s/W<m^(1-epsilon).
This is an exact rational/power-of-two certificate. The earlier draft
incorrectly divided the side-wire count by v and claimed Delta>1/(4m);
that bound is withdrawn. The strict exponent conclusion above uses the
correct counts and remains valid.

## Scope

This closes the generic graph's finite label/rank count and its endpoint correction, conditional on the source's explicit scalar routing and its fixed-tape primitives. It does not prove a growing-root FFT, ordinary-coefficient conversion, or unconditional ordinary multiplication bound.
