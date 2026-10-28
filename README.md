# competitive-programming-library

AtCoder / Codeforces にそのまま提出できる GNU++17 競技プログラミングライブラリです。ヘッダーは `library/` に分割し、`python tools/bundle.py` で単一ファイルの `template.cpp` を生成できます。

## 一覧

`Verified` は現時点の検証状態です。`local` はローカルのコンパイル／ランダム差分テスト済み、`adapter` は Library Checker 用コードをコンパイル済み（オンライン提出は未実施）を表します。

| Category | Library | File | Complexity | Verified |
|---|---|---|---|---|
| Basic | helpers / compression | `library/basic/base.hpp` | compression `O(N log N)` | local |
| Basic | input/output / graph reader / container shortcuts | `library/basic/convenience.hpp` | mostly `O(N)` wrappers | local |
| Basic | 1D/2D prefix sum / grid rotate | `library/basic/prefix_sum.hpp` | build `O(HW)`, query `O(1)` | local, adapter |
| Math | ModInt (Montgomery default / basic fallback) | `library/math/modint.hpp` | `+`, `-`, `*`: `O(1)`; inverse: `O(log MOD)`; power: `O(log exponent)` | local differential, migration tests |
| Math | adaptive Combination / H / multinomial | `library/math/combination.hpp` | tables: build `O(N)`, C/H `O(1)`, K-group multinomial `O(K)`; large values: C via Lucas/products | local random |
| Math | batch inverse | `library/math/batch_inverse.hpp` | `O(N + log MOD)`, one inverse | local differential, operation counts |
| Math | NTT convolution / square | `library/math/convolution.hpp` | `O(N log N)`; square uses two transforms | local random, adapter |
| Math | subset/superset zeta / Mobius / OR・AND convolution | `library/math/subset_transform.hpp` | `O(B 2^B)` time | local differential, adapter |
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

フーリエ変換・畳み込みによる数え上げは、通常テンプレートと別枠の [追加パック](docs/convolution.md) にまとめています。入口は `library/convolution/all.hpp`、単一ファイル版は `convolution_template.cpp` です。

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

## ModInt：高速版を標準化

`mint`・`amint` は既定でMontgomery形式を使います。`fastmint`・`fastamint` は、それぞれと同じ型を指す互換名になりました。
`+ - * /`、比較、`val()`、`mod()`、`pow()`、`inv()`、入出力の使い方は従来どおりです。

`ModInt<MOD>` は法が奇数かつ `1 < MOD < 2^30` ならMontgomery、それ以外は通常の剰余計算をコンパイル時に選びます。
偶数の法や `2013265921` のような大きい法も、引き続き使えます。全体の対応範囲は `1 <= MOD <= INT_MAX` です。
通常の32/64bit整数演算だけを使い、CPU固有命令・インラインアセンブリ・`-march=native` に依存しません。

| 型・名前 | 動作 |
|---|---|
| `mint` / `amint` | 998244353 / 1000000007、Montgomery形式 |
| `fastmint` / `fastamint` | `mint` / `amint` と同じ型 |
| `BasicModInt<MOD>` | 通常の剰余計算を明示的に選ぶ |
| `MontgomeryModInt<MOD>` | Montgomery形式を明示。奇数かつ `1 < MOD < 2^30` が必要 |

移行時は次の点に注意してください。

- 公開メンバー `.v` は廃止しました。値は常に `.val()` で取得してください。内部表現を直接読み書きできません。
- `mint` と `fastmint` は同じ型なので、それぞれに別の関数オーバーロードを定義していた場合は統合が必要です。
- 整数コンストラクタの入力範囲は `long long` です。ACLなど他実装との完全なAPI互換は保証しません。
- `raw(v)` は `0 <= v < MOD` の通常の剰余を受け取り、内部形式へ変換します。逆元・除算には法と互いに素な値を使ってください。

以前の `math/montgomery_modint.hpp` は互換用のincludeだけを残し、実装は `math/modint.hpp` に統合しました。

```cpp
mint answer = 1; // これだけで高速版
for (int i = 1; i <= n; ++i) answer *= i;
cout << answer.val() << '\n';
combination<mint> co(200000);
```

`convolution(vector<mint>, vector<mint>)` は既定型をそのまま使い、通常型との変換や複製を省きます。`convolution<MOD,Root>(a,b)` の明示呼び出しも維持しています。
NTTの回転因子も段ごとに再利用して乗算回数を削減します。NTTの追加メモリは `O(N)` です。
大きな `N` の `combination` は分母をまとめ、1桁あたりの逆元計算を `min(r,n-r)` 回から1回へ削減します。

単発の逆元・入出力・累乗が中心だとMontgomery形式の変換コストで遅くなる場合もあります。その場合は `BasicModInt<MOD>` と比較できます。
再計測用コードは通常演算・NTT・巨大組合せを版 `f5c2173` と比較し、改善しないケースも含めて出力します。二乗は一般の畳み込み、`batch_inverse` は個別の `inv()` を基準に比較します。7回の中央値を使い、処理結果の一致も確認します。

```bash
g++ -std=c++17 -O2 tools/benchmark_modint.cpp -o .build/benchmark_modint
.build/benchmark_modint
```

CIはGitHubのLinux環境（x86-64 / ARM64）でGCC / Clangの両方について、GNU++17/20/23のテスト、AddressSanitizer / UndefinedBehaviorSanitizer、`-O2` のベンチマークを実行します。CPU・コンパイラ情報と全計測結果をログに残し、CSVを `benchmark-<OS>-<compiler>` として保存します。共有サーバー上の計測値には変動があるため、速度の合否閾値は設けません。

方式の参考: [Peter L. Montgomery, Modular Multiplication Without Trial Division (1985)](https://www.ams.org/journals/mcom/1985-44-170/S0025-5718-1985-0777282-X/S0025-5718-1985-0777282-X.pdf)。

## 環境に依存しにくい処理削減

すべてのCPU・入力で実行時間が必ず短くなる保証はできません。通常の演算APIを保ったうえで、処理回数を減らせる場面に専用の操作を用意しています。

| 場面 | 使い方 | 減らす処理 |
|---|---|---|
| 複数の逆元 | `batch_inverse(a)` | 逆元N回 → 1回と `3(N-1)` 回の乗算 |
| 多項式の二乗 | `convolution_square(a)` | NTT3回 → 2回。小さい場合も対称性で乗算を削減 |
| 組合せの端 | `co.C(n,0)`, `co.C(n,1)` など | 恒等式で直接返し、逆元計算・乗算を省略 |
| 通常の小さいnの組合せ | `co.C(n,r)` | 不要なLucas分解と高位桁の処理を省略 |

`batch_inverse` は全要素が法と互いに素である必要があります。0や逆元を持たない値は渡さないでください。
空配列には空配列を返します。これらの操作回数は `tests/core_efficiency_test.cpp` でも確認します。

## 別枠：フーリエ変換・数え上げ

`library/convolution/` に、FFT、整数の正確な畳み込み、任意modの畳み込み、ペアの和・繰り返し選択の数え上げを用意しています。
通常の `library/all.hpp` には追加せず、必要なときだけ読み込みます。用途・計算量・精度と入力範囲は [使い方と履修メモ](docs/convolution.md) を参照してください。

| 機能 | ファイル | 計算量 |
|---|---|---|
| FFT / 実数畳み込み | `library/convolution/fft.hpp` | `O(L log L)` |
| 整数 / 任意mod畳み込み | `library/convolution/exact.hpp` | `O(L log L)`、NTTを3種類の法で実行 |
| ペアの和の数え上げ | `library/convolution/counting.hpp` | `O(N+M+L log L)` |
| K回選択した和の分布 | `library/convolution/counting.hpp` | `O(W+S+L log L log(K+1))`、Wはwaysの長さ |

Lは畳み込みに必要な長さを2の冪へ切り上げた値です。追加パックもローカルの差分テスト対象です。

```bash
python tools/bundle.py --entry library/convolution/all.hpp --output convolution_template.cpp
```

## 別枠：確率・期待値と行列

`library/probability/all.hpp` と `probability_template.cpp` を追加しています。重複組合せ・多項係数・部分集合変換は通常テンプレートでも使えます。確率・行列の大きな機能は必要なときだけ読み込めます。

| 機能 | ファイル | 計算量・条件 |
|---|---|---|
| 独立Bernoulli試行の成功回数分布 | `library/probability/distribution.hpp` | `O(N^2)` 時間、`O(N)` メモリ |
| 二項分布 | 同上 | 実数 `O(N)`、mod `O(N+log MOD)`。mod版は原則N<MOD |
| 分布の期待値・分散 | 同上 | `O(N)`、非空・正規化済みの分布 |
| 自己ループ1個の期待値の式変形 | 同上 | 除算1回、分母0は拒否 |
| 行列積 / 累乗 | `library/math/matrix.hpp` | 積 `O(NKM)`、S×SのK乗 `O(S^3 log(K+1))` |
| 連立方程式・mod版 / 実数版 | `library/math/linear_equations.hpp` | n式m変数で `O(nm min(n,m)+m^2)` |

実数版は近似計算です。modの確率・連立方程式には素数の法などの体と、逆元を持つ分母を使ってください。
[使い方と期待値DPの例集](docs/probability.md) に、コイン、自己ループ、クーポン、循環する状態の期待値、行列遷移をまとめています。
実行できる例は `examples/probability_expectation.cpp` です。

```bash
python tools/bundle.py --entry library/probability/all.hpp --output probability_template.cpp
```

## 検証

```bash
python tools/test.py
```

GNU++17/20/23 で全ヘッダーと `verify/`・`examples/` をコンパイルし、`tests/*_test.cpp` を実行します。通常版・畳み込み版・確率版の単一ファイルも生成してコンパイルします。ModInt・組合せ・NTT・整数CRT・部分集合変換は差分テスト、FFTは許容誤差付きの比較、数え上げ・確率・連立方程式は小さな全探索との比較などで検証します。CIも同じコマンドを使用します。Library Checkerアダプタは `verify/` にありますが、オンラインjudgeへ未提出のため「Library Checker verified」とは表記していません。

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
