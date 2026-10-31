# Contributing

Project repository:
[arpcs/finite-field-polynomial-multiplication](https://github.com/arpcs/finite-field-polynomial-multiplication).
Use [Issues](https://github.com/arpcs/finite-field-polynomial-multiplication/issues)
or the public contact in [SUPPORT.md](SUPPORT.md). The issue and pull-request
templates help identify the exact claim and evidence.

Useful contributions include precise proof objections, counterexamples,
missing-implication reports, independent reproductions, scoped formalization,
source and attribution corrections, and documentation improvements. A proof
objection is useful without a proposed repair. Before duplicating an
investigation, check the manuscript's `STATUS.md`, the [claim-selection
record](docs/CLAIM_SELECTION.md), and the [contents catalog](CONTENTS.md) for
the exact claim, existing route, and prior work already recorded.
For substantial work, also consult the [roadmap](ROADMAP.md) and existing
issues and pull requests. Reuse suitable
pinned Mathlib and upstream results rather than duplicating their proofs;
record the exact statement being reused and its source revision.

## Issues, pull requests and review

An Issue reports a question, error or proposed direction. A pull request
proposes actual changes to files. To contribute a change, fork the repository,
create a branch, make the change in that copy and open a pull request.
Direct write access is not needed for this workflow.
The maintainer reviews the proposal and decides whether to merge it; submission
does not automatically change the project or establish the mathematics.

Useful contributions are credited. Paper coauthorship is discussed separately
based on scholarly contribution and responsibility. The project's license
and significant-AI disclosure expectations apply to submitted material.

## Make a report reviewable

Name the exact manuscript and dated revision, theorem or source location, and
the conclusion you think is affected. State the assumptions, field and size
quantifiers, input/output convention, and computational model relevant to the
point. For a counterexample, give the smallest clear instance and explain the
expected and observed result. For a proposed exponent improvement, include the
complete changed cost and dependency argument; a numerical search alone does
not establish an asymptotic result. See [REVIEWING.md](REVIEWING.md) for the
proof-review scope.

For Lean work, identify the exact statement and source revision, encodings,
machine model, dependency pins, checked command and result, source hash, axiom
report, and remaining assumptions. Distinguish a checked component from a
proof of the complete multiplier. Keep experimental sources under
`lean/experimental/` until they meet the repository's proof requirements.

Keep dated archive snapshots intact. Record new versions in
[`docs/VERSION_HISTORY.md`](docs/VERSION_HISTORY.md), and keep paper sources
and regenerated PDFs associated with their build and layout evidence. Use the
bounded, relevant procedures in [BUILDING.md](BUILDING.md); do not rerun every
historical experiment or build as a default. Read [VERIFICATION.md](VERIFICATION.md)
for the limits of existing evidence.

## Credit, licensing, and AI assistance

Credit predecessor work and identify copied or adapted source with its
applicable notices. The original project material uses Apache-2.0;
third-party terms remain separate. Read
[`docs/LICENSING.md`](docs/LICENSING.md) before offering material for inclusion.
No contributor agreement or transfer of ownership is requested.

Record material contributions and disclose substantial AI assistance, the
tool/model and version when known, its role, and what was personally checked.
Mark unavailable details as unrecorded. Preserve useful provenance, but do not include
private conversations, credentials, or unrelated personal information. AI
systems are not paper authors; paper authorship is a separate decision based
on scholarly contribution and responsibility. Keep discussion focused on
claims, evidence, and proposed changes, and treat questions and objections
respectfully.

Research branches with unclosed supplier interfaces are excluded from the
selected claims. Full Lean verification remains incomplete.
Unfinished formalization alone does not settle a written mathematical
argument. See the [roadmap](ROADMAP.md) for current priorities.
