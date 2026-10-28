# 数え上げ・確率・期待値の道具と例集

通常テンプレートには重複組合せ・多項係数・部分集合変換を追加しています。
確率分布・行列・連立方程式まで使う場合は、別枠の次の入口を読み込みます。

```cpp
#include "library/probability/all.hpp"
```

単一ファイル版は `probability_template.cpp` です。既存の `template.cpp` や畳み込み専用版はそのまま使えます。
実行できる一式は `examples/probability_expectation.cpp` にあります。

## 何を使うか

| やりたいこと | 入口 | 計算量 |
|---|---|---|
| n種類から重複を許してr個選ぶ | `co.H(n,r)` | `C(n+r-1,r)` 1回 |
| 同じものを含む並べ方 | `co.multinomial(counts)` | 階乗表の範囲内ならグループ数Kに対して `O(K)`、他はCを高々K回 |
| 成功確率が異なる独立試行の成功回数 | `cp_probability::bernoulli_sum_distribution(p)` | `O(N^2)` 時間、`O(N)` メモリ |
| 同じ成功確率でN回試す | `cp_probability::binomial_distribution(N,p)` | 実数 `O(N)`、mod版 `O(N+log MOD)` |
| 分布から期待値・分散を計算 | `cp_probability::expectation(pmf)` / `variance(pmf)` | `O(N)` |
| 同じ状態に留まる期待値DP | `cp_probability::self_loop_expectation(c,other,stay)` | フィールド上の除算1回 |
| 行列を掛ける | `cp_linear::matrix_multiply(a,b)` | N×KとK×Mなら `O(NKM)` |
| 遷移をK回繰り返す | `cp_linear::matrix_power(a,K)` | S×Sなら `O(S^3 log(K+1))` |
| mod上の連立一次方程式 | `cp_linear::gauss_jordan(a,b)` | n式m変数で `O(nm min(n,m)+m^2)` |
| 実数の連立一次方程式 | `cp_linear::solve_linear_real(a,b)` | 同上、許容誤差付き |
| 部分集合／上位集合の総和 | `cp_subset::subset_zeta(a)` / `superset_zeta(a)` | 長さ2^Bに対して `O(B 2^B)` |
| 上記の逆変換 | `cp_subset::subset_mobius(a)` / `superset_mobius(a)` | `O(B 2^B)` |
| ビットOR／ANDで合成する数え上げ | `cp_subset::bitwise_or_convolution(a,b)` / `bitwise_and_convolution(a,b)` | `O(B 2^B)` |

`cp_probability::binomial_distribution` は必ず名前空間を付けてください。乱数生成用の `std::binomial_distribution` とは別物です。

## 1. 重複組合せと多項係数

```cpp
combination<mint> co(100);
cout << co.H(3, 4) << '\n';                 // 15
cout << co.multinomial({2, 1, 1}) << '\n'; // 12
```

`H(3,4)` は、区別しない玉4個を区別する箱3個に分ける方法です。空の箱を許します。
`multinomial({2,1,1})` は、Aが2個・BとCが1個ずつある4文字の並べ方 `4!/(2!1!1!)` です。

`H(0,0)=1`、`H(0,r>0)=0`、空の多項係数は1です。負の引数・個数には0を返します。
`n+r-1` や個数の合計が `long long` を超えると `overflow_error` になります。
法は従来の `C` と同じく素数を想定し、合計が法以上ならLucasの定理に対応した `C` を利用します。

## 2. 確率を実数で扱うか、modで扱うか

```cpp
long double p_real = 1.0L / 3;
mint p_mod = mint(1) / 3;
```

実数は確率そのものに近い値を持ちますが、丸め誤差があります。
modでは有理数を逆元で表現します。`p_mod.val()` は小数の確率ではありません。
分母は法と互いに素である必要があります。mod版の確率入力から、実数として0〜1かどうかは判定できません。

実数入力の確率は有限な0〜1の範囲を検査します。浮動小数点型と `mint` / `fastmint` を想定しており、`int` による確率の整数除算は使えません。

## 3. コインの成功回数

```cpp
auto pmf = cp_probability::bernoulli_sum_distribution(
    vector<long double>{0.5L, 0.25L});
// pmf = {0.375, 0.5, 0.125}
cout << cp_probability::expectation(pmf) << '\n'; // 0.75
cout << cp_probability::variance(pmf) << '\n';    // 0.4375

auto same = cp_probability::binomial_distribution(3, mint(1) / 2);
// 0〜3回成功の確率。mod上で {1/8,3/8,3/8,1/8}
```

`pmf[k]` は「ちょうどk回成功」の確率です。両関数とも試行の独立性を仮定します。
空の試行列やN=0の分布は `{1}`、成功確率0・1も扱えます。
同じ確率を繰り返すなら、二項分布の関数を使うと `O(N^2)` のDPを避けられます。

実数の二項分布は最頻値付近から両側へ計算し、端の極小確率から始めることによるアンダーフローを避けます。
非常に小さい裾の確率まで厳密に保持する保証はありません。
mod版の二項分布は素数の法かつ `N<MOD` が必要です。ただし確率0・1の決定的な場合はNが法以上でも扱えます。
異なる確率のDPは逆元を追加計算せず、入力した確率を使って分布を構築します。

`expectation` / `variance` は「添字kを値とする、非空で合計1の分布」を受け取ります。
実数では合計の誤差を `max(1e-12,64*epsilon(T))` まで許し、modでは厳密に合計1を要求します。
勝手な正規化はしません。分散は `Σ p[k]*(k-平均)^2` で計算し、大きな二乗同士の引き算を避けています。

期待値だけが必要なら、分布全体を求めなくてよい場合があります。
成功回数の期待値は `Σ p[i]` です。この等式には試行の独立性は不要です。
一方、独立試行の分散を `Σ p[i]*(1-p[i])` とする式には独立性が必要です。

## 4. 後ろから計算できる期待値DP

「各回1マスか2マス進む、どちらも確率1/2。ゴールに達したら終了」という例です。
`E[i]` を位置iからの残り回数の期待値とすると、後ろから計算できます。

```cpp
int goal = 3;
mint half = mint(1) / 2;
vector<mint> E(goal + 1);
for (int i = goal - 1; i >= 0; --i)
    E[i] = 1 + half * E[i + 1] + half * E[min(goal, i + 2)];
// E[0] = 9/4
```

この形なら、行列や連立方程式は不要です。まず状態と遷移を決めることが重要です。

## 5. 自己ループを含む期待値DP

式が `E = c + other + stay*E` なら、`E=(c+other)/(1-stay)` と整理します。
`other` は、**自分以外の次状態の期待値に、その遷移確率を掛けたものの合計**です。

```cpp
mint E = cp_probability::self_loop_expectation(mint(1), mint(0), mint(1)/2);
// 確率1/2で終了するまで試行する回数：E=2
```

3種類のクーポンを等確率で引いて集める例では、既にhave種類あると自己ループ確率は `have/3` です。

```cpp
vector<mint> E(4);
for (int have = 2; have >= 0; --have){
    mint stay = mint(have) / 3;
    E[have] = cp_probability::self_loop_expectation(
        mint(1), (mint(1)-stay)*E[have+1], stay);
}
// E[0] = 11/2
```

`stay=1`、またはmod上で `1-stay=0` なら、一意に割れないため `domain_error` です。
この関数が扱うのは自己ループ1個の式変形で、複数状態が循環する場合の汎用ソルバーではありません。

## 6. 状態が循環するとき：連立方程式

`E0=1+E0/2+E1/2`, `E1=1+E0/4` の例です。
ゴールの期待値を0とし、未知の期待値を左辺に集めます。

```cpp
auto solution = cp_linear::solve_linear_real(
    {{0.5L,-0.5L},{-0.25L,1.0L}}, {1.0L,1.0L});
if (solution.consistent && solution.kernel.empty()){
    cout << solution.particular[0] << '\n'; // 4
    cout << solution.particular[1] << '\n'; // 2
}
```

mod上では `cp_linear::gauss_jordan(Matrix<mint>, vector<mint>)` を使います。
返り値は次の意味です。

- `consistent`：解が存在するか。falseなら解ベクトルは使えません。
- `rank`：係数行列の階数です。自由度ではありません。
- `particular`：解の一例。
- `kernel`：自由に動かせる方向の基底。全解は `particular + Σ t[i]*kernel[i]`。

解があり `kernel` が空なら一意解です。解なし・複数解も区別します。
0式m変数を表す場合は、`gauss_jordan(Matrix<mint>{}, vector<mint>{}, m)` と変数数を明示できます。
実数版の引数順は `solve_linear_real(a,b,eps,variables)` です。

mod版は素数の法などの**体**を要求し、整数の割り算や合成数modの一般的な連立方程式には対応しません。
実数版は部分ピボット選択と絶対誤差 `eps`（既定 `1e-12`）を使います。桁の違いが大きい場合はスケールを揃え、必要に応じてepsを調整してください。
実数の入力値とepsは有限である必要があり、epsは正数です。

終了しない確率過程には有限の期待値が存在しない場合があります。
さらに、実数では一意解でも、modへ移すと分母が0になって表現できない場合があります。
連立方程式を立てただけで、期待値の有限性やmodでの表現可能性まで保証されるわけではありません。

## 7. 同じ遷移を非常に多く繰り返すとき：行列累乗

```cpp
cp_linear::Matrix<long double> P{{.5L,.5L},{.25L,.75L}};
auto P2 = cp_linear::matrix_power(P, 2);
auto state = cp_linear::matrix_multiply(
    cp_linear::Matrix<long double>{{1,0}}, P2)[0];
// state = {0.375,0.625}
```

ここでは `P[i][j]` がiからjへの遷移確率で、状態分布を**行ベクトル**として右から掛けます。
行列の向きが違う定義と混ぜないでください。数え上げなら `Matrix<mint>` も使えます。
0乗は単位行列です。負の指数や、形の合わない積・正方でない累乗は `invalid_argument` になります。
空の外側vectorは0×0として扱います。確率の行和や、スカラー演算のオーバーフローまでは行列関数は検査しません。

## 8. 部分集合の数え上げ

```cpp
vector<mint> f{1,2,3,4}; // 添字は2bitの集合：00,01,10,11
cp_subset::subset_zeta(f);  // {1,3,4,10}
cp_subset::subset_mobius(f); // 元の {1,2,3,4} に戻る
```

部分集合ゼータ変換は `f[S]=Σ_{T⊆S} 元のf[T]` です。上位集合版は `T⊇S` を集計します。
これらはその場で配列を書き換えます。
OR畳み込みは `(i|j)=S`、AND畳み込みは `(i&j)=S` となる組の積を合計します。
通常の「添字の和」の畳み込みとは別物です。
長さは2の冪とし、畳み込みの2配列は同じ長さにします。空配列も扱えます。
整数型を使うならオーバーフローしない範囲で、modでよければ `mint` を使ってください。

## 検証と参考

小さなコインの全列挙、法7の連立方程式の全探索、部分集合の二重ループなどと比較するテストを用意しています。
Library Checker用アダプタもありますが、オンライン提出前のためオンライン検証済みとは扱いません。

考え方の参考：[MIT・期待値の線形性](https://web.mit.edu/neboat/Public/6.042/expectationvalue1.pdf)、
[MIT・有限状態マルコフ連鎖と期待値の連立方程式](https://ocw.mit.edu/courses/6-262-discrete-stochastic-processes-spring-2011/3558b08622765d26c2b0a7d2eeeac885_MIT6_262S11_chap03.pdf)。
