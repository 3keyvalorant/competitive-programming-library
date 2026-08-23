# HANDOFF

## Implemented

- Basic helpers, prefix sums, coordinate compression, grid helpers
- Convenience helpers for input/output, graph loading, containers, multidimensional vectors, and integer binary search
- ModInt, combinations, number theory
- NTT convolution
- Union-Find, weighted Union-Find, Fenwick tree, segment trees, sparse table
- Graph traversal, shortest paths, SCC, 2-SAT, MST, max flow, cycle utilities
- Binary lifting, Euler tour, functional graph
- Heavy-Light Decomposition, rerooting, LowLink
- Min-Cost Flow, Binary Trie, Li Chao Tree, Mo's algorithm
- Rollback Union-Find, Wavelet Matrix, two-edge-connected components
- Rolling hash, Z algorithm, KMP, Manacher, LIS, run-length encoding
- Suffix Array and LCP array

## Verification status

- **Locally tested:** all headers compile under GNU++17; `tests/random_test.cpp` covers core structures and graph/string algorithms.
- **Library Checker adapters:** compile-tested only. They are not described as judge-verified until submitted.
- **Not yet verified:** all adapters against the online Library Checker judge; exhaustive multigraph cycle recovery beyond local randomized tests.

## Known issues / API changes

- Heuristic utilities, Timer, and XorShift from the original monolithic file are intentionally excluded.
- `unionfind<T>` remains as a compatibility alias and `marge` remains as an alias of `merge`.
- `combination<T>` now selects factorial-table or multiplicative/Lucas mode from its initialization value. Public `C/P/get/calu` arguments were widened from `int` to `long long` without breaking ordinary calls.
- Cycle functions accept adjacency lists and return a vertex sequence without repeating the first vertex.
- Parallel-edge identity is not represented by `vector<vector<int>>`; edge-specific multigraph work should use an edge-id graph in a future extension.

## Library Checker status

- Adapters exist for union-find, point-add/range-sum, static range sum/RMQ, shortest path, SCC, 2-SAT, Z algorithm, suffix array, vertex-add/path-sum, line-add/get-min, convolution, range-kth-smallest, and two-edge-connected components.
- Status: locally compile-tested, not online-judge verified.

## Next candidates

- Pollard-Rho factorization, biconnected components, offline dynamic connectivity, Disjoint Sparse Table
- Online Library Checker submissions and badges
- Edge-id based cycle API for multigraph-specific queries
