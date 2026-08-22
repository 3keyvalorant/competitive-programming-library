# Development rules

- Keep every library compatible with GNU++17 or later and directly submitable to AtCoder/Codeforces.
- `bits/stdc++.h` is allowed. GCC extensions must be common in contest environments; avoid CPU-specific `#pragma GCC target`.
- Preserve existing user APIs unless there is a concrete correctness or safety reason to change them.
- Prefer short, readable implementations. Do not code-golf at the cost of clarity.
- Add a Library Checker verify program when a matching problem exists.
- Otherwise add a small random differential test against a brute-force implementation.
- Prefer iterative implementations when recursion may overflow around `N = 2e5`.
- Record new libraries and their complexity in README.md.
- Never call code “verified” unless the corresponding check has actually been run.
- Do not add heuristic/marathon-only utilities to this repository.
- Run `python tools/test.py` and regenerate `template.cpp` before opening a pull request.

