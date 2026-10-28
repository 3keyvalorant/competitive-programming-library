# competitive-programming-library

AtCoder / Codeforces にそのまま提出できる GNU++17 競技プログラミングライブラリです。ヘッダーは `library/` に分割し、`python tools/bundle.py` で単一ファイルの `template.cpp` を生成できます。

## 一覧

`Verified` は現時点の検証状態です。`local` はローカルのコンパイル／ランダム差分テスト済み、`adapter` は Library Checker 用コードをコンパイル済み（オンライン提出は未実施）を表します。

| Category | Library | File | Complexity | Verified |
|---|---|---|---|---|
| Basic | helpers / compression | `library/basic/base.hpp` | compression `O(N log N)` | local |
| Basic | input/output / graph reader / container shortcuts | `library/basic/convenience.hpp` | mostly `O(N)` wrappers | local |
| Basic | 1D/2D prefix sum / grid rotate | `library/basic/prefix_sum.hpp` | build `O(HW)`, query `O(1)` | local, adapter |
| Math | ModInt | `library/math/modint.hpp` | `+`, `-`, `*`: `O(1)`; inverse: `O(log MOD)`; power: `O(log exponent)` | local differential |
| Math | MontgomeryModInt / fastmint / fastamint | `library/math/montgomery_modint.hpp` | arithmetic `O(1)`; inverse `O(log MOD)`; odd `1 < MOD < 2^30` | local differential |
| Math | adaptive Combination | `library/math/combination.hpp` | small `N`: build `O(N)`, query `O(1)`; large `N`: query `O(min(r,n-r) + log MOD)` per base-`MOD` digit | local random |
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
print(::sorted_unique(a)); // C++23のstd::sorted_uniqueタグとの名前衝突を避ける

auto dp = make_vec(n, m, LINF);
ll x = first_true(0LL, 1'000'000'001LL, [&](ll v){ return condition(v); });

int u, v;
scan1(u, v);          // 1-indexed input -> 0-indexed values
st(a); unq(a);        // familiar short form: sort, then erase adjacent duplicates
auto p = indices(n);  // {0,1,...,n-1}
auto deg = degrees(g);

auto s = prefix_1Dsum(a); // existing submission name; same as prefix_sum(a)
int pos = lb(a, x);       // lower_bound position
rep(k, 4){ int ni = i + tate[k], nj = j + yoko[k]; }
Yes;                     // both `Yes;` and `Yes();` are supported
```

## ModInt の高速化

`mint`、`amint`、`ModInt<MOD>` の使い方と、`v` / `val()` が通常の剰余を返す仕様はそのままです。
乗算は符号なし64bit演算、逆元は32bitの除算を使い、逆元の最後の不要な剰余計算も省きます。
法は `1 <= MOD <= INT_MAX`。加算もこの範囲でオーバーフローしません。逆元・除算は法と互いに素な値に対して使ってください。

乗算を繰り返す計算向けに `MontgomeryModInt<MOD>`、`fastmint`、`fastamint` も使えます。
通常の32/64bit整数演算だけを使い、CPU固有命令・インラインアセンブリ・`-march=native` に依存しません。
法は奇数かつ `1 < MOD < 2^30`。内部表現を変えているので値は `.val()` で取得します。公開メンバー `.v` が必要なら従来の `mint` / `amint` を使ってください。

```cpp
fastmint answer = 1;
for (int i = 1; i <= n; ++i) answer *= i;
cout << answer.val() << '\n';
combination<fastmint> co(200000);
```

`convolution(vector<mint>, vector<mint>)` は適用可能な法でMontgomery形式を自動利用し、戻り値の型はそのままです。NTTの回転因子も段ごとに再利用して乗算回数を削減します。NTTの追加メモリは `O(N)` です。
大きな `N` の `combination` は分母をまとめ、1桁あたりの逆元計算を `min(r,n-r)` 回から1回へ削減します。

単発の逆元・入出力・累乗が中心だとMontgomery形式の変換コストで遅くなる場合もあります。用途に合わせて通常型も比較してください。
再計測用コードは**直前の版 `f5c2173`** と比較し、改善しないケースも含めて出力します。7回の中央値を使い、処理結果の一致も確認します。

```bash
g++ -std=c++17 -O2 tools/benchmark_modint.cpp -o .build/benchmark_modint
.build/benchmark_modint
```

CIはGitHubのLinux環境（x86-64 / ARM64）でGCC / Clangの両方について、GNU++17/20/23のテスト、AddressSanitizer / UndefinedBehaviorSanitizer、`-O2` のベンチマークを実行します。CPU・コンパイラ情報と全計測結果をログに残し、CSVを `benchmark-<OS>-<compiler>` として保存します。共有サーバー上の計測値には変動があるため、速度の合否閾値は設けません。

方式の参考: [Peter L. Montgomery, Modular Multiplication Without Trial Division (1985)](https://www.ams.org/journals/mcom/1985-44-170/S0025-5718-1985-0777282-X/S0025-5718-1985-0777282-X.pdf)。

## 検証

```bash
python tools/test.py
```

GNU++17/20/23 で全ヘッダーと `verify/` をコンパイルし、`tests/random_test.cpp` と `tests/modint_test.cpp` を実行します。ModInt は負数・整数の端の値・合成数の法・`INT_MAX` の法を含む差分テストと、組合せ・NTT畳み込みを検証します。CIも同じコマンドを使用します。Library Checkerアダプタは `verify/` にありますが、オンラインjudgeへ未提出のため「Library Checker verified」とは表記していません。

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
