# First release and later commits: owner workflow

This focused folder is intended to be its own repository root. The larger
`finite-field-polynomial-multiplication` collection is a separate sibling
folder and is not part of this first release. Local `main` tracks
`origin/main` at https://github.com/arpcs/finite-field-polynomial-multiplication.git.
Preparation on 31 October 2026 started from the existing GitHub license-only
commit (`fef412e`). That is the historical baseline; use `git status` and
the repository history to inspect the current commit and publication state.

From the original FastMul workspace:

```powershell
Set-Location .\output\finite-field-polynomial-multiplication-first-release
.\scripts\check-release.ps1
$projectGitArgs = @('--git-dir=.git', '--work-tree=.')
git @projectGitArgs config --local --get user.name
git @projectGitArgs config --local --get user.email
git @projectGitArgs status --short
git @projectGitArgs add -- .
git @projectGitArgs diff --cached --check
git @projectGitArgs diff --cached --stat
git @projectGitArgs diff --cached
```

These commands select this repository explicitly, so Windows Git can use it
without changing global directory-trust settings. Keep the same PowerShell
session and working directory for the commit command below.

The repository's `.gitattributes` preserves the exact file bytes used by the
checksum and build receipts. Its whitespace rules accept CRLF, Markdown hard
line breaks, and terminal blank lines in existing Markdown/TeX snapshots.
Other text still receives Git's usual trailing-whitespace and space-before-tab
checks; this does not normalize sources or change global Git settings.

The repository-local author identity has been set to **Árpád Csizmadia** and
**arpad.csizmadia.public@gmail.com**, the public identity chosen for this
project. Check these two displayed values before committing; Git author
email addresses become part of the commit metadata. Other repositories'
identity settings are unchanged.

Review the four papers and their exact claim boundaries, the source list,
license/attribution and staged diff. Only the selected routes with supplied proof dependencies are included. The `.gitignore` excludes
build caches, tool binaries and generated objects, while PDFs and source
records are included. When satisfied, commit with a message describing the
reviewed changes. For the initial research release, the message is:

```powershell
git @projectGitArgs commit -m "Add four finite-field multiplication preprints"
```

The remote is already configured. These instructions make a local commit
only; they do not push the papers or change GitHub visibility.

[GITHUB_SETUP.md](GITHUB_SETUP.md) gives the recommended repository name,
creation options and contribution workflow.
