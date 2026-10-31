# Reviewing mathematical claims

The manuscripts are research drafts open for mathematical review. This guide
describes useful ways to inspect a claim. Independent mathematical review
and end-to-end Lean proofs of the fast multiplication theorems remain
outstanding. The selected claims and excluded conditional branches are
identified in [claim selection](docs/CLAIM_SELECTION.md).

## Trace the statement and its route

Start from the exact dated manuscript and its `STATUS.md`. Write down the
theorem's hypotheses, quantifiers, conclusion, input and output, cost measure,
and machine model. Follow each implication to the construction and to every
imported result or service it uses. Identify the source and exact statement of
each supplier, and check that its hypotheses match the point where it is
applied. Keep distinct ordinary univariate multiplication, group convolution,
multivariate multiplication, circuit bounds, and integer multiplication.

A smaller logarithmic exponent is a stronger bound for the same problem and
model, but its numerical size does not show that its proof is complete. Compare
the full argument and dependency closure. A cited prior theorem with a known
statement is different from an unproved local hypothesis; say which one is
needed and whether the interface actually follows from the cited result.

For a fixed-tape complexity claim, account for the entire algorithm: field and
basis conversions, setup, evaluation and decoding, native arithmetic, address
changes and routing, arbitrary workspace state, cleanup, and ordinary input
and output. Check the cost at the stated lengths and for the stated field
quantifiers. Do not infer an end-to-end time theorem from a local identity,
finite witness, transform routine, or circuit result whose movement costs are
different.

## Report evidence at its actual scope

Give the exact source revision, theorem or equation, and the smallest relevant
reasoning or example. State whether the issue is a confirmed contradiction,
an apparent missing implication, a hypothesis mismatch, or a question. Explain
which conclusion it affects and what evidence would resolve it. A proposed
repair is welcome but not required.

For formalization, record the Lean and Mathlib revisions or dependency pins,
the exact declaration checked, command and result, source hash, and reported
axioms and assumptions. Check that the formal statement corresponds to the
paper's quantifiers, encodings, cost model, and conclusion. A checked lemma or
component is evidence for that declaration only; partial Lean receipts do not
verify the complete multiplier. Keep standard logical axioms separate from
unproved mathematical assumptions, and report any nonstandard dependency.

Separate mathematical argument review from PDF compilation, hash checks,
finite-instance tests, local Lean component checks, and novelty searches.
Those checks can support specific facts about the package without certifying
the asymptotic theorem. The current evidence limits and outstanding proof
obligations are summarized in [VERIFICATION.md](VERIFICATION.md).
