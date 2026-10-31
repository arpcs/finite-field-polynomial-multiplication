# Finite witness bundle

This directory contains two bounded C++17 witnesses and their supporting fixture/header:

- `code/bounded_prefix_macro_fft.cpp` checks the finite all-prefix evaluator/radix identities and its binary transpose.
- `code/bounded_prefix_macro_parent.cpp` includes the evaluator and checks finite parent/raw multiplication and ordinary adjoints.
- `code/bounded_periodic_boundary_filter.cpp` and `code/bounded_binary_karatsuba.hpp` provide their fixtures and bounded arithmetic support.

Each executable installs a Windows job limit of 64 MiB process memory and 10 CPU seconds before algebra and refuses to proceed if it cannot install the limit. `verify-witnesses.ps1` compiles/runs only these two programs. The historical JSON receipts in `code/` were produced by the source packet on 30 October 2026; they are copied as receipts and are not newly regenerated for this focused release. Run the script to create new outputs under `build/`.

These programs use ordinary finite Pascal cores. They do not time the fast H2 tensor machine, implement the asymptotic multiplier, or verify its O(n log n) proof. Their assertions are finite algebra/indexing evidence only. Source and report SHA-256 provenance is recorded in the parent `audit.json`.
