# Opaque-record cost audit for guarded packed routing

Proof-only audit, 29 October 2026. This is a separate proof of opaque payload
cost. It does **not** infer a `log M` descriptor bound from the packed
construction in Lemma 13 of the imported preprint. It uses only the final
Lemma 12 interchange bound, and supplies its own controlled record rotation,
boundary handling, and exceptional sort.

## 1. Array and width conventions

The tape contains `M` complete address records, each with an opaque
`R`-bit payload. Let `V=MR` be payload volume and
`p=ceil(log2(2M))` the address-key width. The address key comprises every
logical address field used by the operation: physical bit planes, selector
fields, auxiliary/guard fields, and role-row fields. The payload width `R`
is **not** included in `p`. A fixed number of tracks may mark record starts
and holes. Their total size is `O(M)<=O(V)`.

The only imported movement hypothesis is the final arbitrary-width
equal-chunk interchange of Lemma 12, cost `O(V u^tau)` for two `u`-bit
address chunks, with arbitrary prefix, gap, suffix, and payload. It already
prices all `R` payload bits. The independent rotations and sorts below also
move whole records; they never assume unit-cost random array access.

## 2. Copying an opaque record in O(R) tape steps

Keep the binary parameter `R` on a work track, least-significant bit first.
At the start of each record, copy this `ceil(log2(R+1))`-bit value to a
working down-counter. Copy the payload by scanning its `R` bits once and
decrementing the counter once per bit. The payload value is never inspected
arithmetically.

The counter head starts at its least-significant bit. A decrement scans
only the trailing zero run and the first one, flips those bits, and returns
to the low end. Over the complete countdown `R,R-1,...,1`, the total
trailing-run length is `O(R)` (each run length occurs at most
`floor(R/2^j)` times); hence all counter-head movement and bit flips cost
`O(R)`, not `O(R log R)`. A track marks the highest remaining one.
If that marked one is decremented, move the mark to the preceding newly
set bit, or set a zero flag if its position was zero. Thus termination
does not rescan the counter at every payload bit. Resetting the counter from the saved `R` costs
`O(log R)` per record, which is at most `O(R)`. Reading, writing, and
copying the record costs another `O(R)`. Therefore an opaque record can be
copied, moved, or compared at its boundary in `O(R)` total tape work.

Address counters have only `p` bits. Their amortized updates over a scan of
records cost `O(number of records + p)` per contiguous scan, by the same
trailing-run argument. Initializing/resetting such counters and preparing
the `R` counter once per record costs `O(M p + M log R) <= O(V+Mp)`.
Since the stated metadata allowance is `M p^C` and `R` is assumed
superpolynomial in `p`, these setup costs are absorbed. No `R`-bit
displacement or offset is computed.

## 3. Controlled cyclic rotation by whole records

Arrange the target address field after the fields on which its offset
depends. For a fixed control fiber, the target has `2^u` address values.
Each target value occupies one contiguous block of `B` complete records,
where `B` is the product of the suffix address-field lengths. The payload
is the innermost suffix, so every block consists of `B` records of `R`
bits. `B<=M` and `log B<=p`.

Compute the desired offset `delta` (or its guarded-lane sum) from the
control fields using `poly(p)` address work. The suffix dimensions and
`delta` are `p`-bit integers. Split the fiber at
`delta*B` **records**, not at a bit displacement: copy the tail block
sequence to a temporary tape, then the prefix, then concatenate them in
rotated order. Each block copy uses the opaque-record counter above. This
costs `O(volume of that fiber + p^C)`; no `delta*R` arithmetic occurs.
Over all fibers the movement sums to `O(V)`. There are at most `M`
control fibers, so all offset and split-count preparation costs
`O(M p^C)`. The line-rotation tape routine therefore costs
`O(V+M p^C)` even when `R` is much larger than `2^p`.

This argument also covers an offset which is an arbitrary
`poly(p)`-time vector function of a fixed number of disjoint control
fields: evaluate its `u` output bits on the current control tuple, form
the target-coordinate displacement in `p` bits, and rotate that fiber.
The address fields, not the opaque payload, are the function inputs.

## 4. Guard errors and exact correction

Use `K=ceil((log2(p+2))^2)` and split target bits into residue classes.
For one class, guarded `K`-bit lanes implement independent selected-bit
XORs except on a set of at most

```
delta_bad M,       delta_bad = O(u 2^(-K)),
```

complete addresses. The ideal XOR map preserves each guard quotient, so
it preserves the bad set. The packed sequence is a bijection agreeing
with the ideal map off that set, hence it also preserves the bad set. The
exact correction `ideal o packed^(-1)` is therefore supported only on
bad records.

For each extracted bad record, compute its current full `p`-bit address
and exact destination label in `poly(p)` work. Mark its hole in the
original stream; keep the original stream in place while sorting the
extracted bank. Stable binary radix sorting on the `p`-bit destination
uses `p` passes. A pass scans each selected record once, copies its
`R`-bit payload by the boundary counter, and carries only its `p`-bit
key. The addresses are a permutation of the bad set, so destination
labels are distinct and exactly fill the marked holes. A final full
stream scan reinserts the sorted records.

The exact correction cost is

```
O(V + M p^C + delta_bad M p(R+p)).
```

The `O(V)` term covers the full-stream extraction/reinsertion scans. The
radix term pays for every bad payload bit on every key pass. Since
`u<=p` and `K=Theta((log p)^2)`,
`delta_bad p=O(p^2 2^(-Theta((log p)^2)))=o(1)`. Thus correction is
`O(V+M p^C)`, absorbed by `O(V)` when `R` dominates every fixed
polynomial in `p`.

Combining the `K` residue classes, a guarded vector XOR on `u` target
bits costs

```
O(V u^tau log^2(p+2) + M p^C + delta_bad M p(R+p)),
```

with the small-`u` direct route included. Under `p=poly(m)` and
`R >> p^C`, this is `O(V u^tau log^2(p+2)+V)`. The ordinary transpose
uses the inverse address permutation and the same record-copy/sort ledger.

## 5. No implicit coefficient-column gather

For the stated layout, let the original H2 target key have `B=4m` bits,
written as four contiguous `m`-bit planes `[X1,Y1,X2,Y2]`. Let the
coefficient-column index have `a>=B` bits. Split that index from its
most-significant end into three `m`-bit scratch planes `Q,Z,W`, then
`r_role=O(log m)` role-index bits, then its remaining low `a-3m-r_role`
bits. For fixed target/scratch/role address, the low column bits and the
`D`-bit coefficient word are already a contiguous suffix record of width

```
R = 2^(a-3m-r_role) D.
```

This is the ordinary radix decomposition of the original column index:
the high bits identify the record and the low bits vary consecutively
inside its payload. No transpose, scatter, or gather is performed to
form the record. The total volume is unchanged:

```
M R = 2^(B+3m+r_role) 2^(a-3m-r_role) D = 2^(B+a)D.
```

The logical block `[X1,Y1]` can use `Q,Z,W`; `[X2,Y2]` can use the same
three fields in a separate call. Each call restores them exactly. The
other target block is fixed context. Address width is
`p=B+3m+r_role=7m+O(log m)=O(m)`, while `R>=2^(m-r_role)D`; hence `R`
dominates every fixed polynomial in `p` for growing `m`. Finitely many
small `m` use the direct finite-width route, whose constant is independent
of `D`.

For the role row, choose `r_role` so `N=2^r_role>=W^k`, where `W^k` is
the number of rows required by recursion depth `k`. Since `W` is fixed
and `k=O(log m)`, `r_role=O(log m)`. Pad to the next multiple `N'` of
`W^k`; because `N>=W^k`,
`N' < N+W^k <= 2N`. Thus padding increases volume by less than a factor
two. The source role network preserves completed row indices, so padded
zero rows remain zero and are deleted afterward. This row padding is
separate from payload bundling; it does not gather the low coefficient
columns.

This layout argument assumes the row-index interface and completed-row
preservation stated by the source phase-network construction. If the
application stores the coefficient columns in a different order, the
reblocking cost must be charged; it cannot be inferred from the payload
width alone.

## 6. Conclusion and scope

The opaque-record argument obtains `p=log M` metadata costs by explicit
record counters, record-granular fiber rotation, and `p`-bit exceptional
sorting. It does not treat `log R` as free: initialization and per-record
reset are charged `O(M log R)<=O(V)`, while no `log R` work is repeated
per payload bit. It also does not infer this stronger bound from the
preprint's Lemma 13 `A_rect=log(2V)` statement.

Under the stated contiguous column layout, existing index fields, large
payload, and role-row hypotheses, the packed prefix/selector router can
use these costs with address width `p=O(m)` and full payload movement
charged. This removes the `A_rect=log V` obstacle for that layout. It
does not establish that an arbitrary application has the required index
fields or coefficient ordering, and it makes no ordinary multiplication
claim beyond the separately proved operator/circuit recurrences.
