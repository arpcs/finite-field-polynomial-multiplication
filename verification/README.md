# Evidence and provenance

`paper-builds.json` binds each compiled PDF to hashes of the paper's TeX and
required text inputs. `pdf-layout.json` records selected rendered pages and
the final reference/layout warning scan. Neither certifies mathematics.

`release-check.json` reports the package check's actual scope and outcome.
It checks the presence of the declared author, AI and unfinished-Lean
disclosures; it does not decide mathematical correctness or discover
publication status. `payload_files` counts the checksum entries;
`total_release_files` also includes the manifest and mutable check report.

Each paper's `audit.json` records its copied or derived sources, original
hashes, edit scope and current copy hashes. Historical source identifiers use
content hashes and source filenames; they are provenance labels, not paths
to files a reader must obtain elsewhere. Supporting proof records needed for
review are included in the corresponding paper directory.

The simple paper's bounded C++ reports are historical evidence, not new runs
for this release. Lean sources and completed theorem receipts are not
included in this release. See [VERIFICATION.md](../VERIFICATION.md) for the
exact evidence scope.

The general paper's finite-unit bundle under
`papers/01-general/proofs/finite-unit/` supplies separately identified native
endpoint, controller and profile inputs/checkers. Its ARTIFACTS.json binds
their exact bytes and upstream origins. Historical expected reports stay
under the bundle's `historical/` directory; the runner generates new reports
and its receipt under the ignored `build/` directory.

`finite-unit-replay.json` publishes the successful fresh replay completed on
31 October 2026 at 01:48:05 UTC. The six files in `finite-unit/` are byte
copies of that run's stdout/stderr, not copies relabeled from the historical
expectations; all three stderr files are empty. No executable is included.
The record uses schema `finite-unit-public-replay/1`: `working_directory`
sets the base for the recorded compile/replay commands; `files`,
`artifact_manifest` and each run's stdout/stderr object use repository-root
relative paths and SHA256 hashes. It retains the source receipt's completion
time, compiler identification, limits, exit statuses and historical-output
matches, and records that every paid/target bin matched the public RESULT.
The private-location-free public record is derived from the runner's receipt;
this publication step did not rerun the checkers.

The passed checks concern the fixed scalar endpoint, formal Laurent
controller, direct geometry and exact invoice/moment calculation. They do
not certify native frame-operator lowering on all columns, the all-length
tensor/compiler construction or the asymptotic multiplication theorem.
Independent human proof review and complete theorem-level Lean verification
remain outstanding.

The root SHA256SUMS.txt covers the public payload, excluding ignored build
caches, itself and the mutable release-check report. Refresh it only after
deliberate edits; a new hash records the file state rather than validating a
new mathematical conclusion. The root `.gitattributes` disables Git's
automatic line-ending conversion, so checkouts preserve the exact source
bytes bound by these records. Text files remain available for normal diffs.
