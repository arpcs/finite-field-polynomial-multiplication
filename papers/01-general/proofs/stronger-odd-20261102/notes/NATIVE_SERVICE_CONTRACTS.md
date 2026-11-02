# Native service assumptions and host-cost reconstruction

This note states the exact native-service contracts used by the host reduction and gives the parameterized cost reconstruction. The original research source snapshot at `investigation/odd_prime_gapclosure_20261031_0410/proof_source_snapshot/native-main.tex` is recorded as 470,230 bytes with SHA-256 `6CD806C6E52A4883270DA6002A4D0C7B0120CA719745033183EB5686B3DB6F07`. Those size and hash identify only that original research source. The publication-oriented source `native-source.tex.txt` is an edited selection and restatement; `SOURCE_SELECTION.json` records its source mapping and distinct identity. It is not byte-identical to the original, and the original hash does not identify it.

## Primitive contracts and mathematical availability

Let V be the whole physical bit volume, including every complete prefix,
gap, suffix, independent lane and coefficient bit. A completed service
restores its auxiliary/caller spectator banks and declared head positions.

| Service | Exact map and cost | Actual proof source / status |
|---|---|---|
| Old interchange I_L | Swap equal binary address fields, arbitrary positive-length complete spectators and one-bit payload; O(V(u+1)^tau_L), tau_L=1-123879734039/10^15. | `lem:stage2swap`, gives the header/encoding/q-power-padding wrapper around the real source theorem `Stage2Machine.Bound.uniform_bound`. |
| Strong interchange I_tau | Same ABI, O(V(u+1)^tau polylog(u+2)), tau=1-a_B, a_B=859173879734039/250000000000000000. | `thm:mixedbitswap`, via `lem:pr589nativebit`, strictification, integer flow, effective finite precompilation and delayed cover. These are written mathematical arguments, not a numerical-moment substitution for a missing compiler. Finite-source provenance is summarized in [the native finite-source note](FINITE_NATIVE_PREMISES.md).
| Strong phase P_gamma | Literal C^tensor k on ordinary arrays over A_P=(Z/P)[I]/(I²+1), every odd P, every modulus width s, every independent lane count ell, N=2^k; O(N*ell*s*(k+1)^gamma*polylog(k+2)), gamma=1-3125805/10^9. | `thm:mixedbitinteger`, phase conclusion only. It uses strong I_tau and `lem:strongerphasemoment` in the existing striped induction. The fixed-field proof uses only this phase contract. |
| Inverse phase | Same ABI and bound. | C²=X and C⁴=I over every A_P, so three completed forward calls implement the inverse if desired. No characteristic-dependent root choice. |
| Lossless unequal binary transpose | Adjacent complete fields [2^a][2^b] exchange in O(V(a+b+1)^tau*polylog(a+b+2)); arbitrary complete spectators/payload. | `lem:binarycoordinatewiring` and `cor:losslessbinarytranspose`. Direct proof uses I_tau, elementary streams, near-commensurate whole blocks and the router from the native source proof, with no native-phase dependency cycle. |

The cited old interchange theorem has a proof body and remains an explicit source dependency. A fresh kernel rebuild of that dependency is not established here. This is a formal-verification limitation, not an added mathematical existence hypothesis. Rebuilding the old theorem alone would not verify the stronger I_tau or P_gamma constructions.

## Why arbitrary odd P is legitimate

`lem:rawdyadic` records the actual raw word's coefficients in
Z[i,1/2], with every supplied direction and absolute phase retained. The
all-column induction identifies the endpoint, while finite exact ledgers
check the constants/monomial adapters. `lem:wordproduct`,
preserves this coefficient ring under finite products, completion and
splitting; point coefficients are copied, not raised to a column count.
Thus the entire phase word reduces through i->I and 2^-1->(P+1)/2 for
every odd P. Odd factors in rational address charts are handled by the
separately selected fixed address prime. They are not inverses in the
caller's coefficient ring. Fixed dyadic data operations cost O(s) on an
s-bit residue pair; there is no coefficient-growth/precision approximation.

This proves why an integer-only, complex-only, or good-prime-only network
cannot be substituted without more work. The current strong phase theorem
does state the needed ring scope and linear s charge.

## Native reconstruction at the actual host shape

Let M=product n_i, L=ceil(log2(2M)), every n_i even, L³<=n_i<=R and
log2 R=O((log L)²). Let W be the actual per-point bit width, V=MW.
Freeze the finite local-permutation generator family first. One effective
fixed polynomial P_*(R,L) then bounds all route generation, logical-control
gauge reconstruction, tables, lookups, address copying and erasure. Assume
W>=P_*(R,L); the cyclotomic coefficient degree pays this explicitly.

Put a=ceil(log2 R), h=floor(L/(40a)). Since
(L-2)/a<t<L and h=Theta(L/a), there are enough axes for each selected
h-axis bank, an equally large dirty native bank and a full suffix. There
are O(log R) endpoint blocks. Dock construction `lem:nativedock`
 uses disjoint binary data, dirty auxiliary and movement dock
fields. Its remaining complete opaque suffix has at least 0.8L bits, so
its multiplicity pays each fixed polynomial in L used by guard correction.

The host-shape construction applies the following source lemmas using the strong services:

* Native phase (`prop:nativephase`): relocate the selected whole
  aggregate range, dock its endpoint choices into a binary h-bit field,
  apply P_gamma there, undo the exact conjugation and all relocation.
* Shuffle (`lem:nativeshuffle`): a linear-volume flat shuffle plus
  two endpoint reflections, each with O(log R) paired-block families.
* Ragged routing (`lem:raggednative`): O(log R) GLOBAL levels;
  siblings share one full-wire residual recursion, not a full-array call
  per child or edge. Odd intervals are never padded as new subnetworks.
* Controlled permutations (`prop:nativecontrolled`): fixed-ring A_3
  bit codec, completed target-only kernels, actual full shuffles and a
  tracked inverse gauge on controls. All per-record metadata is paid by W.
* CRT routing (`prop:nativeCRT`): at each balanced merge depth all
  right-child axes form one target set. The affine update on an axis is
  z_i->P_A*z_i+x_A modulo q_i, controlled by the left residues. All siblings
  share one controlled call. There are O(log t) depths; each completed map
  preserves every dummy pattern, and the inverse reverses the same maps.

At every aggregate relocation the moved objects are contiguous complete
numeric ranges [A],[B]. Pad those two whole ranges to separate binary
powers, at combined factor <4, apply the lossless binary transpose and
crop only at its completed boundary. A literal rectangle permutation sends
the valid rectangle to the valid transposed rectangle. Do not pad each
axis or invoke the polynomial-radix balanced-block proposition instead.
This prices those moves at tau, with no 1/(2-tau) exponent loss.

Consequently every native service above and its inverse costs

    O(V*L^gamma*(log(L+2))^K_native),

for a fixed effective K_native whenever 0<tau<=gamma<1. All O(log R),
O(log t), route depths and primitive secondary logarithms are included in
this one fixed secondary power. At the displayed values tau<gamma follows
from

    a_B - 3125805/10^9
      = 77722629734039/250000000000000000 > 0.

The frequency identity after the priced CRT permutation uses coupled roots
omega^E_i, E_i=(m/q_i)*((m/q_i)^-1 modulo q_i), not an independent root
oracle (`lem:CRTphase`).

## Fixed-tape composition and the precise remaining boundary

A fixed finite family of completed machines can be composed on a fixed
finite set of banks: rename their fixed tape indices, use a fixed common
alphabet/track encoding, and inline the finite call/return controls.
Runtime dimensions, archives and loop counters are data, not new tapes or
states. Header writing, copying, return scans and primitive cleanup are
charged above. Setup recursion may use a stack on ordinary tapes and
polynomial-time list scans; its time is charged as setup. Main loops reuse
the same completed banks, so no tape per axis, prime, depth or gate is
needed. This is a constructive mathematical composition argument; it does
not assert a newly kernel-checked literal source execution.

The reconstruction proves applicability of the native API at this host shape without adding a separate permutation oracle. Correctness of the strong native supplier depends on its all-column, precompilation, and cover proofs and on the exact finite assets. A missing rebuilt kernel closure is a formal-verification limitation; finite checks support only their stated finite premises and do not verify the complete multiplier. The associated source and certificate provenance appears in [the native finite-source note](FINITE_NATIVE_PREMISES.md).
