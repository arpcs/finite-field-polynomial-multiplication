# Manuscript catalogue

1. **Paired-phase binary multiplication:**
   [PDF](papers/03-best-binary/versions/0.2.1/paper.pdf),
   [TeX](papers/03-best-binary/versions/0.2.1/main.tex),
   [proof scope](papers/03-best-binary/versions/0.2.1/README.txt),
   [exact claim](papers/03-best-binary/versions/0.2.1/CLAIM.json).
   States ordinary F2 multiplication in O(n log(n+2)^(1301/1302))
   deterministic bit time on fixed finite tapes, with all 2n-1 output bits.
2. **General fixed-field multiplication:** [PDF](papers/01-general/paper.pdf),
   [TeX](papers/01-general/main.tex), [status](papers/01-general/STATUS.md).
   States O_q(n log(n+2)^(1301/1302)) over each fixed finite field and
   O_q(n log(n+2)^(319/320)) over each fixed field of odd characteristic.
   Its characteristic-two branch uses the paired-phase theorem through a fixed-basis reduction.
   The [native supplement](papers/01-general/proofs/stronger-odd-20261102/README.md)
   supplies the odd-field host transfer, native services and finite premises.
   Constants depend on the individually fixed field; growing-field
   uniformity and a combined workspace bound are outside the statements.
3. **Fast Pascal transforms:** [PDF](papers/02-simple-binary/paper.pdf),
   [TeX](papers/02-simple-binary/main.tex), [status](papers/02-simple-binary/STATUS.md).
   States ordinary F2 multiplication in O(n log(n+2)), with an explicit
   evaluator, decoder and tensor proof, and a fixed characteristic-two
   extension corollary.
4. **General n log n baseline:** [PDF](papers/04-general-nlogn/paper.pdf),
   [TeX](papers/04-general-nlogn/main.tex), [status](papers/04-general-nlogn/STATUS.md).
   States ordinary multiplication over each fixed finite field in
   O_q(n log(n+2)) bit time. It combines the Pascal/Taylor binary theorem,
   the general paper's odd-field proposition and a fixed-basis reduction.
5. **Controlled-CRT binary multiplication:** [PDF](papers/03-best-binary/paper.pdf),
   [TeX](papers/03-best-binary/main.tex), [status](papers/03-best-binary/STATUS.md).
   States exponent 1-2^-38 as a separate binary construction. The general
   paper uses the paired-phase theorem for its common exponent.

The odd-field proposition is independent of the binary theorems. The
manuscripts share finite-network and interchange antecedents; their
dependency relationships are detailed in the
[claim map](docs/CLAIM_SELECTION.md).

Each manuscript supplies author/contact information, substantial-AI
disclosure, references and evidence records. Independent human mathematical
review and complete formal verification remain outstanding. Build receipts
bind each PDF to its exact sources. Conditional orthogonal-tree
transfers and integer/complex-DFT investigations are outside these statements.

See [VERIFICATION.md](VERIFICATION.md) for the evidence scope and
[version history](docs/VERSION_HISTORY.md) for manuscript provenance.
