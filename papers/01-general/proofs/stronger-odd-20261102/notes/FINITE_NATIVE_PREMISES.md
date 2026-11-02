# Finite-source proofs and native-service scope

This note records how the original native-source arguments and finite certificates support the strong interchange and phase services. The original research snapshot is `investigation/odd_prime_gapclosure_20261031_0410/proof_source_snapshot/native-main.tex` (470,230 bytes; SHA-256 `6CD806C6E52A4883270DA6002A4D0C7B0120CA719745033183EB5686B3DB6F07`). The publication-oriented `native-source.tex.txt` is an edited selection and restatement; `SOURCE_SELECTION.json` records its source mapping and distinct identity. The original size/hash does not identify that edited file or these supporting notes.

## Source-level closure and limits

At manuscript-source level, the finite native/all-column premise used by the mixed-bit services is closed. The source gives explicit proofs that lift finite scalar identities to arbitrary column multiplicities, products, odd residue rings, and an effective all-size rank-one compiler. In particular, `thm:finitebitcompiler` is a strong-induction construction; it does not assume a community mixed compiler or leave a native-all-columns premise for its own PR589 word.

This is a written source proof supported by bounded exact finite checks. It is not an independent source proof, a fresh proof-assistant rebuild, or a materialized uniform word. `thm:mixedbitswap` and `thm:mixedbitinteger` retain the cited older Stage2 machine theorem as a dependency. 

## Native manuscript source and theorem structure

The original research source snapshot is `investigation/odd_prime_gapclosure_20261031_0410/proof_source_snapshot/native-main.tex` (470,230 bytes; SHA-256 `6CD806C6E52A4883270DA6002A4D0C7B0120CA719745033183EB5686B3DB6F07`). This size and hash identify only that original source. The publication-oriented `native-source.tex.txt` is an edited selection and restatement; `SOURCE_SELECTION.json` records its source mapping and distinct identity. It is not byte-identical to the original, and the original hash does not identify it or these supporting notes.

The relevant native declarations are:

| Declaration | Role |
|---|---|
| `lem:ramframe` | Common-frame induction; lifts the finite logical word to every column count and arbitrary inputs. |
| `lem:clifflower` | Exact A C_r B lowering, including absolute phase. |
| `prop:recordunit` | Actual 145-axis Gaussian-dyadic phase word and its all-column endpoints. |
| `lem:rawdyadic` | Dyadic coefficient/width ledger and specialization to every odd Gaussian residue ring. |
| `lem:wordproduct` | Explicit product, coefficient-ring closure, and owned-row clearing. |
| `lem:strongerphasemoment` | Stronger rate and source/exit budget on the existing phase word. |
| `lem:pr589nativebit` | Pinned finite PR589 BIT unit and exact rank histogram. |
| `lem:bitwordstrictification` | Product, completion, and splitting to a separated finite word. |
| `lem:finitebitflow` | Integer source/fed/exit matching with explicit field ownership. |
| `thm:finitebitcompiler` | Strong-induction finite precompiler; no external all-size mixed compiler premise. |
| `thm:mixedbitswap` | All-length opaque equal-field interchange, conditional on the named old Stage2 import and proved native construction. |
| `thm:mixedbitinteger` | All-odd-modulus phase/Walsh service using the stronger phase moment. |

These finite-source arguments are written proofs with bounded exact-check support, not kernel-checked local theorems.

## Finite BIT input and exact checker


The local data manifest `finite-data/pr589-bit/sources.json` pins repository `CrocSwap/integer-mult-bounds` at commit `322e0ec764aa7ef7801383feb1f656e460dd8bed`. Its seven primary Git blobs are listed as verified. Current local SHA-256 values match that manifest for the assets consumed by the exact checker:

| Asset | SHA-256 | Use |
|---|---|---|
| `finite-data/pr589-bit/WORD.json.gz` | `E3E301E62BC2B41DBF1CEAC0ACF3D35824EBEAB1848C5A2142D4577B109DA52F` | Pinned compressed local word. |
| `finite-data/pr589-bit/WORD.json` | `5642FD0E35A1ACC11ACFF8D0C08350C1617E95F310D4D35AD63A651F9EEEBA0B` | Bounded decompression of the pinned word; the C++ checker reads this file. |
| `finite-data/pr589-bit/frames.json` | `D006B3BFE0C04AFECFEA7AECFA59DFE4298B99501C70DA3938E40289BC2F5010` | All local rational frame bases. |
| `finite-data/pr589-bit/249-records.bin` | `EA44AA047A2A9CF034DE8B56B2166C49CF2DBDF9CD9ED6A20299A4F2B05EF09A` | Complete 27,234 six-integer source records (653,616 bytes). |
| `finite-data/pr589-bit/249-states.json` | `701CA802279B23BA23FFD502935AE9F34A33FC81FDFD266042F3208A2CB16265` | Pinned state context; not parsed by `pr589_native_bit_probe.cpp`. |
| `finite-data/pr589-bit/XCHECK.json` | `86EAB972E14F7660242B20DAABE2DB2AC6C0D7986FCE824D2D4791C112CD78BA` | Pinned upstream replay/interface summary; not parsed by that C++ checker. |
| `finite-data/pr589-bit/bit_controller_322e0ec_source.json` | `39AC84FB848B908F7BA051FAE4556D507900C421DC5D23501A9C0CB1D61FD08D` | The separate 32-wire p16/a7 BIT controller consumed by `mixed_bit_controller_probe.cpp`. |

`pr589_native_bit_probe.cpp` (SHA-256 `CB76E808B65AFC1319FD74C96C358ACED408945B876DE048910D682AACBCD152`) reads `WORD.json`, `frames.json`, and `249-records.bin`. Its source explicitly loops over every one of the 661 scalar basis inputs in both orientations, executes the full record chronology, and checks the expected shear/identity output and cleared owned copy. The existing report records 436,921 output comparisons per orientation, all 636 frame projectors, all 2,386 distinct nested transports, and nine rank-seven copy episodes. This is exhaustive basis coverage of the 661-dimensional logical map, not random probing. By linearity, agreement on this finite basis gives its arbitrary logical-input endpoint.

The same checker separately verifies rational frame symmetry/idempotence/rank and the actual main/helper boundary projectors. Its `geometry()` does **not** instantiate every 15-dimensional Householder chart. The paper supplies that chart constructively: `lem:pr589nativebit` sets `P_a=q_aq_a^T/4`, takes the Householder map sending `2e_0` to `q_a`, and proves `A_a^TA_a=I_7`, `A_aA_a^T=K_a`, and `R_a^2=I_{15}` algebraically. The pinned `bit_native_binding_source.py` (SHA-256 `BF6374225F388E7531FA6475CC255BD430100FF62C38D582C41601F0739DE7B7`) also contains exact rational chart checks, but it was not executed; the manifest records `Python_executed: false`. This is a validation-coverage distinction, not an absent chart formula in the manuscript.

The controller is separately exhaustive at its finite coefficient dimension. `mixed_bit_controller_probe.cpp` (SHA-256 `D73AEE3889340BEF32DE6924F69119F3E0CCCA56745CBBE84FC404C32E837C91`) reads the pinned controller JSON and checks all 32 formal columns over its sparse Laurent-monomial representation, exact left/right boundary factorizations, all physical events, invoice bins, and three omission/sign negative controls. Its report is not a sample of characters or address vectors. The combined paper proof then uses the disjoint rational-projector geometry and the local all-column endpoint; the controller checker alone does not prove the native local word.

## Raw-CU phase-word certificate chain

The PR589 BIT source is distinct from the 145-axis phase word used for Pγ. The raw-CU assembler reads a separate source family:

| Input | SHA-256 recorded in `raw_cu_recipe.json` |
|---|---|
| `finite-unit/inputs/native-word.json` | `BDB99BDE29DE80E90BACBFB516BD37F636B36B52D870794851D07A3ECF639C01` |
| `finite-unit/inputs/controller.json` | `1F5D6AA267E4E66048818714B5D3B5EAE17A58ABE91D15DEEAA34574F7391A5F` |
| `finite-data/raw-cu/native_lowering_recipes.tsv` | `10294CD5E01003B3251C1FB2403D95F61DC2AC8971BFA3082F0ECBE4BAFCE47B` |

The first is the 770-public-role native scalar word, not PR589's 661-field `WORD.json`; the second is the phase controller, not the p16/a7 BIT controller above. The recorded hashes match the raw-CU manifest. `raw_cu_recipe.cpp` has SHA-256 `CE6B6078CD76E0FB5347841220863ACFCBCBCD411CB54659C44F6F3B7E746D27`; the assembled `raw_cu_recipe.json` is SHA-256 `9C98C43332D8BAFE5D59E197AC3090CB1FA71BBFCD8CCFB0F8AD90116DCB78D6`.

The supporting certificates are specific and finite:

- `native_scalar_record_probe.cpp` (SHA-256 `987C2542254966F8D123D87729639698E8C888CC8F13167C78AF7615D35E8A63`) streams **all 770** public logical basis columns over capped exact rationals and checks all **799** output coefficients per column, along with every chart, endpoint, and owned lifetime. Its report says the local logical shear/helpers are identity on arbitrary input basis and the owned output is zero. It explicitly leaves frame operators/lowerings to the separate lowering construction.
- `native_lowering_record_certificate.cpp` (SHA-256 `8577B14AFE45AD63B7F6D97B131C5C8B5877DD68AFE7F0F2BD15D0E6C005B67F`) constructs/replays all 1,093 nine-bit frames and all 2,922 distinct ordered transitions. It checks signed Pauli maps plus an exact Gaussian-dyadic reference state, including absolute phase, and rejects wrong phase/rank. Its own output says “all-column lifting remains the mathematical proof”: the finite certificate identifies the adapters; `lem:ramframe` and `lem:clifflower` provide the general lift.
- `controller_record_probe.cpp` (SHA-256 `496ADFA861363CA40C416B85BE75BCD97F4DA144DAC18F9FCEFB38F55B064607`) verifies the phase controller on all 32 formal columns, its boundaries and the 104 port geometries. It exhausts each 9-bit phase domain (512 addresses per port), rather than randomly sampling.
- `raw_cu_recipe.cpp` checks integration/ranks only. It links all 2,922 lowering recipes, all 18 native calls, 15 query shears and 15 idles; it checks each of 3,328 main and 1,560 idle direction families for independence across the 104 port choices, exact role injection, and every invoice bin. Its source comment correctly says it does not recertify the scalar/Laurent identities.
- `raw_cu_dyadic_ledger.cpp` (SHA-256 `179A8C0968763FDED35DD424AD9CC8732BD0C622085B5E34ED99CF843115A48D`) scans all 22,803 native events and the complete 222-entry macro word. Its recorded exact ledger gives denominator charge `D=334656`, rank mass `S=240152`, norm exponent `U=380400`, with every actual point coefficient's denominator dividing 16. This proves the finite-word dyadic/width facts needed by `lem:rawdyadic`; it does not prove the recursive runtime.

The raw-CU recipe's `source_sha256` values bind its inputs, C++ source, and four recorded dependency reports (`native_scalar_record_probe.txt`, `controller_record_probe.txt`, `native_lowering_record_certificate.txt`, `record_rate_probe.txt`). A provenance limitation remains: the raw-CU script's pre-assembly gate checks those reports for a PASS marker rather than pinning their hashes there. The saved JSON then records their current hashes, and the result/ledger manifests bind the recipe inputs. The PASS marker alone does not cryptographically bind those reports to the source; the saved JSON and result/ledger manifests record the dependency hashes.

## Source proof beyond the finite certificates

1. `lem:ramframe` proves by induction on the chronological word that the physical value is the lifted current frame applied to the logical scalar value, for every column count `f`, all arbitrary complex inputs, and independent spectators. It also proves that a point coefficient remains `q`, not `q^f`. Therefore the 661- and 770-column checks are complete finite logical-map certificates; the all-`f` claim comes from the written common-frame lemma, not from running all `f`.
2. `lem:clifflower` proves the general exact transition factorization including absolute fourth-root phase. The nine-bit certificate checks the actual local inventory and emits recipes, not a dense matrix proof for all address states.
3. `prop:recordunit` constructs the actual 145-axis phase word from those records, its controller, fresh helper ownership, and independent target families. `raw_cu_recipe.cpp` checks the finite assembly and histogram but relies on the exact endpoint proofs and certificate dependencies above.
4. `lem:rawdyadic` and the exact ledger give coefficient closure in `Z[i,1/2]`; reducing `i` to `u` and `2^{-1}` to `(P+1)/2` gives the same identities over every odd `P`, with no field or irreducibility assumption.
5. `lem:wordproduct` gives an explicit tensor-product word: ranks multiply, supplied direction families are retained, point coefficients are copied once, and any dirty owned scratch is explicitly cleared. This is the mathematical bridge for products and powers.
6. `lem:strongerphasemoment` proves the stronger rational rate and budget inequalities on the same phase word. The numerical rate check supports those inequalities; `thm:finitebitcompiler` supplies the separate universal compiler proof.
7. For the PR589 supplier, `lem:pr589nativebit` gives the finite word and all-column endpoint; `lem:bitwordstrictification` supplies strict separated ranks and a moment; `lem:finitebitflow` proves exact integer job matching and ownership; and `thm:finitebitcompiler` proves by strong induction that some finite fixed rank-one word has the desired ratio. Its search termination is argued from the source/exit potential and concavity inequality. It does not materialize or execute the winning word, but it is a proof of an effective finite template, not an unsupported assertion that such a compiler exists.

## Service statements and verification boundary

The finite `native_all_columns` premise is supplied at source level: the PR589 logical operator is checked on all 661 input basis elements, its 32-wire controller on all 32 coefficient basis columns, and the common-frame lemma lifts their composition to every column count. The 145-axis phase word has separate 770-column scalar evidence, 32-column phase-controller evidence, exact lowering recipes, and a dyadic ledger.

`thm:mixedbitswap` proves the all-length opaque equal-field interchange from the finite PR589 word using the finite compiler and delayed-cover argument, with the older Stage2 theorem as a named dependency. `thm:mixedbitinteger` proves the all-odd-modulus phase/Walsh contract at leading exponent `gamma=0.996874195` using the same phase word and stronger moment/routing comparison.

The manuscript-source proofs and finite checks do not constitute a fresh kernel-checked native/Stage2 dependency closure or an end-to-end multiplier proof.
