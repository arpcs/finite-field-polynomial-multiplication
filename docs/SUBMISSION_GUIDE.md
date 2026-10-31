# Submission preparation

This source/PDF package is not an arXiv submission or acceptance. GitHub
publication and arXiv submission are separate owner-controlled actions.

## GitHub first release

Use this focused directory as the repository root. Include the four papers,
their source/proof/evidence files and the community/license documents. Do not
add the surrounding workspace or broader historical collection. Run the
package check and inspect the staged paths as described in
[FIRST_COMMIT.md](FIRST_COMMIT.md). Retain the exact theorem scope and cited dependencies when posting the papers.

Record the repository's actual URL and immutable revision in citations and
metadata. A version tag may identify a stable snapshot; no
identifier is invented in the current metadata.

## arXiv

### Recommended selection

Keep all four documents on GitHub, with their shared dependencies explicit.
The recommended initial arXiv submission is the principal binary paper,
`papers/03-best-binary`, after a knowledgeable human has reviewed its main
argument. This is an editorial recommendation, not an additional arXiv
requirement or a claim that the package checks certify the mathematics.

Keep the general n log n baseline (`04-general-nlogn`) as a GitHub companion
initially. The alternative binary method (`02-simple-binary`) may justify
a separate paper later if its methodological contribution warrants it.
An eventual second arXiv paper should center the odd-characteristic exponent
0.9999, with the all-field theorem as a consequence. Before that submission,
assemble the essential odd-field proof supplements into a readable manuscript
or appendix; the current general PDF delegates key proofs to bundled sources.

For a paper selected for submission, use the exact title and concise abstract in
[SUBMISSION_METADATA.json](SUBMISSION_METADATA.json), reviewing them against
the final PDF. The author is Árpád Csizmadia. The ASCII author-entry spelling
is `\'Arp\'ad Csizmadia`; the contact address is
`arpad.csizmadia.public@gmail.com`. The printed papers retain the chosen
name/contact format without an affiliation line.

### Account and current submission policies

A student can create their own arXiv account; the university does not need
to create it. Use accurate current affiliation information in the account,
and an institutional email if available. A relevant lecturer or supervisor
may help with mathematical feedback and, if eligible, personal endorsement.
Endorsement is separate from proof review.

Since 21 January 2026, an institutional email alone is insufficient for
automatic endorsement. The automatic route also requires previous authorship
on an accepted paper in the relevant endorsement domain; otherwise seek
personal endorsement from an eligible arXiv author. See the
[endorsement policy update](https://blog.arxiv.org/2026/01/21/attention-authors-updated-endorsement-policy/).

Since 1 October 2026, submitting accounts are limited to two new submissions
per calendar month and three active submissions at a time, across categories.
See the [rate-limit policy](https://blog.arxiv.org/2026/10/01/updated-rate-limit-policy/).
Choose submissions for their distinct scientific contributions.

### Prepare the selected manuscript

The prepared metadata abstracts use standard ASCII TeX and are below arXiv's
1,920-character limit. Category suggestions are proposals for the owner to
check. Do not enter a journal reference, publication DOI or arXiv ID that does
not exist. Keep the AI-use disclosure and incomplete Lean status explicit,
and preserve the exact claim boundaries in titles and abstracts.

Upload LaTeX source with its required local inputs and bibliography/supporting
assets, not only an unrelated exported PDF. Do not include build caches,
executables, private logs or alternative top-level manuscripts as if they were
inputs to the selected paper. Every source bundle must identify its main.tex.

The baseline general paper cites the accessible binary theorem and the
odd-field proposition in the stronger general paper. The stronger general
paper also uses the principal binary saving. Retain these exact companion
dependencies and add public identifiers when available. The proof
record supplements belong with the paper they support. A cited private
workspace path alone is not a public proof reference.

The arXiv license selection is separate from the repository's Apache-2.0
license; choose one of the agreements offered at actual submission. The
account may require endorsement. arXiv moderation is not mathematical peer
review. Significant generative AI assistance must be disclosed in the work;
AI systems are not authors.

Official guidance: [submission](https://info.arxiv.org/help/submit/index.html),
[metadata](https://info.arxiv.org/help/prep.html),
[AI/moderation](https://info.arxiv.org/help/moderation/index.html),
[licenses](https://info.arxiv.org/help/license/index.html),
and [endorsement](https://info.arxiv.org/help/endorsement.html).

No race proposal or external submission is made by these instructions. Full
Lean proofs remain planned for a later update; this package does not resume
the paused formalization goal.
