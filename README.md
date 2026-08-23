# competitive-programming-library

AtCoder / Codeforces にそのまま提出できる GNU++17 競技プログラミングライブラリです。ヘッダーは `library/` に分割し、`python tools/bundle.py` で単一ファイルの `template.cpp` を生成できます。

## 一覧

`Verified` は現時点の検証状態です。`local` はローカルのコンパイル／ランダム差分テスト済み、`adapter` は Library Checker 用コードをコンパイル済み（オンライン提出は未実施）を表します。

| Category | Library | File | Complexity | Verified |
|---|---|---|---|---|
| Basic | helpers / compression | `library/basic/base.hpp` | compression `O(N log N)` | local |
| Basic | input/output / graph reader / container shortcuts | `library/basic/convenience.hpp` | mostly `O(N)` wrappers | local |
| Basic | 1D/2D prefix sum / grid rotate | `library/basic/prefix_sum.hpp` | build `O(HW)`, query `O(1)` | local, adapter |
| Math | ModInt / adaptive Combination | `library/math/` | small `N`: build `O(N)`, query `O(1)`; large `N`: query `O(min(r,n-r))` per base-`MOD` digit | local random |
| Math | NTT convolution | `library/math/convolution.hpp` | `O(N log N)` | local random, adapter |
| Math | sieve / factorization / extgcd / CRT / integer sqrt | `library/math/number_theory.hpp` | sieve `O(N log log N)`, factorization `O(sqrt N)` | local |
| Data structure | Union-Find / Weighted Union-Find | `library/data_structure/union_find.hpp` | amortized `O(alpha(N))` | local, adapter |
| Data structure | Rollback Union-Find | `library/data_structure/rollback_union_find.hpp` | merge `O(log N)`, undo `O(1)` | local random |
| Data structure | Binary Trie | `library/data_structure/binary_trie.hpp` | operation `O(B)` | local random |
| Data structure | Fenwick tree | `library/data_structure/fenwick_tree.hpp` | build `O(N)`, query/update `O(log N)` | local, adapter |
| Data structure | Segment tree / Lazy segment tree | `library/data_structure/*segtree.hpp` | build `O(N)`, query/update `O(log N)` | local |
| Data structure | Sparse table | `library/data_structure/sparse_table.hpp` | build `O(N log N)`, query `O(1)` | local, adapter |
| Data structure | Li Chao Tree | `library/data_structure/li_chao_tree.hpp` | add/query `O(log N)` | local random, adapter |
| Data structure | Wavelet Matrix | `library/data_structure/wavelet_matrix.hpp` | query `O(B)` | local random, adapter |
| Graph | BFS / 01-BFS / Dijkstra / Bellman-Ford / Floyd-Warshall / topo sort | `library/graph/shortest_path.hpp` | standard bounds | local, adapter |
| Graph | SCC / 2-SAT | `library/graph/scc.hpp`, `two_sat.hpp` | `O(N+M)` | local, adapter |
| Graph | Kruskal / Dinic | `library/graph/mst.hpp`, `dinic.hpp` | `O(M log M)`, `O(V^2E)` | local |
| Graph | Min-Cost Flow | `library/graph/min_cost_flow.hpp` | initial `O(VE)`, then `O(F E log V)` | local |
| Graph | LowLink | `library/graph/lowlink.hpp` | `O(N+M)` | local |
| Graph | Two-edge-connected components | `library/graph/two_edge_connected_components.hpp` | `O(N+M)` | local, adapter |
| Graph | cycle recovery | `library/graph/cycle.hpp` | ordinary/odd `O(N+M)`; shortest/even `O(M(N+M))` | local random |
| Tree | Binary lifting / Euler tour | `library/tree/` | build `O(N log N)`, LCA `O(log N)` | local |
| Tree | HLD / Rerooting | `library/tree/heavy_light_decomposition.hpp`, `rerooting.hpp` | build `O(N)`, path `O(log N)` segments | local random, HLD adapter |
| Graph | Functional graph | `library/algorithm/functional_graph.hpp` | build `O(N log K)`, jump `O(log K)` | local random |
| String | Rolling hash / Z / KMP / Manacher | `library/string/` | build/search `O(N)` | local, Z adapter |
| String | Suffix Array / LCP | `library/string/suffix_array.hpp` | `O(N log N)` / `O(N)` | local random, adapter |
| Algorithm | LIS / run-length encoding | `library/algorithm/` | `O(N log N)` / `O(N)` | local |
| Algorithm | Mo's algorithm query ordering | `library/algorithm/mo.hpp` | typical `O((N+Q)sqrt(N))` moves | local random |

## 最小使用例

```cpp
#include "library/all.hpp"

int main(){
    UnionFind uf(4);
    uf.merge(0, 1);
    FenwickTree<long long> fw(vector<long long>{1, 2, 3});
    cout << uf.same(0, 1) << ' ' << fw.sum(0, 3) << '\n';
}
```

頻出処理は次のように短縮できます。

```cpp
int n, m;
scan(n, m);
auto a = read_vector<ll>(n);
auto g = read_graph(n, m); // 1-indexed入力を0-indexed隣接リストへ
print(sorted_unique(a));

auto dp = make_vec(n, m, LINF);
ll x = first_true(0LL, 1'000'000'001LL, [&](ll v){ return condition(v); });

int u, v;
scan1(u, v);          // 1-indexed input -> 0-indexed values
st(a); unq(a);        // familiar short form: sort, then erase adjacent duplicates
auto p = indices(n);  // {0,1,...,n-1}
auto deg = degrees(g);
```

## 検証

```bash
python tools/test.py
```

GNU++17/20/23 で全ヘッダーと `verify/` をコンパイルし、`tests/random_test.cpp` を実行します。CIも同じコマンドを使用します。Library Checkerアダプタは `verify/` にありますが、オンラインjudgeへ未提出のため「Library Checker verified」とは表記していません。

## 注意

- `combination<T>(N)` は `N <= 2,000,000` なら階乗表を構築し、それより大きければ巨大配列を確保せず乗算式へ切り替えます。`N >= MOD` の `C` はLucasの定理を使うため、`MOD` は素数を想定します。
- NTTは既定で `998244353` と原始根 `3` を使用します。他の法ではNTT可能な素数と原始根をテンプレート引数で指定してください。
- Wavelet Matrixは符号なし整数用です。値域が分かる場合は `WaveletMatrix<unsigned, 30>` のようにビット数を絞るとメモリと定数倍を削減できます。
- `read_graph/read_tree` は既定で1-indexed入力を0-indexedへ変換します。0-indexed入力では最後の引数に `0` を指定してください。
- Rolling hash は法 `2^61-1` の単一ハッシュで、衝突確率は低いもののゼロではありません。
- cycle API は返す頂点列の末尾に始点を重複させません。現在の隣接リストAPIは平行辺のedge idを保持しません。
- Min-Cost Flow は到達可能な負閉路がないことを前提とします。Li Chao Treeの問い合わせ座標は構築時に渡してください。
- 一般グラフの「長さK以上の単純サイクル」は困難なため、見逃し得るヒューリスティック版は収録していません。
- Timer、XorShift、焼きなまし等のAHC専用品は対象外です。
