# Polynomial multiplication over fixed finite fields

This project explores polynomial multiplication over fixed finite fields,
building on the work of Harvey, van der Hoeven, Lecerf and many other
researchers, alongside recent OpenAI mathematical manuscripts and community
follow-ups. It brings together four related AI-assisted papers and companion
notes, covering n log n baselines and stronger claimed bounds.

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

## Selected claims and the four papers

| Paper | Role and stated result | Read |
|---|---|---|
| General n log n | Baseline companion: O_q(n log(n+2)) for each fixed finite field, using the accessible binary construction, the odd-field proposition and an explicit fixed-basis reduction | [PDF](papers/04-general-nlogn/paper.pdf), [source](papers/04-general-nlogn/main.tex), [status](papers/04-general-nlogn/STATUS.md) |
| Stronger general result | O_q(n (log(n+2))^(1-2^-38)) over each fixed finite field; the odd-field branch has the sharper exponent 0.9999 | [PDF](papers/01-general/paper.pdf), [source](papers/01-general/main.tex), [status](papers/01-general/STATUS.md) |
| Fast Pascal transforms | Accessible binary companion: ordinary F2 multiplication in O(n log(n+2)), with a fixed characteristic-two extension corollary | [PDF](papers/02-simple-binary/paper.pdf), [source](papers/02-simple-binary/main.tex), [status](papers/02-simple-binary/STATUS.md) |
| Ordinary binary multiplication below n log n | Principal characteristic-two paper: controlled CRT/routing construction with exponent 1-2^-38 on fixed finite tapes | [PDF](papers/03-best-binary/paper.pdf), [source](papers/03-best-binary/main.tex), [status](papers/03-best-binary/STATUS.md) |

For a bound $O(n(\log n)^{1-\kappa})$, a larger saving $\kappa$ is stronger
for the same problem and model. Here the selected binary saving is
$\kappa=2^{-38}\approx3.64\times10^{-12}$; the odd-field saving is
$\kappa=10^{-4}$, which is not asserted in characteristic two.
The exponent saving is asymptotic; no practical speedup is claimed.

The general baseline uses the accessible binary result and only the odd
proposition from the stronger general paper. The stronger general theorem
instead uses the principal binary result. The odd proposition is independent
of that binary theorem, so this dependency direction is not circular.
These four documents present related constructions and consequences.
See [CONTENTS.md](CONTENTS.md) and the
[claim map](docs/CLAIM_SELECTION.md).

Each paper records its proof dependencies and current status. The
[claim map](docs/CLAIM_SELECTION.md) explains the selection, including
research branches left out while their proof interfaces remain open.
Questions about any step in the written arguments are welcome.

Substantial generative AI assisted mathematical exploration, proof and
algorithm development, writing, coding and review. Full Lean formalization
is unfinished and planned for a later update. Read
[AI_USE.md](AI_USE.md), [VERIFICATION.md](VERIFICATION.md), and each paper's
STATUS.md for the actual evidence scope.

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
This collection contains the focused four-document selection; the wider
historical collection is kept outside it. Corrections and changed claims
belong in the [version history](docs/VERSION_HISTORY.md), with earlier public
versions retained. The [release status](docs/RELEASE_STATUS.md) and
[owner-run setup guide](docs/GITHUB_SETUP.md) record publication preparation.
