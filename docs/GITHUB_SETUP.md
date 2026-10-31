# Recommended GitHub setup

## Name and description

Repository name: **finite-field-polynomial-multiplication**

This describes the whole collection, including the general finite-field
paper and the principal characteristic-two paper. The local folder can keep
its existing name; it does not have to match the GitHub repository name.

Suggested description, ready to paste:

> AI-assisted research preprints and proof artifacts for polynomial multiplication over fixed finite fields. Full Lean formalization is in progress.

Suggested topics: `polynomial-multiplication`, `finite-fields`,
`computational-complexity`, `algorithms`, `characteristic-two`,
`ai-assisted-research`.

## Repository connection and visibility

Use your personal account as owner. Choose **Private** for the initial
upload and preview; change to **Public** when you want the release visible.
Public visibility allows readers to inspect the sources and propose work.

The owner created [arpcs/finite-field-polynomial-multiplication](https://github.com/arpcs/finite-field-polynomial-multiplication).
The local focused folder is connected through `origin` to
`https://github.com/arpcs/finite-field-polynomial-multiplication.git`.
At initial setup on 31 October 2026, read access was checked and the existing
`main` history downloaded. Its Apache-2.0 license-only commit (`fef412e`) is
retained as the historical baseline. Later commits and uploads are recorded
in the repository history. Follow [FIRST_COMMIT.md](FIRST_COMMIT.md) for
the owner-run commit workflow.

The settings below are recommendations; check the repository's current
settings rather than treating this guide as an account-settings receipt.
See [GitHub's creation guide](https://docs.github.com/en/repositories/creating-and-managing-repositories/creating-a-new-repository)
and [visibility controls](https://docs.github.com/en/repositories/managing-your-repositorys-settings-and-features/managing-repository-settings/setting-repository-visibility).

## Initial settings

| Setting | Recommendation for this project |
|---|---|
| Default branch | `main`; initialized locally and tracking `origin/main` |
| Issues | Enabled for specific proof objections, corrections and reproduction reports |
| Discussions | Leave off initially; enable later if open-ended research conversations need a separate home |
| Wiki and Projects | Leave off initially; the repository documents and Issues are sufficient |
| Write/admin access | Keep with the owner initially; public contributors can propose changes through forks |
| Merge method | Prefer squash merging for a concise history; inspect mathematical changes and preserve contributor credit |
| Auto-merge | Leave off; the owner decides what to incorporate |
| Required CI checks | None until an actual bounded workflow is configured; local package checks already have instructions |
| Website field | Leave blank until a real project page, DOI or arXiv landing page exists |

After the first upload, consider protecting `main` against deletion and force
pushes if your account/visibility supports those controls. Keep the setup
usable by a sole maintainer: do not require approval from a second reviewer
who does not exist, or a status check that has never been configured. Add a
review requirement when there are maintainers who can fulfill it.
See [branch protection](https://docs.github.com/en/repositories/configuring-branches-and-merges-in-your-repository/managing-protected-branches/about-protected-branches).

## How contributing works

An **Issue** is a report or question: for example, a possible gap at a named
equation. A **pull request** proposes concrete file changes. Someone without
write access can fork the repository, make a change on a branch in their own
copy, and send a pull request. The owner reviews it and chooses whether to
merge it. A suggestion does not automatically change the project.
See [GitHub's contribution workflow](https://docs.github.com/en/get-started/exploring-projects-on-github/contributing-to-a-project).

The existing CONTRIBUTING.md and issue/PR templates provide the report
format. GitHub links the contribution guide when people open issues or pull
requests; no special contribution application is required.
See [contributor guidelines](https://docs.github.com/en/communities/setting-up-your-project-for-healthy-contributions/setting-guidelines-for-repository-contributors).

For this project, acceptance should record the exact changed claim, sources,
checks, remaining limitations and actual credit. Merging a correction is not
scientific certification, and contributing a patch does not automatically
make someone a coauthor of a paper. Authorship is discussed separately based
on the scholarly contribution. Significant AI use should be disclosed.

## At public launch

Record the first public paper revision in citation/submission metadata and
confirm contributor-channel access. The repository URL is already supplied
in CITATION.cff; submission metadata should link the publicly available
paper snapshot when it exists. Keep the research-preprint and unfinished-
Lean disclosures. A version tag such as
`v0.1.0-preprint` can identify the first public snapshot.

The mathematical papers, contribution intake and visibility choice remain
separate decisions. Creating a private repository or making a local commit
does not submit a paper to arXiv or create a race entry.
