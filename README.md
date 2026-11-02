# Polynomial multiplication over fixed finite fields

This repository contains research preprints on polynomial multiplication
over fixed finite fields, building on the work of Harvey, van der Hoeven,
Lecerf and many other researchers, alongside recent OpenAI mathematical
manuscripts and community follow-ups. The AI-assisted manuscripts and
companion notes cover
n log n baselines and stronger claimed bounds.

Questions, corrections and contributions are welcome, whether you are
exploring the ideas, checking a proof or improving the documentation.

The papers are research preprints open for mathematical review. Independent
human proof review and complete theorem-level Lean verification remain
outstanding; [VERIFICATION.md](VERIFICATION.md) describes the checks so far.

## Problem and previous benchmark

Multiply two ordinary degree-less-than-n polynomials over an individually
fixed finite field and output all 2n-1 product coefficients. Time counts bit
operations on a deterministic machine with a fixed finite alphabet and a
fixed number of sequential tapes, including setup, movement and decoding.
The field is fixed before n varies.

The standard unconditional fixed-field benchmark is
$O_q(n\log n\,4^{\log^*n})$, from
[Harvey and van der Hoeven (2019)](https://doi.org/10.1016/j.jco.2019.03.004),
with constant-degree basis reduction for fixed extensions. Their
[2022 finite-field n log n theorem](https://doi.org/10.1145/3505584)
assumes an explicit Linnik hypothesis. Harvey's
[20 October 2026 discussion, Section 4](https://web.maths.unsw.edu.au/~davidharvey/research/subnlogn.pdf)
also identifies the fixed-field problem separately from integer multiplication.
These antecedents supply the comparison and foundations for this work.

Earlier work developed the fast arithmetic, structured evaluation and
cyclotomic methods that made these bounds possible. Removing the remaining
iterated-logarithmic factor was still a fixed-field target in the cited
October 2026 discussion. The baseline papers claim to reach n log n;
the stronger companions claim a strict logarithmic saving. Their proposed
advance is the complete transfer to ordinary polynomial input/output and
fixed-tape costs, built on the prior results credited below.

## Preprints and stated bounds

| Paper | Role and stated result | Read |
|---|---|---|
| Paired-phase binary multiplication | Ordinary F2 multiplication in $O(n(\log(n+2))^{1301/1302})$, with saving $\kappa=1/1302$ | [PDF](papers/03-best-binary/versions/0.2.1/paper.pdf), [source](papers/03-best-binary/versions/0.2.1/main.tex), [proof scope](papers/03-best-binary/versions/0.2.1/README.txt) |
| General fixed-field multiplication | $O_q(n(\log(n+2))^{1301/1302})$ for each fixed finite field; $O_q(n(\log(n+2))^{319/320})$ for each fixed field of odd characteristic | [PDF](papers/01-general/paper.pdf), [source](papers/01-general/main.tex), [status](papers/01-general/STATUS.md) |
| Fast Pascal transforms | Ordinary F2 multiplication in $O(n\log(n+2))$, with a corollary for each fixed characteristic-two extension | [PDF](papers/02-simple-binary/paper.pdf), [source](papers/02-simple-binary/main.tex), [status](papers/02-simple-binary/STATUS.md) |
| General n log n baseline | Ordinary multiplication over each fixed finite field in $O_q(n\log(n+2))$ | [PDF](papers/04-general-nlogn/paper.pdf), [source](papers/04-general-nlogn/main.tex), [status](papers/04-general-nlogn/STATUS.md) |

The characteristic-two branch of the general paper uses the paired-phase
binary theorem through its fixed-basis reduction. The
[controlled-CRT binary construction](papers/03-best-binary/paper.pdf),
with exponent $1-2^{-38}$, remains a separate construction with its own
[source](papers/03-best-binary/main.tex) and
[status](papers/03-best-binary/STATUS.md).
The paired-phase construction has its own proof and
[exact claim specification](papers/03-best-binary/versions/0.2.1/CLAIM.json).

For a bound $O(n(\log n)^{1-\kappa})$, a larger saving $\kappa$ is stronger
for the same problem and model. The paired-phase binary saving is
$\kappa=1/1302$; the general paper's odd-field saving is $\kappa=1/320$.
The common all-field saving is also $\kappa=1/1302$; the stronger
odd-field exponent is specific to odd characteristic.
These are asymptotic bounds; no practical speedup is claimed.

The general baseline uses the Pascal/Taylor binary theorem, the general
paper's odd-field proposition and a fixed-basis reduction. The odd-field
proposition is independent of the binary theorems. The general paper's
common strict saving combines the paired-phase binary theorem with that
independent odd-field proposition.
See [CONTENTS.md](CONTENTS.md) and the
[claim map](docs/CLAIM_SELECTION.md).

Each paper records its proof dependencies and evidence scope. Research
branches with open proof interfaces are identified in the claim map.

Substantial generative AI assisted mathematical exploration, proof and
algorithm development, writing, coding and review. Complete formal
verification of the fast multiplication theorems remains outstanding.
[AI_USE.md](AI_USE.md), [VERIFICATION.md](VERIFICATION.md) and each paper's
STATUS.md describe the evidence scope.

## Prior work and credits

The papers distinguish inherited inputs from their claimed contributions:

| Prior work | Role |
|---|---|
| Harvey, van der Hoeven and Lecerf; Harvey and van der Hoeven | Earlier bit bounds and cyclotomic host/root constructions |
| Cantor; Gao and Mateer; Bostan and Schost; Liu | Additive evaluation, Taylor transforms, basis conversions and related binary multiplication algorithms |
| Karatsuba and Ofman; Schönhage and Strassen; Brent and Zimmermann | Classical arithmetic used by the constructions |
| OpenAI's integer and exact-DFT preprints | Finite-network/interchange and local compiler antecedents, with the cited model boundaries |
| Alman; van der Hoeven and Larrieu | Lookup-table tensor algorithms and Frobenius FFTs, compared in their actual access and cost models |
| CrocSwap contributors; platypii and contributors; J. A. Sussman | Attributed community constructions, the named stage-two machine source, and related recursion work; their roles are distinguished in the papers |

Complete bibliographic entries and source revisions appear in the papers.
[Third-party notices](docs/THIRD_PARTY_NOTICES.md) summarize source and
license boundaries. Citation acknowledges prior work and does not imply
its authors reviewed or endorsed this collection.

## Contributing

A question, a useful reference or a small correction can help. Contributions
can include clearer explanations, code and documentation improvements,
independent proof review, alternative approaches or scoped formalization.
You do not need a complete solution to join the discussion.

[BUILDING.md](BUILDING.md) describes the lightweight package check and
guarded PDF compilation. The odd-field branch also includes a
[finite proof-artifact map](papers/01-general/proofs/finite-unit/README.md)
and a [fresh bounded replay record](verification/finite-unit-replay.json).
These check fixed finite premises; the complete asymptotic argument remains
in the written proofs. The simple binary witnesses retain their historical
receipts. No scientific or Lean workload is started by the package check.

Use [CONTRIBUTING.md](CONTRIBUTING.md) for objections and improvements,
[REVIEWING.md](REVIEWING.md) for proof-review expectations,
[ROADMAP.md](ROADMAP.md) for priorities, and [SUPPORT.md](SUPPORT.md) for
contact information.

For a mathematical question, include the paper and the relevant step or
equation where possible; a proposed repair is optional. For larger proof or
formalization work, check existing discussions and the roadmap so we can
build on one another's work.

Maintained by **Árpád Csizmadia**.
Contact: [arpad.csizmadia.public@gmail.com](mailto:arpad.csizmadia.public@gmail.com).

Original project material uses **Apache-2.0**, with source-specific terms
and attribution preserved in [NOTICE](NOTICE),
[third-party notices](docs/THIRD_PARTY_NOTICES.md), and
[licensing scope](docs/LICENSING.md). Each paper has `citation.bib`;
[CITATION.cff](CITATION.cff) describes the collection.

Project home: [arpcs/finite-field-polynomial-multiplication](https://github.com/arpcs/finite-field-polynomial-multiplication).
Corrections and changed claims are recorded in the
[version history](docs/VERSION_HISTORY.md), with earlier public versions
retained. See the [release status](docs/RELEASE_STATUS.md) for the scope of
the current collection.
