# Exact Binary Polynomial Multiplication from Fast Pascal Transforms

Focused first-release paper for ordinary polynomial multiplication over the fixed field F2. `main.tex` is the standalone TeX entry point, its inputs are included here, and `paper.pdf` is the compiled document. Build receipts are recorded under the collection's `verification/` directory.

The manuscript claims an exact deterministic O(n log(n+2)) bit-time algorithm on one fixed finite-alphabet multitape Turing machine, using the explicitly cited arbitrary-width equal-chunk interchange theorem as an external dependency. `references.tex` pins the citation revision to `4eaee87548250b2682affda7d05d947c05554bae`; the historical local text hash in `evidence.tex` is a separate provenance record. It also states the fixed characteristic-two extension corollary. The abstract, theorem statements and cost proof specify the model and field quantifiers.

Lean formalization is unfinished. The manuscript discloses substantial generative AI assistance. It claims internal review only; it does not claim external peer review, formal certification, or priority.

Two bounded finite witnesses and historical JSON receipts are included under `witnesses/`; see that folder’s README. The receipts are from the reviewed source packet dated 30 October 2026 and were not regenerated for this focused release. The witnesses check finite algebra/indexing only and do not implement the asymptotic multiplier or certify its running-time proof.
