# Fixed native unit: data, exact checks and provenance

This directory supplies the finite inputs and small exact checkers cited by
the odd-characteristic proof. It closes a packaging gap: the native proof's
saved word, scalar endpoint, controller and profile calculation can be
located and replayed without the author's wider research workspace.
It is supporting evidence for a written proof, not an end-to-end verified
polynomial multiplier.

The construction builds on the CrocSwap community's work. In particular,
Cinna Davis supplied the p16 productive-controller lineage; Ali Romman
supplied the forward wrapper and verifier lineage. The selected native word
is DreamingOfClouds' PR #6030 helper-470 edit, following PR #5907 and the
PR #5827 verifier chain, with the earlier contributors retained in the
upstream notes. Those notes disclose OpenAI Codex assistance and Claude
Opus 5.5 assistance through Claude Code. This project's independent small
C++ replays were developed with substantial OpenAI Codex assistance.
The checkers reuse the mathematical inputs; they do not claim authorship
of the community construction or acceptance of the upstream framework claims.

## Exact public inputs

All three fixtures are frozen byte copies. The public source pin is
[`2485805a6d47f36ea83ddde6327d453ac82d44dc`](https://github.com/CrocSwap/integer-mult-bounds/tree/2485805a6d47f36ea83ddde6327d453ac82d44dc).

| Local input | Immutable upstream path | Bytes and SHA256 |
|---|---|---|
| `inputs/native-word.json` | [`research/p104-helper470-twin-rung-removal/WORD.json.gz`](https://github.com/CrocSwap/integer-mult-bounds/blob/2485805a6d47f36ea83ddde6327d453ac82d44dc/research/p104-helper470-twin-rung-removal/WORD.json.gz), after gzip decompression | 1,660,484; `bdb99bde29de80e90bacbfb516bd37f636b36b52d870794851d07a3ecf639c01` |
| `inputs/controller.json` | [`research/joint-helper-lattice/CONTROLLER.json`](https://github.com/CrocSwap/integer-mult-bounds/blob/2485805a6d47f36ea83ddde6327d453ac82d44dc/research/joint-helper-lattice/CONTROLLER.json) | 57,924; `1f5d6aa267e4e66048818714b5d3b5eae17a58abe91d15deeaa34574f7391a5f` |
| `inputs/frontier6030-result.json` | [`research/p104-helper470-twin-rung-removal/RESULT.json`](https://github.com/CrocSwap/integer-mult-bounds/blob/2485805a6d47f36ea83ddde6327d453ac82d44dc/research/p104-helper470-twin-rung-removal/RESULT.json) | 12,798; `84fcbe2a0b64307b5703c363408042bdd91555b0419509aa50daa43b3b1924ad` |

The upstream compressed word is 119,880 bytes, SHA256
`7834725d9e34ee846a9ccc615221ea81e0201613938afa185d2eda0c9a6c232f`.
Its entire decompressed byte stream was compared with the published local
fixture. Compression-container and decompressed-payload hashes are distinct.
The p16/a7/rank145 controller is the one actually checked here; the upstream
`query-thinned-controllers/COMPLEX-CONTROLLER.json` is a different
p17/a8/rank153 fixture and is not an input to this bundle.

`ARTIFACTS.json` records each released file's relative path, size, current
SHA256, original workspace-relative provenance, original SHA256 and any
public source path. No machine-specific workspace path is needed. For the
three C++ entry points, the only publication changes are a modification
notice and a local shared-support include path. The shared arithmetic/guard
and bounded JSON support are byte-identical to their originals.

## What the three checks establish

1. `native_scalar_record_probe.cpp` reads all 22,803 native events and 1,093
   independent nine-bit frame bases. It checks common charts, strict nested
   transports, all public frame endpoints, owned-storage chronology and the
   complete paid/helper rank histograms. It replays all 770 public scalar
   basis columns, checking every one of 799 outputs per column: the 104
   main shears, 562 independent helper identities and zero owned outputs.
   Owned inputs begin at zero. Removing the first ADD is rejected. Linearity
   extends this scalar endpoint calculation to arbitrary public scalar inputs.
2. `controller_record_probe.cpp` checks both 32-column scalar boundary
   programs and all 32 columns of the base and forward Laurent identities.
   The 154-event base expands to 218 forward-wrapper events, with 18 native
   calls, 15 query calls, 15 idle calls and 16 wrapper sites. It derives the
   main-target and whole-idle histograms. It also checks the direct geometry
   for the native word's 104 ports, including all 512 points of each nine-bit
   phase domain and basis relations for the seventeen-axis routes. Three
   controller mutations and omitted phase corrections are rejected.
3. `record_rate_probe.cpp` joins 18 copies of the native histograms with the
   controller's query/idle/main counts. It checks 66,834 paid jobs with rank
   mass 240,152 and 13,444 productive roles with rank mass 240,912, using 16
   paid bins and 18 target bins. The allocation is
   `32*104 + 18*562 = 13444` public productive roles and `29+1 = 30` owned
   roles. Its exact rational moment bounds use tested saving `39/12500` and
   obtain normalized strictification upper bound
   `16777216015641/16794395869184 < 1`. The runner additionally compares every
   paid/target bin with the saved public RESULT. The RESULT's other compiler,
   ordinary-bit and outer-inequality claims are not certified by this check.

Together these checks provide the fixed scalar endpoint, formal controller
identity, finite geometry and exact invoice/moment premises for
`prop:recordunit` in `../native_odd_source_snapshot.tex.txt`. Relevant source
anchors include `prop:recordunit`, the native endpoint preceding it, the
record-rate calculation, `thm:stage2phase` and `lem:nativeparameter`.
The native frame operators, all-column lowering, chronological tensor
construction, rounding and complete uniform fixed-tape cost transfer still
require the written mathematical argument and its separately cited theorems.
No `2^145` data array or giant tensor word is instantiated here. Historical
DFT exponents printed by the rate checker are not a new claim that the
finite checks alone prove an asymptotic DFT or finite-field theorem.

## Reproduction

Use Windows, PowerShell 7, a C++17 GCC-compatible compiler and GMP development
headers/library. PSAPI is supplied by Windows. No toolchain or dependency is
downloaded by the runner. GMP is an external dependency, not copied here.

From this directory, this command only checks the manifest and file hashes:

```powershell
pwsh -NoProfile -File ./verify-finite-unit.ps1
```

For compilation and replay, supply an existing bounded compiler launcher:

```powershell
pwsh -NoProfile -File ./verify-finite-unit.ps1 -Replay `
  -Compiler g++ -CompilerGuard /path/to/guarded-document.exe
```

`CompilerGuard` must use the calling convention
`guard.exe compiler.exe arguments...`. The repository's
`../../../../scripts/guarded-document.cpp` implements a suitable Windows
launcher: 512 MiB aggregate process-tree memory, 60 CPU seconds and 120 wall
seconds per compiler invocation. Compile that launcher using your existing
trusted bounded toolchain setup. The runner compiles one checker at a time
and applies the guard only to compilation, so its serialization mutex is
not nested around checker execution. It fails before compilation when no
guard is supplied. Add nonstandard GMP include/library locations through
the compiler's normal environment or a compiler wrapper.

Each checker installs its unchanged self-only hard limits of 64 MiB and
10 CPU seconds before parsing input; installation failure is a refusal,
not a successful result. The runner adds a 30-second wall limit per checker.
Rationals are capped at 2,048 bits. JSON is capped at 2 MiB, 220,000 tokens
and depth 24. The native state holds 799 scalar rationals; the controller
uses one Laurent column, capped at 1,024 terms per wire and 8,192 in total.
The historical controller peak was 35 terms.

`historical/` contains unchanged historical workspace stdout receipts.
They are expected-output fixtures, not a fresh run for this release.
The runner checks exact normalized output, exit status and the public bins,
then writes fresh reports, compiler logs and a machine-readable
`build/replay-receipt.json`. Build outputs are ignored and are not evidence
until the recorded commands actually succeed. The receipt records relative
commands, source/input hashes and compiler identification, without resolved
personal directory paths. No Lean build is involved.

## Licensing and retained credit

Original project checker contributions use the repository's Apache-2.0
license. Copied CrocSwap fixtures and provenance notes retain their upstream
Apache-2.0 terms, the full upstream notice in `upstream/CrocSwap-NOTICE`, and
license text in `upstream/CrocSwap-LICENSE`. The three unchanged upstream
README files preserve the native-word, base-controller and forward-wrapper
credits and their stated limitations. Relative links in those frozen notes
refer to their original upstream package directories; the immutable links
and paths in `ARTIFACTS.json` identify those directories. Their recorded
commands are upstream documentation, not instructions executed by this runner.
