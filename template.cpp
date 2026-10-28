#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
template<class T> using minpq = priority_queue<T, vector<T>, greater<T>>;
template<class T> using maxpq = priority_queue<T>;

constexpr int INF = numeric_limits<int>::max() / 2;
constexpr ll LINF = numeric_limits<ll>::max() / 4;
constexpr int inf = 2'000'000'000;
constexpr int minf = -inf;
constexpr ll MINF = -LINF;
constexpr ll mod = 998244353;
constexpr ll amod = 1'000'000'007;

#define rep(i,n) for (long long i = 0; i < (long long)(n); ++i)
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)

template<class T, class U> bool chmin(T& a, const U& b){ if (b < a) return a = b, true; return false; }
template<class T, class U> bool chmax(T& a, const U& b){ if (a < b) return a = b, true; return false; }

struct AnswerPrinter {
    explicit AnswerPrinter(const char* word){ cout << word << '\n'; }
    void operator()() const {}
};
#define Yes AnswerPrinter("Yes")
#define No AnswerPrinter("No")
inline void YN(bool ok){ if (ok) Yes; else No; }

template<class T> T ceil_div(T a, T b){
    assert(b != 0);
    T q = a / b, r = a % b;
    return q + (r != 0 && ((r > 0) == (b > 0)));
}
template<class T> T cutup(T a, T b){ return ceil_div(a,b); }
inline bool is_in_grid(int i, int j, int h, int w){ return 0 <= i && i < h && 0 <= j && j < w; }
template<class T> T manhattan_distance(T x1, T y1, T x2, T y2){ return abs(x1 - x2) + abs(y1 - y2); }
template<class T> long double euclidean_distance(T x1, T y1, T x2, T y2){ return hypot((long double)(x1 - x2), (long double)(y1 - y2)); }

template<class T> vector<T> compressed_values(vector<T> xs){ sort(all(xs)); xs.erase(unique(all(xs)), xs.end()); return xs; }
template<class T> vector<int> coordinate_compress(const vector<T>& a){
    auto xs = compressed_values(a);
    vector<int> res(a.size());
    for (int i = 0; i < (int)a.size(); ++i) res[i] = lower_bound(all(xs), a[i]) - xs.begin();
    return res;
}

using pii = pair<int,int>;
using pll = pair<long long,long long>;
using vi = vector<int>;
using vll = vector<long long>;
using vvi = vector<vector<int>>;
using vvll = vector<vector<long long>>;

#define reps(i,l,r) for (long long i = (long long)(l); i < (long long)(r); ++i)
#define rrep(i,n) for (long long i = (long long)(n) - 1; i >= 0; --i)
#define each(x,a) for (auto& x : (a))

constexpr int di4[] = {-1,0,1,0};
constexpr int dj4[] = {0,1,0,-1};
constexpr int di8[] = {-1,-1,0,1,1,1,0,-1};
constexpr int dj8[] = {0,1,1,1,0,-1,-1,-1};
constexpr int tate[] = {0,-1,0,1};
constexpr int yoko[] = {1,0,-1,0};
constexpr int etate[] = {0,-1,-1,-1,0,1,1,1};
constexpr int eyoko[] = {1,1,0,-1,-1,-1,0,1};

template<class C> int sz(const C& c){ return (int)c.size(); }

template<class T> void scan(T& x){ cin >> x; }
template<class T, class U> void scan(pair<T,U>& p){ scan(p.first); scan(p.second); }
template<class T> void scan(vector<T>& a){ for (auto& x : a) scan(x); }
template<class T, class U, class... Ts> void scan(T& x, U& y, Ts&... xs){ scan(x); scan(y, xs...); }
template<class T> void scan1(T& x){ scan(x); --x; }
template<class T, class... Ts> void scan1(T& x, Ts&... xs){ scan1(x); scan1(xs...); }

template<class T> vector<T> read_vector(int n){ vector<T> a(n); scan(a); return a; }
template<class T> vector<vector<T>> read_matrix(int h, int w){ vector a(h, vector<T>(w)); scan(a); return a; }
inline vector<string> read_grid(int h){ return read_vector<string>(h); }

template<class T, class... Ts> void print(const T& x, const Ts&... xs){ cout << x; ((cout << ' ' << xs), ...); cout << '\n'; }
template<class T> void print(const vector<T>& a, char separator = ' '){ for (int i = 0; i < sz(a); ++i) cout << a[i] << (i + 1 == sz(a) ? '\n' : separator); if (a.empty()) cout << '\n'; }

inline vector<vector<int>> read_graph(int n, int m, bool directed = false, int index_base = 1){
    vector<vector<int>> g(n); while (m--){ int u,v; scan(u,v); u -= index_base; v -= index_base; g[u].push_back(v); if (!directed) g[v].push_back(u); } return g;
}
inline vector<vector<int>> read_tree(int n, int index_base = 1){ return read_graph(n,n-1,false,index_base); }
template<class T> vector<vector<pair<int,T>>> read_weighted_graph(int n, int m, bool directed = false, int index_base = 1){
    vector<vector<pair<int,T>>> g(n); while (m--){ int u,v; T w; scan(u,v,w); u -= index_base; v -= index_base; g[u].push_back({v,w}); if (!directed) g[v].push_back({u,w}); } return g;
}
template<class T> vector<vector<pair<int,T>>> read_weighted_tree(int n, int index_base = 1){ return read_weighted_graph<T>(n,n-1,false,index_base); }

template<class T> void sort_unique(vector<T>& a){ sort(all(a)); a.erase(unique(all(a)), a.end()); }
template<class C> void st(C& a){ sort(all(a)); }
template<class C> void rst(C& a){ sort(rall(a)); }
template<class C> void rev(C& a){ reverse(all(a)); }
template<class T> void unq(vector<T>& a){ a.erase(unique(all(a)), a.end()); }
template<class T> vector<T> sorted(vector<T> a){ sort(all(a)); return a; }
template<class T> vector<T> sorted_unique(vector<T> a){ sort_unique(a); return a; }
template<class T> vector<T> reversed(vector<T> a){ reverse(all(a)); return a; }
template<class T = int> vector<T> indices(int n, T first = T{}){ vector<T> p(n); iota(all(p),first); return p; }
template<class T, class U> int lb(const vector<T>& a, const U& x){ return lower_bound(all(a),x) - a.begin(); }
template<class T, class U> int ub(const vector<T>& a, const U& x){ return upper_bound(all(a),x) - a.begin(); }
template<class T> vector<int> argsort(const vector<T>& a){ vector<int> p(a.size()); iota(all(p),0); stable_sort(all(p),[&](int i,int j){ return a[i] < a[j]; }); return p; }
inline vector<int> inverse_permutation(const vector<int>& p){ vector<int> inv(p.size()); for (int i = 0; i < sz(p); ++i) inv[p[i]] = i; return inv; }
template<class T> map<T,int> counter(const vector<T>& a){ map<T,int> res; for (auto& x : a) ++res[x]; return res; }
inline int mex(const vector<int>& a){ vector<char> seen(a.size() + 1); for (int x : a) if (0 <= x && x <= sz(a)) seen[x] = true; return find(all(seen),false) - seen.begin(); }
template<class T> T sum(const vector<T>& a){ return accumulate(all(a),T{}); }
template<class T> T min_value(const vector<T>& a){ assert(!a.empty()); return *min_element(all(a)); }
template<class T> T max_value(const vector<T>& a){ assert(!a.empty()); return *max_element(all(a)); }
inline int bit_count(unsigned long long x){ return __builtin_popcountll(x); }
template<class Graph> vector<int> degrees(const Graph& g){ vector<int> d(g.size()); for (int v = 0; v < sz(g); ++v) d[v] = sz(g[v]); return d; }

template<class T> T floor_div(T a, T b){ assert(b != 0); T q = a / b, r = a % b; return q - (r != 0 && ((r > 0) != (b > 0))); }
template<class T> T mod_floor(T a, T b){ assert(b != 0); T r = a % b; if (r != 0 && ((r > 0) != (b > 0))) r += b; return r; }

template<class T> auto make_vec(size_t n, const T& value){ return vector<T>(n, value); }
template<class... Args, enable_if_t<(sizeof...(Args) > 0),int> = 0> auto make_vec(size_t n, size_t m, Args... args){ return vector(n, make_vec(m, args...)); }

template<class Int, class F> Int first_true(Int l, Int r, F f){ while (l < r){ Int m = l + (r - l) / 2; if (f(m)) r = m; else l = m + 1; } return l; }
template<class Int, class F> Int last_true(Int l, Int r, F f){ static_assert(is_signed<Int>::value); Int x = first_true(l,r,[&](Int v){ return !f(v); }); return x - 1; }

template<class T> vector<T> prefix_sum(const vector<T>& a){
    vector<T> s(a.size() + 1);
    for (int i = 0; i < (int)a.size(); ++i) s[i + 1] = s[i] + a[i];
    return s;
}
template<class T> vector<T> prefix_1Dsum(const vector<T>& a){ return prefix_sum(a); }
template<class T> T range_sum(const vector<T>& s, int l, int r){ assert(0 <= l && l <= r && r < (int)s.size()); return s[r] - s[l]; }
template<class T> vector<vector<T>> prefix_sum_2d(const vector<vector<T>>& a){
    int h = a.size(), w = h ? a[0].size() : 0;
    vector s(h + 1, vector<T>(w + 1));
    for (int i = 0; i < h; ++i) for (int j = 0; j < w; ++j)
        s[i + 1][j + 1] = a[i][j] + s[i][j + 1] + s[i + 1][j] - s[i][j];
    return s;
}
template<class T> T range_sum_2d(const vector<vector<T>>& s, int x1, int y1, int x2, int y2){
    return s[x2][y2] - s[x1][y2] - s[x2][y1] + s[x1][y1];
}
template<class T> void rotate_grid(vector<vector<T>>& a, bool counterclockwise = false){
    if (a.empty() || a[0].empty()) return;
    int h = a.size(), w = a[0].size();
    vector b(w, vector<T>(h));
    for (int i = 0; i < h; ++i) for (int j = 0; j < w; ++j)
        if (counterclockwise) b[w - 1 - j][i] = a[i][j]; else b[j][h - 1 - i] = a[i][j];
    a = move(b);
}

template<int MOD> struct ModInt {
    static_assert(MOD > 0);
    int v;
    ModInt(long long x = 0) : v((int)(x % MOD)){ if (v < 0) v += MOD; }
    static constexpr int mod(){ return MOD; }
    int val() const { return v; }
    ModInt& operator+=(const ModInt& o){ unsigned int sum = (unsigned int)v + o.v; v = sum >= MOD ? sum - MOD : sum; return *this; }
    ModInt& operator-=(const ModInt& o){ if ((v -= o.v) < 0) v += MOD; return *this; }
    ModInt& operator*=(const ModInt& o){ v = (unsigned long long)(unsigned int)v * (unsigned int)o.v % MOD; return *this; }
    ModInt& operator/=(const ModInt& o){ return *this *= o.inv(); }
    ModInt pow(long long n) const { assert(n >= 0); ModInt a = *this, r = 1; while (n){ if (n & 1) r *= a; a *= a; n >>= 1; } return r; }
    ModInt inv() const {
        int a = v, b = MOD; long long x = 1, y = 0;
        while (b){ int q = a / b; a -= q * b; swap(a, b); x -= q * y; swap(x, y); }
        assert(a == 1);
        // Euclid's coefficient is in (-MOD, MOD), so no remainder is needed.
        ModInt res; res.v = x < 0 ? x + MOD : x; return res;
    }
    friend ModInt operator+(ModInt a, const ModInt& b){ return a += b; }
    friend ModInt operator-(ModInt a, const ModInt& b){ return a -= b; }
    friend ModInt operator*(ModInt a, const ModInt& b){ return a *= b; }
    friend ModInt operator/(ModInt a, const ModInt& b){ return a /= b; }
    friend bool operator==(const ModInt& a, const ModInt& b){ return a.v == b.v; }
    friend bool operator!=(const ModInt& a, const ModInt& b){ return !(a == b); }
    friend ostream& operator<<(ostream& os, const ModInt& x){ return os << x.v; }
    friend istream& operator>>(istream& is, ModInt& x){ long long v; is >> v; x = ModInt(v); return is; }
};
using mint = ModInt<998244353>;
using amint = ModInt<1000000007>;


template<int MOD> class MontgomeryModInt {
    static_assert(MOD > 1 && MOD < (1 << 30) && (MOD & 1), "MontgomeryModInt requires odd 1 < MOD < 2^30");
    using u32 = uint32_t;
    using u64 = uint64_t;
    u32 x = 0;
    static constexpr u32 negative_inverse(){
        u32 r = MOD;
        for (int i = 0; i < 5; ++i) r *= 2u - (u32)MOD * r;
        return 0u - r;
    }
    static constexpr u32 R2 = (0ull - (u64)MOD) % MOD;
    // x stays in [0, 2*MOD); MOD < 2^30 keeps products below MOD*2^32.
    static u32 reduce(u64 t){ return (t + (u64)(u32)((u32)t * negative_inverse()) * MOD) >> 32; }
public:
    MontgomeryModInt() = default;
    MontgomeryModInt(long long value){
        long long r = value % MOD; if (r < 0) r += MOD;
        x = reduce((u64)r * R2);
    }
    static constexpr int mod(){ return MOD; }
    static MontgomeryModInt raw(int value){
        assert(0 <= value && value < MOD);
        MontgomeryModInt r; r.x = reduce((u64)value * R2); return r;
    }
    int val() const { u32 r = reduce(x); return r >= MOD ? r - MOD : r; }
    MontgomeryModInt& operator+=(const MontgomeryModInt& o){ x += o.x; if (x >= 2u * MOD) x -= 2u * MOD; return *this; }
    MontgomeryModInt& operator-=(const MontgomeryModInt& o){ x += 2u * MOD - o.x; if (x >= 2u * MOD) x -= 2u * MOD; return *this; }
    MontgomeryModInt& operator*=(const MontgomeryModInt& o){ x = reduce((u64)x * o.x); return *this; }
    MontgomeryModInt& operator/=(const MontgomeryModInt& o){ return *this *= o.inv(); }
    MontgomeryModInt pow(long long n) const {
        assert(n >= 0); MontgomeryModInt a = *this, r = 1;
        while (n){ if (n & 1) r *= a; a *= a; n >>= 1; } return r;
    }
    MontgomeryModInt inv() const { return raw(ModInt<MOD>(val()).inv().val()); }
    friend MontgomeryModInt operator+(MontgomeryModInt a, const MontgomeryModInt& b){ return a += b; }
    friend MontgomeryModInt operator-(MontgomeryModInt a, const MontgomeryModInt& b){ return a -= b; }
    friend MontgomeryModInt operator*(MontgomeryModInt a, const MontgomeryModInt& b){ return a *= b; }
    friend MontgomeryModInt operator/(MontgomeryModInt a, const MontgomeryModInt& b){ return a /= b; }
    friend bool operator==(const MontgomeryModInt& a, const MontgomeryModInt& b){
        return (a.x >= MOD ? a.x - MOD : a.x) == (b.x >= MOD ? b.x - MOD : b.x);
    }
    friend bool operator!=(const MontgomeryModInt& a, const MontgomeryModInt& b){ return !(a == b); }
    friend ostream& operator<<(ostream& os, const MontgomeryModInt& a){ return os << a.val(); }
    friend istream& operator>>(istream& is, MontgomeryModInt& a){ long long value; if (is >> value) a = MontgomeryModInt(value); return is; }
};
using fastmint = MontgomeryModInt<998244353>;
using fastamint = MontgomeryModInt<1000000007>;

// Every entry must be invertible; zero/non-unit inputs violate T::inv()'s precondition.
// Nonempty input: one inverse and 3*(N-1) multiplications; O(N) extra space.
template<class T> vector<T> batch_inverse(const vector<T>& a){
    if (a.empty()) return {};
    vector<T> result(a.size()); result[0] = a[0];
    for (size_t i = 1; i < a.size(); ++i) result[i] = result[i - 1] * a[i];
    T inverse = result.back().inv();
    for (size_t i = a.size() - 1; i > 0; --i){
        result[i] = inverse * result[i - 1];
        inverse *= a[i];
    }
    result[0] = inverse;
    return result;
}

template<class T> struct combination {
    static constexpr int PRECOMPUTE_LIMIT = 2000000;
    vector<T> fact, ifact;
    bool table_mode = true;
    combination(long long n = 0){ reset(n); }
    void reset(long long n){
        assert(n >= 0); table_mode = n <= PRECOMPUTE_LIMIT && n < T::mod();
        int size = table_mode ? (int)n : 0;
        fact.assign(size + 1, 1); ifact.assign(size + 1, 1);
        for (int i = 1; i <= size; ++i) fact[i] = fact[i - 1] * i;
        if (size){ ifact[size] = fact[size].inv(); for (int i = size; i; --i) ifact[i - 1] = ifact[i] * i; }
    }
    bool uses_precomputation() const { return table_mode; }
    T small_C(long long n, long long r) const {
        if (r < 0 || n < r) return 0;
        r = min(r, n - r);
        if (!r) return 1;
        if (r == 1) return T(n);
        if (n < (long long)fact.size()) return fact[n] * ifact[r] * ifact[n - r];
        T numerator = 1, denominator = 1;
        for (long long i = 1; i <= r; ++i) numerator *= T(n - r + i), denominator *= T(i);
        return numerator / denominator;
    }
    T get(long long n, long long r) const {
        if (r < 0 || n < r) return 0;
        r = min(r, n - r);
        if (!r) return 1;
        if (r == 1) return T(n);
        const long long modulus = T::mod(); T res = 1;
        if (n < modulus) return small_C(n, r);
        while (r){ long long ni = n % modulus, ri = r % modulus; if (ni < ri) return 0; if (ri) res *= small_C(ni, ri); n /= modulus; r /= modulus; }
        return res;
    }
    T C(long long n, long long r) const { return get(n, r); }
    T permutation(long long n, long long r) const {
        if (r < 0 || n < r) return 0;
        if (!r) return 1;
        if (r == 1) return T(n);
        const long long modulus = T::mod(); if (r >= modulus || (n >= modulus && r > n % modulus)) return 0;
        if (n < (long long)fact.size()) return fact[n] * ifact[n - r];
        T res = 1; for (long long i = 0; i < r; ++i) res *= T(n - i); return res;
    }
    T P(long long n, long long r) const { return permutation(n, r); }
    T calu(long long n, long long r) const { return get(n, r); }
};

namespace convolution_detail {
template<class T, int PrimitiveRoot>
void ntt(vector<T>& a, bool inverse){
    constexpr int MOD = T::mod();
    int n = a.size(); assert(n && (n & (n - 1)) == 0 && (MOD - 1) % n == 0);
    for (int i = 1, j = 0; i < n; ++i){
        int bit = n >> 1; for (; j & bit; bit >>= 1) j ^= bit; j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    vector<T> roots(n / 2, 1);
    for (int len = 2; len <= n; len <<= 1){
        T root = T(PrimitiveRoot).pow((MOD - 1) / len); if (inverse) root = root.inv();
        for (int j = 1; j < len / 2; ++j) roots[j] = roots[j - 1] * root;
        for (int i = 0; i < n; i += len){ for (int j = 0; j < len / 2; ++j){ auto u = a[i+j], v = a[i+j+len/2] * roots[j]; a[i+j] = u + v; a[i+j+len/2] = u - v; } }
    }
    if (inverse){ T inv_n = T(n).inv(); for (auto& x : a) x *= inv_n; }
}

template<class T, int PrimitiveRoot>
vector<T> convolution(vector<T> a, vector<T> b){
    constexpr int MOD = T::mod();
    if (a.empty() || b.empty()) return {};
    if (min(a.size(), b.size()) <= 32){ vector<T> c(a.size() + b.size() - 1); for (int i = 0; i < (int)a.size(); ++i) for (int j = 0; j < (int)b.size(); ++j) c[i+j] += a[i] * b[j]; return c; }
    int need = a.size() + b.size() - 1, n = 1; while (n < need) n <<= 1; assert((MOD - 1) % n == 0);
    a.resize(n); b.resize(n); ntt<T,PrimitiveRoot>(a, false); ntt<T,PrimitiveRoot>(b, false); for (int i = 0; i < n; ++i) a[i] *= b[i]; ntt<T,PrimitiveRoot>(a, true); a.resize(need); return a;
}

template<class T, int PrimitiveRoot>
vector<T> square(vector<T> a){
    constexpr int MOD = T::mod();
    if (a.empty()) return {};
    if (a.size() <= 32){
        vector<T> c(a.size() * 2 - 1);
        for (int i = 0; i < (int)a.size(); ++i){
            c[2 * i] += a[i] * a[i]; T twice = a[i] + a[i];
            for (int j = i + 1; j < (int)a.size(); ++j) c[i + j] += twice * a[j];
        }
        return c;
    }
    unsigned int order = MOD - 1;
    size_t max_transform = order & (0u - order);
    if (a.size() > (max_transform + 1) / 2) throw length_error("convolution_square exceeds the modulus NTT length");
    int need = (int)a.size() * 2 - 1, n = 1;
    while (n < need) n <<= 1;
    assert((MOD - 1) % n == 0);
    a.resize(n); ntt<T,PrimitiveRoot>(a, false);
    for (auto& x : a) x *= x;
    ntt<T,PrimitiveRoot>(a, true); a.resize(need); return a;
}
} // namespace convolution_detail

template<int MOD, int PrimitiveRoot = 3>
void ntt(vector<ModInt<MOD>>& a, bool inverse){ convolution_detail::ntt<ModInt<MOD>,PrimitiveRoot>(a, inverse); }
template<int MOD, int PrimitiveRoot = 3>
void ntt(vector<MontgomeryModInt<MOD>>& a, bool inverse){ convolution_detail::ntt<MontgomeryModInt<MOD>,PrimitiveRoot>(a, inverse); }

template<int MOD, int PrimitiveRoot = 3>
vector<MontgomeryModInt<MOD>> convolution(vector<MontgomeryModInt<MOD>> a, vector<MontgomeryModInt<MOD>> b){
    return convolution_detail::convolution<MontgomeryModInt<MOD>,PrimitiveRoot>(move(a), move(b));
}
template<int MOD, int PrimitiveRoot = 3>
vector<ModInt<MOD>> convolution(vector<ModInt<MOD>> a, vector<ModInt<MOD>> b){
    if constexpr (MOD > 1 && MOD < (1 << 30) && (MOD & 1)){
        if (min(a.size(), b.size()) > 32){
            vector<MontgomeryModInt<MOD>> x(a.size()), y(b.size());
            for (int i = 0; i < (int)a.size(); ++i) x[i] = MontgomeryModInt<MOD>::raw(a[i].val());
            for (int i = 0; i < (int)b.size(); ++i) y[i] = MontgomeryModInt<MOD>::raw(b[i].val());
            auto z = convolution<MOD,PrimitiveRoot>(move(x), move(y));
            a.resize(z.size()); for (int i = 0; i < (int)z.size(); ++i) a[i] = z[i].val();
            return a;
        }
    }
    return convolution_detail::convolution<ModInt<MOD>,PrimitiveRoot>(move(a), move(b));
}

// Reuses the forward transform: two NTTs instead of three for a*a.
template<int MOD, int PrimitiveRoot = 3>
vector<MontgomeryModInt<MOD>> convolution_square(vector<MontgomeryModInt<MOD>> a){
    return convolution_detail::square<MontgomeryModInt<MOD>,PrimitiveRoot>(move(a));
}
template<int MOD, int PrimitiveRoot = 3>
vector<ModInt<MOD>> convolution_square(vector<ModInt<MOD>> a){
    if constexpr (MOD > 1 && MOD < (1 << 30) && (MOD & 1)){
        if (a.size() > 32){
            vector<MontgomeryModInt<MOD>> x(a.size());
            for (int i = 0; i < (int)a.size(); ++i) x[i] = MontgomeryModInt<MOD>::raw(a[i].val());
            auto z = convolution_square<MOD,PrimitiveRoot>(move(x));
            a.resize(z.size()); for (int i = 0; i < (int)z.size(); ++i) a[i] = z[i].val();
            return a;
        }
    }
    return convolution_detail::square<ModInt<MOD>,PrimitiveRoot>(move(a));
}


inline long long modpow(long long a, long long n, long long modulus){ long long r = 1 % modulus; for (a %= modulus; n; n >>= 1, a = (long long)((__int128)a * a % modulus)) if (n & 1) r = (long long)((__int128)r * a % modulus); return r; }
inline long long safe_mod_multiply(long long a, long long b, long long modulus){ return (long long)((__int128)a * b % modulus); }
inline long long extgcd(long long a, long long b, long long& x, long long& y){ if (!b){ x = a >= 0 ? 1 : -1; y = 0; return abs(a); } long long g = extgcd(b, a % b, y, x); y -= a / b * x; return g; }
inline optional<long long> modular_inverse(long long a, long long modulus){ long long x, y, g = extgcd(a, modulus, x, y); if (g != 1) return nullopt; return (x % modulus + modulus) % modulus; }
inline pair<long long, long long> crt(const vector<long long>& r, const vector<long long>& m){
    assert(r.size() == m.size()); long long r0 = 0, m0 = 1;
    for (int i = 0; i < (int)r.size(); ++i){
        assert(m[i] > 0); long long r1 = (r[i] % m[i] + m[i]) % m[i], m1 = m[i];
        long long x, y, g = extgcd(m0, m1, x, y); if ((r1 - r0) % g) return {0, 0};
        long long u = m1 / g, t = safe_mod_multiply((r1 - r0) / g, x, u);
        r0 += m0 * t; m0 *= u; r0 = (r0 % m0 + m0) % m0;
    }
    return {r0, m0};
}
inline vector<int> eratosthenes(int n){ vector<int> prime(n + 1, true); if (n >= 0) prime[0] = false; if (n >= 1) prime[1] = false; for (long long i = 2; i * i <= n; ++i) if (prime[i]) for (long long j = i * i; j <= n; j += i) prime[j] = false; return prime; }
inline vector<int> primes_up_to(int n){ auto p = eratosthenes(n); vector<int> res; for (int i = 2; i <= n; ++i) if (p[i]) res.push_back(i); return res; }
inline bool is_prime(long long n){ if (n < 2) return false; for (long long p = 2; p * p <= n; ++p) if (n % p == 0) return false; return true; }
inline map<long long, int> prime_factorize(long long n){ map<long long, int> f; for (long long p = 2; p * p <= n; ++p) while (n % p == 0) ++f[p], n /= p; if (n > 1) ++f[n]; return f; }
inline vector<long long> divisors(long long n){ vector<long long> d; for (long long i = 1; i * i <= n; ++i) if (n % i == 0){ d.push_back(i); if (i * i != n) d.push_back(n / i); } sort(all(d)); return d; }
inline long long integer_sqrt(long long n){ assert(n >= 0); long long x = sqrt((long double)n); while ((__int128)(x + 1) * (x + 1) <= n) ++x; while ((__int128)x * x > n) --x; return x; }

struct UnionFind {
    vector<int> p;
    UnionFind(int n = 0){ reset(n); }
    void reset(int n){ p.assign(n, -1); }
    int leader(int a){ assert(0 <= a && a < (int)p.size()); while (p[a] >= 0){ if (p[p[a]] >= 0) p[a] = p[p[a]]; a = p[a]; } return a; }
    bool merge(int a, int b){ a = leader(a); b = leader(b); if (a == b) return false; if (-p[a] < -p[b]) swap(a, b); p[a] += p[b]; p[b] = a; return true; }
    bool marge(int a, int b){ return merge(a, b); }
    bool same(int a, int b){ return leader(a) == leader(b); }
    int size(int a){ return -p[leader(a)]; }
    vector<vector<int>> groups(){ vector<vector<int>> g(p.size()); for (int i = 0; i < (int)p.size(); ++i) g[leader(i)].push_back(i); g.erase(remove_if(all(g), [](auto& v){ return v.empty(); }), g.end()); return g; }
};
template<class T = int> using unionfind = UnionFind;

template<class T> struct WeightedUnionFind {
    vector<int> p; vector<T> diff;
    WeightedUnionFind(int n = 0){ reset(n); }
    void reset(int n){ p.assign(n, -1); diff.assign(n, T{}); }
    int leader(int x){ if (p[x] < 0) return x; int q = p[x]; p[x] = leader(q); diff[x] += diff[q]; return p[x]; }
    T potential(int x){ leader(x); return diff[x]; }
    bool same(int x, int y){ return leader(x) == leader(y); }
    T difference(int x, int y){ assert(same(x, y)); return potential(y) - potential(x); }
    bool merge(int x, int y, T w){ w += potential(x) - potential(y); x = leader(x); y = leader(y); if (x == y) return w == T{}; if (-p[x] < -p[y]) swap(x, y), w = -w; p[x] += p[y]; p[y] = x; diff[y] = w; return true; }
    int size(int x){ return -p[leader(x)]; }
};


struct RollbackUnionFind {
    vector<int> p; vector<pair<int,int>> history; int components = 0;
    RollbackUnionFind(int n = 0){ reset(n); }
    void reset(int n){ p.assign(n, -1); history.clear(); components = n; }
    int leader(int v) const { while (p[v] >= 0) v = p[v]; return v; }
    bool same(int u, int v) const { return leader(u) == leader(v); }
    int size(int v) const { return -p[leader(v)]; }
    bool merge(int u, int v){
        u = leader(u); v = leader(v); if (u == v){ history.push_back({-1,-1}); return false; }
        if (-p[u] < -p[v]) swap(u, v);
        history.push_back({u,p[u]}); history.push_back({v,p[v]}); p[u] += p[v]; p[v] = u; --components; return true;
    }
    int snapshot() const { return history.size(); }
    void undo(){ assert(!history.empty()); if (history.back().first < 0){ history.pop_back(); return; } auto [v,pv] = history.back(); history.pop_back(); auto [u,pu] = history.back(); history.pop_back(); p[u] = pu; p[v] = pv; ++components; }
    void rollback(int state){ assert(0 <= state && state <= (int)history.size()); while ((int)history.size() > state) undo(); }
};

template<class UInt = unsigned long long, int B = numeric_limits<UInt>::digits> struct BinaryTrie {
    static_assert(is_unsigned<UInt>::value, "BinaryTrie requires an unsigned integer type");
    struct Node { int next[2] = {-1,-1}; int count = 0; };
    vector<Node> nodes{Node{}};
    int size() const { return nodes[0].count; }
    int count(UInt x) const { int v = 0; for (int b = B - 1; b >= 0; --b){ v = nodes[v].next[x >> b & 1]; if (v < 0) return 0; } return nodes[v].count; }
    void insert(UInt x, int delta = 1){
        assert(delta > 0); int v = 0; nodes[v].count += delta;
        for (int b = B - 1; b >= 0; --b){ int c = x >> b & 1; if (nodes[v].next[c] < 0) nodes[v].next[c] = nodes.size(), nodes.push_back(Node{}); v = nodes[v].next[c]; nodes[v].count += delta; }
    }
    void erase(UInt x, int delta = 1){ assert(count(x) >= delta); int v = 0; nodes[v].count -= delta; for (int b = B - 1; b >= 0; --b){ v = nodes[v].next[x >> b & 1]; nodes[v].count -= delta; } }
    UInt kth_element(int k, UInt xor_mask = 0) const {
        assert(0 <= k && k < size()); int v = 0; UInt value = 0;
        for (int b = B - 1; b >= 0; --b){ int preferred = xor_mask >> b & 1, left = nodes[v].next[preferred], cnt = left < 0 ? 0 : nodes[left].count; int c = preferred; if (k >= cnt) k -= cnt, c ^= 1; v = nodes[v].next[c]; value |= UInt(c) << b; }
        return value;
    }
    UInt min_xor(UInt x) const { assert(size()); return kth_element(0, x) ^ x; }
    UInt max_xor(UInt x) const { assert(size()); return kth_element(size() - 1, x) ^ x; }
    int count_less(UInt x, UInt xor_mask = 0) const {
        int v = 0, res = 0;
        for (int b = B - 1; b >= 0 && v >= 0; --b){ int mb = xor_mask >> b & 1, xb = x >> b & 1; if (xb){ int z = nodes[v].next[mb]; if (z >= 0) res += nodes[z].count; } v = nodes[v].next[mb ^ xb]; }
        return res;
    }
};


template<class T> struct FenwickTree {
    int n = 0; vector<T> bit;
    FenwickTree(int m = 0){ reset(m); }
    FenwickTree(const vector<T>& a){ n = a.size(); bit.assign(n + 1, T{}); for (int i = 0; i < n; ++i) bit[i + 1] += a[i]; for (int i = 1; i <= n; ++i) if (i + (i & -i) <= n) bit[i + (i & -i)] += bit[i]; }
    void reset(int m){ n = m; bit.assign(n + 1, T{}); }
    void add(int i, T x){ assert(0 <= i && i < n); for (++i; i <= n; i += i & -i) bit[i] += x; }
    T sum(int r) const { assert(0 <= r && r <= n); T s{}; for (; r; r -= r & -r) s += bit[r]; return s; }
    T sum(int l, int r) const { return sum(r) - sum(l); }
    T get(int i) const { return sum(i, i + 1); }
    int lower_bound(T x) const { if (x <= T{}) return 0; int k = 1, i = 0; T s{}; while ((k << 1) <= n) k <<= 1; for (; k; k >>= 1) if (i + k <= n && s + bit[i + k] < x) s += bit[i += k]; return min(i, n); }
};

template<bool Minimum = true> struct LiChaoTree {
    struct Line { long long a = 0, b = 0; __int128 eval(long long x) const { return (__int128)a * x + b; } };
    vector<long long> xs; vector<Line> seg; vector<char> used;
    LiChaoTree(vector<long long> x) : xs(move(x)) { sort(all(xs)); xs.erase(unique(all(xs)), xs.end()); seg.resize(xs.size() * 4 + 4); used.assign(seg.size(), false); }
    bool better(__int128 a, __int128 b) const { return Minimum ? a < b : a > b; }
    void add_line(Line line){ assert(!xs.empty()); add_line(line, 1, 0, xs.size()); }
    void add_segment(Line line, long long xl, long long xr){ int l = lower_bound(all(xs), xl) - xs.begin(), r = lower_bound(all(xs), xr) - xs.begin(); add_segment(line, l, r, 1, 0, xs.size()); }
    long long query(long long x) const {
        int p = lower_bound(all(xs), x) - xs.begin(); assert(p < (int)xs.size() && xs[p] == x); __int128 ans = Minimum ? (__int128)LLONG_MAX : (__int128)LLONG_MIN;
        for (int k = 1, l = 0, r = xs.size();;){ if (used[k] && better(seg[k].eval(x), ans)) ans = seg[k].eval(x); if (r - l == 1) break; int m = (l + r) / 2; if (p < m) k *= 2, r = m; else k = k * 2 + 1, l = m; }
        return (long long)ans;
    }
private:
    void add_line(Line line, int k, int l, int r){
        if (!used[k]){ seg[k] = line; used[k] = true; return; }
        int m = (l + r) / 2; bool left = better(line.eval(xs[l]), seg[k].eval(xs[l])), mid = better(line.eval(xs[m]), seg[k].eval(xs[m]));
        if (mid) swap(line, seg[k]);
        if (r - l == 1) return;
        if (left != mid) add_line(line, k * 2, l, m); else add_line(line, k * 2 + 1, m, r);
    }
    void add_segment(Line line, int ql, int qr, int k, int l, int r){ if (qr <= l || r <= ql) return; if (ql <= l && r <= qr){ add_line(line, k, l, r); return; } int m = (l + r) / 2; add_segment(line, ql, qr, k * 2, l, m); add_segment(line, ql, qr, k * 2 + 1, m, r); }
};

template<class S, S (*op)(S, S), S (*e)()> struct segtree {
    int n = 0, size = 1, log = 0; vector<S> d;
    segtree(int m = 0) : segtree(vector<S>(m, e())) {}
    segtree(const vector<S>& v){ n = v.size(); while (size < n) size <<= 1, ++log; d.assign(2 * size, e()); copy(v.begin(), v.end(), d.begin() + size); for (int i = size - 1; i; --i) update(i); }
    void update(int k){ d[k] = op(d[2 * k], d[2 * k + 1]); }
    void set(int p, S x){ assert(0 <= p && p < n); d[p += size] = x; while (p >>= 1) update(p); }
    S get(int p) const { assert(0 <= p && p < n); return d[p + size]; }
    S prod(int l, int r) const { assert(0 <= l && l <= r && r <= n); S a = e(), b = e(); for (l += size, r += size; l < r; l >>= 1, r >>= 1){ if (l & 1) a = op(a, d[l++]); if (r & 1) b = op(d[--r], b); } return op(a, b); }
    S all_prod() const { return d[1]; }
    template<class F> int max_right(int l, F f) const {
        assert(0 <= l && l <= n && f(e())); if (l == n) return n; l += size; S sm = e();
        do { while (!(l & 1)) l >>= 1; if (!f(op(sm, d[l]))){ while (l < size){ l <<= 1; if (f(op(sm, d[l]))) sm = op(sm, d[l++]); } return l - size; } sm = op(sm, d[l++]); } while ((l & -l) != l);
        return n;
    }
    template<class F> int min_left(int r, F f) const {
        assert(0 <= r && r <= n && f(e())); if (!r) return 0; r += size; S sm = e();
        do { --r; while (r > 1 && (r & 1)) r >>= 1; if (!f(op(d[r], sm))){ while (r < size){ r = 2 * r + 1; if (f(op(d[r], sm))) sm = op(d[r--], sm); } return r + 1 - size; } sm = op(d[r], sm); } while ((r & -r) != r);
        return 0;
    }
};

template<class S, S (*op)(S,S), S (*e)(), class F, S (*mapping)(F,S), F (*composition)(F,F), F (*id)()>
struct lazy_segtree {
    int n = 0, size = 1, log = 0; vector<S> d; vector<F> lz;
    lazy_segtree(int m = 0) : lazy_segtree(vector<S>(m, e())) {}
    lazy_segtree(const vector<S>& v){ n = v.size(); while (size < n) size <<= 1, ++log; d.assign(2 * size, e()); lz.assign(size, id()); copy(v.begin(), v.end(), d.begin() + size); for (int i = size - 1; i; --i) update(i); }
    void update(int k){ d[k] = op(d[2*k], d[2*k+1]); }
    void all_apply(int k, F f){ d[k] = mapping(f, d[k]); if (k < size) lz[k] = composition(f, lz[k]); }
    void push(int k){ all_apply(2*k, lz[k]); all_apply(2*k+1, lz[k]); lz[k] = id(); }
    void set(int p, S x){ assert(0 <= p && p < n); p += size; for (int i = log; i; --i) push(p >> i); d[p] = x; for (int i = 1; i <= log; ++i) update(p >> i); }
    S get(int p){ assert(0 <= p && p < n); p += size; for (int i = log; i; --i) push(p >> i); return d[p]; }
    S prod(int l, int r){
        assert(0 <= l && l <= r && r <= n); if (l == r) return e(); l += size; r += size;
        for (int i = log; i; --i){ if ((l >> i) << i != l) push(l >> i); if ((r >> i) << i != r) push((r - 1) >> i); }
        S a = e(), b = e(); for (; l < r; l >>= 1, r >>= 1){ if (l & 1) a = op(a, d[l++]); if (r & 1) b = op(d[--r], b); } return op(a, b);
    }
    S all_prod() const { return d[1]; }
    void apply(int p, F f){ assert(0 <= p && p < n); p += size; for (int i = log; i; --i) push(p >> i); d[p] = mapping(f, d[p]); for (int i = 1; i <= log; ++i) update(p >> i); }
    void apply(int l, int r, F f){
        assert(0 <= l && l <= r && r <= n); if (l == r) return; l += size; r += size;
        for (int i = log; i; --i){ if ((l >> i) << i != l) push(l >> i); if ((r >> i) << i != r) push((r - 1) >> i); }
        int l2 = l, r2 = r; for (; l < r; l >>= 1, r >>= 1){ if (l & 1) all_apply(l++, f); if (r & 1) all_apply(--r, f); }
        l = l2; r = r2; for (int i = 1; i <= log; ++i){ if ((l >> i) << i != l) update(l >> i); if ((r >> i) << i != r) update((r - 1) >> i); }
    }
    template<class G> int max_right(int l, G g){
        assert(0 <= l && l <= n && g(e())); if (l == n) return n; l += size; for (int i = log; i; --i) push(l >> i); S sm = e();
        do { while (!(l & 1)) l >>= 1; if (!g(op(sm, d[l]))){ while (l < size){ push(l); l <<= 1; if (g(op(sm, d[l]))) sm = op(sm, d[l++]); } return l - size; } sm = op(sm, d[l++]); } while ((l & -l) != l); return n;
    }
    template<class G> int min_left(int r, G g){
        assert(0 <= r && r <= n && g(e())); if (!r) return 0; r += size; for (int i = log; i; --i) push((r - 1) >> i); S sm = e();
        do { --r; while (r > 1 && (r & 1)) r >>= 1; if (!g(op(d[r], sm))){ while (r < size){ push(r); r = 2*r+1; if (g(op(d[r], sm))) sm = op(d[r--], sm); } return r + 1 - size; } sm = op(d[r], sm); } while ((r & -r) != r); return 0;
    }
};

template<class T, T (*op)(T,T)> struct SparseTable {
    vector<int> lg; vector<vector<T>> st;
    SparseTable() = default;
    SparseTable(const vector<T>& a){ build(a); }
    void build(const vector<T>& a){
        int n = a.size(); lg.assign(n + 1, 0); for (int i = 2; i <= n; ++i) lg[i] = lg[i / 2] + 1;
        st.assign(n ? lg[n] + 1 : 0, vector<T>(n)); if (!n) return; st[0] = a;
        for (int k = 1; k < (int)st.size(); ++k) for (int i = 0; i + (1 << k) <= n; ++i) st[k][i] = op(st[k-1][i], st[k-1][i + (1 << (k-1))]);
    }
    T prod(int l, int r) const { assert(0 <= l && l < r && !st.empty() && r <= (int)st[0].size()); int k = lg[r-l]; return op(st[k][l], st[k][r - (1 << k)]); }
    T query(int l, int r) const { return prod(l, r); }
};


template<class UInt = unsigned long long, int B = numeric_limits<UInt>::digits>
struct WaveletMatrix {
    static_assert(is_unsigned<UInt>::value, "WaveletMatrix requires an unsigned integer type");
    int n = 0; vector<int> mid; vector<vector<int>> ones;
    WaveletMatrix() = default; WaveletMatrix(const vector<UInt>& a){ build(a); }
    void build(vector<UInt> a){
        if constexpr (B < numeric_limits<UInt>::digits) for (UInt x : a) assert((x >> B) == 0);
        n = a.size(); mid.assign(B, 0); ones.assign(B, vector<int>(n + 1));
        vector<UInt> zero, one; zero.reserve(n); one.reserve(n);
        for (int level = 0; level < B; ++level){
            int bit = B - 1 - level; zero.clear(); one.clear();
            for (int i = 0; i < n; ++i){ int b = a[i] >> bit & 1; ones[level][i+1] = ones[level][i] + b; (b ? one : zero).push_back(a[i]); }
            mid[level] = zero.size(); copy(all(zero), a.begin()); copy(all(one), a.begin() + mid[level]);
        }
    }
    UInt kth_smallest(int l, int r, int k) const {
        assert(0 <= l && l <= r && r <= n && 0 <= k && k < r - l); UInt res = 0;
        for (int level = 0; level < B; ++level){ int ol = ones[level][l], orr = ones[level][r], zeros = (r-l) - (orr-ol); if (k < zeros) l -= ol, r -= orr; else res |= UInt(1) << (B-1-level), k -= zeros, l = mid[level]+ol, r = mid[level]+orr; }
        return res;
    }
    int rank(UInt x, int l, int r) const {
        assert(0 <= l && l <= r && r <= n);
        if constexpr (B < numeric_limits<UInt>::digits) if (x >> B) return 0;
        for (int level = 0; level < B; ++level){ int ol = ones[level][l], orr = ones[level][r]; if (x >> (B-1-level) & 1) l = mid[level]+ol, r = mid[level]+orr; else l -= ol, r -= orr; }
        return r - l;
    }
    int count_less(int l, int r, UInt x) const {
        assert(0 <= l && l <= r && r <= n); int res = 0;
        if constexpr (B < numeric_limits<UInt>::digits) if (x >> B) return r - l;
        for (int level = 0; level < B; ++level){ int ol = ones[level][l], orr = ones[level][r], zeros = (r-l) - (orr-ol); if (x >> (B-1-level) & 1) res += zeros, l = mid[level]+ol, r = mid[level]+orr; else l -= ol, r -= orr; }
        return res;
    }
    int range_freq(int l, int r, UInt lower, UInt upper) const { return count_less(l,r,upper) - count_less(l,r,lower); }
    optional<UInt> prev_value(int l, int r, UInt upper) const { int k = count_less(l,r,upper); if (!k) return nullopt; return kth_smallest(l,r,k-1); }
    optional<UInt> next_value(int l, int r, UInt lower) const { int k = count_less(l,r,lower); if (k == r-l) return nullopt; return kth_smallest(l,r,k); }
};

inline vector<int> bfs(const vector<vector<int>>& g, const vector<int>& starts){
    vector<int> d(g.size(), -1); queue<int> q; for (int s : starts) if (d[s] < 0) d[s] = 0, q.push(s);
    while (!q.empty()){ int v = q.front(); q.pop(); for (int to : g[v]) if (d[to] < 0) d[to] = d[v] + 1, q.push(to); }
    return d;
}
inline vector<int> bfs(const vector<vector<int>>& g, int s){ return bfs(g, vector<int>{s}); }

template<class T> vector<T> bfs01(const vector<vector<pair<int,T>>>& g, int s){
    const T infinity = numeric_limits<T>::max() / 4; vector<T> d(g.size(), infinity); deque<int> q; d[s] = 0; q.push_back(s);
    while (!q.empty()){ int v = q.front(); q.pop_front(); for (auto [to,w] : g[v]){ assert(w == 0 || w == 1); if (d[to] > d[v] + w){ d[to] = d[v] + w; w ? q.push_back(to) : q.push_front(to); } } }
    return d;
}

template<class T = long long> struct Dijkstra {
    int n = 0, start = -1; vector<vector<pair<int,T>>> g; vector<T> dist; vector<int> prev;
    Dijkstra(int m = 0){ reset(m); }
    void reset(int m){ n = m; g.assign(n, {}); dist.clear(); prev.clear(); }
    void make_directedgraph(int u, int v, T w){ g[u].push_back({v,w}); }
    void make_indirectedgraph(int u, int v, T w){ make_directedgraph(u,v,w); make_directedgraph(v,u,w); }
    const vector<T>& do_dijkstra(int s){
        start = s; T infinity = numeric_limits<T>::max() / 4; dist.assign(n, infinity); prev.assign(n, -1); minpq<pair<T,int>> q; dist[s] = 0; q.push({0,s});
        while (!q.empty()){ auto [d,v] = q.top(); q.pop(); if (d != dist[v]) continue; for (auto [to,w] : g[v]) if (chmin(dist[to], d+w)) prev[to] = v, q.push({dist[to],to}); }
        return dist;
    }
    T output(int v) const { return dist[v]; }
    vector<int> path(int v) const { if (dist.empty() || dist[v] == numeric_limits<T>::max()/4) return {}; vector<int> p; for (; v != -1; v = prev[v]) p.push_back(v); reverse(all(p)); return p; }
};

template<class T> struct BellmanFordResult { vector<T> dist; vector<char> negative; bool has_negative_cycle; };
template<class T> BellmanFordResult<T> bellman_ford(int n, const vector<tuple<int,int,T>>& edges, int s){
    T infinity = numeric_limits<T>::max()/4; vector<T> d(n,infinity); vector<char> neg(n); d[s]=0;
    for (int i=0;i<n;++i) for (auto [u,v,w]:edges) if (d[u]!=infinity && d[v]>max(-infinity,d[u]+w)){ d[v]=max(-infinity,d[u]+w); if(i==n-1) neg[v]=1; }
    for(int i=0;i<n;++i) for(auto [u,v,w]:edges) if(neg[u]) neg[v]=1;
    return {d,neg,any_of(all(neg),[](char x){return x;})};
}

template<class T> void floyd_warshall(vector<vector<T>>& d){
    int n=d.size(); T infinity=numeric_limits<T>::max()/4;
    for(int k=0;k<n;++k)for(int i=0;i<n;++i)if(d[i][k]!=infinity)for(int j=0;j<n;++j)if(d[k][j]!=infinity)chmin(d[i][j],d[i][k]+d[k][j]);
}

inline optional<vector<int>> topological_sort(const vector<vector<int>>& g){
    int n=g.size(); vector<int> deg(n),res; for(auto& es:g)for(int v:es)++deg[v]; queue<int>q; for(int i=0;i<n;++i)if(!deg[i])q.push(i);
    while(!q.empty()){int v=q.front();q.pop();res.push_back(v);for(int to:g[v])if(!--deg[to])q.push(to);} if((int)res.size()!=n)return nullopt; return res;
}

struct SCC {
    int n=0,scc_count=0; vector<vector<int>> g,rg,groups,dag; vector<int> comp,indeg,outdeg;
    SCC(int m=0){reset(m);} void reset(int m){n=m;g.assign(n,{});rg.assign(n,{});}
    void add_edge(int u,int v){g[u].push_back(v);rg[v].push_back(u);}
    int do_scc(){
        vector<char> used(n); vector<int> order;
        for(int s=0;s<n;++s)if(!used[s]){ vector<pair<int,int>> st{{s,0}};used[s]=1; while(!st.empty()){auto&[v,i]=st.back();if(i<(int)g[v].size()){int to=g[v][i++];if(!used[to])used[to]=1,st.push_back({to,0});}else order.push_back(v),st.pop_back();}}
        comp.assign(n,-1);scc_count=0;reverse(all(order)); for(int s:order)if(comp[s]<0){stack<int>st;st.push(s);comp[s]=scc_count;while(!st.empty()){int v=st.top();st.pop();for(int to:rg[v])if(comp[to]<0)comp[to]=scc_count,st.push(to);}++scc_count;}
        groups.assign(scc_count,{});for(int v=0;v<n;++v)groups[comp[v]].push_back(v);dag.assign(scc_count,{});indeg.assign(scc_count,0);outdeg.assign(scc_count,0);
        vector<pair<int,int>> es;for(int v=0;v<n;++v)for(int to:g[v])if(comp[v]!=comp[to])es.push_back({comp[v],comp[to]});sort(all(es));es.erase(unique(all(es)),es.end());for(auto[a,b]:es)dag[a].push_back(b),++outdeg[a],++indeg[b];
        return scc_count;
    }
};

struct TwoSAT {
    int n; SCC scc; vector<bool> ans;
    TwoSAT(int m=0):n(m),scc(2*m),ans(m){}
    int id(int i,bool f)const{return 2*i+(f?0:1);}
    void add_clause(int i,bool f,int j,bool g){scc.add_edge(id(i,!f),id(j,g));scc.add_edge(id(j,!g),id(i,f));}
    bool satisfiable(){scc.do_scc();for(int i=0;i<n;++i){if(scc.comp[id(i,0)]==scc.comp[id(i,1)])return false;ans[i]=scc.comp[id(i,1)]>scc.comp[id(i,0)];}return true;}
    vector<bool> answer()const{return ans;}
};

template<class T> struct KruskalResult{T cost{};vector<tuple<int,int,T>> edges;bool connected=false;};
template<class T> KruskalResult<T> kruskal(int n,vector<tuple<int,int,T>> edges){
    sort(all(edges),[](auto&a,auto&b){return get<2>(a)<get<2>(b);});UnionFind uf(n);KruskalResult<T>r;
    for(auto[u,v,w]:edges)if(uf.merge(u,v)){r.cost+=w;r.edges.push_back({u,v,w});}
    r.connected=n==0||(int)r.edges.size()==n-1;return r;
}

template<class T> struct Dinic {
    struct Edge{int to,rev;T cap;}; int n;vector<vector<Edge>>g;vector<int>level,it;
    Dinic(int m=0):n(m),g(m),level(m),it(m){}
    void add_edge(int u,int v,T cap){int a=g[u].size(),b=g[v].size();g[u].push_back({v,b,cap});g[v].push_back({u,a,T{}});}
    bool bfs_level(int s,int t){fill(all(level),-1);queue<int>q;q.push(s);level[s]=0;while(!q.empty()){int v=q.front();q.pop();for(auto&e:g[v])if(e.cap>0&&level[e.to]<0)level[e.to]=level[v]+1,q.push(e.to);}return level[t]>=0;}
    T dfs(int v,int t,T f){if(v==t)return f;for(int&i=it[v];i<(int)g[v].size();++i){Edge&e=g[v][i];if(e.cap>0&&level[v]<level[e.to]){T d=dfs(e.to,t,min(f,e.cap));if(d>0){e.cap-=d;g[e.to][e.rev].cap+=d;return d;}}}return T{};}
    T flow(int s,int t,T limit=numeric_limits<T>::max()){T res{};while(res<limit&&bfs_level(s,t)){fill(all(it),0);while(T f=dfs(s,t,limit-res))res+=f;}return res;}
};

template<class Cap, class Cost> struct MinCostFlow {
    struct Edge { int to, rev; Cap cap; Cost cost; };
    int n; vector<vector<Edge>> g;
    MinCostFlow(int m = 0) : n(m), g(m) {}
    void add_edge(int u, int v, Cap cap, Cost cost){ int a = g[u].size(), b = g[v].size(); g[u].push_back({v,b,cap,cost}); g[v].push_back({u,a,Cap{},-cost}); }
    pair<Cap,Cost> flow(int s, int t, Cap limit = numeric_limits<Cap>::max()){
        const Cost infinity = numeric_limits<Cost>::max() / 4; vector<Cost> h(n, infinity); h[s] = 0;
        for (int it = 0; it < n; ++it){ bool changed = false; for (int v = 0; v < n; ++v) if (h[v] != infinity) for (auto& e : g[v]) if (e.cap > 0 && h[e.to] > h[v] + e.cost) h[e.to] = h[v] + e.cost, changed = true; if (!changed) break; }
        for (Cost& x : h) if (x == infinity) x = 0;
        Cap sent{}; Cost total{}; vector<Cost> dist(n); vector<int> pv(n), pe(n);
        while (sent < limit){
            fill(all(dist), infinity); dist[s] = 0; minpq<pair<Cost,int>> q; q.push({0,s});
            while (!q.empty()){
                auto [d,v] = q.top(); q.pop(); if (d != dist[v]) continue;
                for (int i = 0; i < (int)g[v].size(); ++i){ auto& e = g[v][i]; Cost nd = d + e.cost + h[v] - h[e.to]; if (e.cap > 0 && chmin(dist[e.to], nd)) pv[e.to] = v, pe[e.to] = i, q.push({nd,e.to}); }
            }
            if (dist[t] == infinity) break;
            for (int v = 0; v < n; ++v) if (dist[v] != infinity) h[v] += dist[v];
            Cap add = limit - sent; for (int v = t; v != s; v = pv[v]) chmin(add, g[pv[v]][pe[v]].cap);
            sent += add; total += (Cost)add * h[t];
            for (int v = t; v != s; v = pv[v]){ Edge& e = g[pv[v]][pe[v]]; e.cap -= add; g[v][e.rev].cap += add; }
        }
        return {sent,total};
    }
};

struct LowLink {
    int n, timer = 0; vector<pair<int,int>> edges; vector<vector<pair<int,int>>> g;
    vector<int> ord, low, parent; vector<char> articulation; vector<int> bridges;
    LowLink(int m = 0) : n(m), g(m) {}
    int add_edge(int u, int v){ int id = edges.size(); edges.push_back({u,v}); g[u].push_back({v,id}); g[v].push_back({u,id}); return id; }
    void build(){
        ord.assign(n, -1); low.resize(n); parent.assign(n, -1); articulation.assign(n, false); bridges.clear(); timer = 0;
        vector<int> parent_edge(n, -1), children(n);
        for (int root = 0; root < n; ++root) if (ord[root] < 0){
            ord[root] = low[root] = timer++;
            vector<pair<int,int>> st{{root,0}};
            while (!st.empty()){
                int v = st.back().first; int& i = st.back().second;
                if (i < (int)g[v].size()){
                    auto [to,id] = g[v][i++]; if (id == parent_edge[v]) continue;
                    if (ord[to] < 0){ parent[to] = v; parent_edge[to] = id; ++children[v]; ord[to] = low[to] = timer++; st.push_back({to,0}); }
                    else low[v] = min(low[v], ord[to]);
                } else {
                    st.pop_back();
                    if (parent[v] >= 0){ int p = parent[v]; low[p] = min(low[p], low[v]); if (low[v] > ord[p]) bridges.push_back(parent_edge[v]); if (parent[p] >= 0 && low[v] >= ord[p]) articulation[p] = true; }
                }
            }
            articulation[root] = children[root] >= 2;
        }
        sort(all(bridges));
    }
    vector<int> articulation_points() const { vector<int> res; for (int v = 0; v < n; ++v) if (articulation[v]) res.push_back(v); return res; }
    vector<pair<int,int>> bridge_edges() const { vector<pair<int,int>> res; for (int id : bridges) res.push_back(edges[id]); return res; }
};

struct TwoEdgeConnectedComponents {
    LowLink lowlink; vector<int> comp; vector<vector<int>> groups, forest;
    TwoEdgeConnectedComponents(int n = 0) : lowlink(n) {}
    int add_edge(int u, int v){ return lowlink.add_edge(u, v); }
    int build(){
        lowlink.build(); int n = lowlink.n; vector<char> bridge(lowlink.edges.size()); for (int id : lowlink.bridges) bridge[id] = true;
        comp.assign(n, -1); groups.clear();
        for (int s = 0; s < n; ++s) if (comp[s] < 0){ int id = groups.size(); groups.push_back({}); queue<int> q; q.push(s); comp[s] = id; while (!q.empty()){ int v = q.front(); q.pop(); groups[id].push_back(v); for (auto [to,e] : lowlink.g[v]) if (!bridge[e] && comp[to] < 0) comp[to] = id, q.push(to); } }
        forest.assign(groups.size(), {}); for (int id : lowlink.bridges){ auto [u,v] = lowlink.edges[id]; int a = comp[u], b = comp[v]; forest[a].push_back(b); forest[b].push_back(a); }
        return groups.size();
    }
};


namespace cycle_detail {
inline vector<int> path(const vector<vector<int>>& g,int s,int t,int banned_vertex=-1,pair<int,int> banned_edge={-1,-1},bool directed=true){
    if(s==banned_vertex||t==banned_vertex)return{};
    vector<int>pre(g.size(),-1);queue<int>q;pre[s]=s;q.push(s);
    while(!q.empty()){int v=q.front();q.pop();for(int to:g[v]){bool bad=v==banned_edge.first&&to==banned_edge.second;if(!directed)bad=bad||(v==banned_edge.second&&to==banned_edge.first);if(bad||to==banned_vertex||pre[to]>=0)continue;pre[to]=v;q.push(to);}}
    if(pre[t]<0)return{};
    vector<int>p;for(int v=t;;v=pre[v]){p.push_back(v);if(v==s)break;}reverse(all(p));return p;
}
inline bool distinct(const vector<int>& p){auto q=p;sort(all(q));return adjacent_find(all(q))==q.end();}
}

inline vector<int> find_cycle_directed(const vector<vector<int>>& g){
    int n=g.size();vector<int>state(n),pos(n,-1),st;for(int s=0;s<n;++s)if(!state[s]){vector<pair<int,int>>dfs{{s,0}};state[s]=1;pos[s]=st.size();st.push_back(s);while(!dfs.empty()){auto&[v,i]=dfs.back();if(i==(int)g[v].size()){state[v]=2;pos[v]=-1;st.pop_back();dfs.pop_back();continue;}int to=g[v][i++];if(!state[to])state[to]=1,pos[to]=st.size(),st.push_back(to),dfs.push_back({to,0});else if(state[to]==1)return vector<int>(st.begin()+pos[to],st.end());}}return{};
}
inline bool has_cycle_directed(const vector<vector<int>>&g){return !find_cycle_directed(g).empty();}

inline vector<int> find_cycle_undirected(const vector<vector<int>>&g){
    int n=g.size();vector<int>par(n,-1),dep(n),state(n);for(int s=0;s<n;++s)if(!state[s]){vector<pair<int,int>>st{{s,0}};state[s]=1;while(!st.empty()){auto&[v,i]=st.back();if(i==(int)g[v].size()){state[v]=2;st.pop_back();continue;}int to=g[v][i++];if(to==v)return{v};if(to==par[v])continue;if(!state[to])par[to]=v,dep[to]=dep[v]+1,state[to]=1,st.push_back({to,0});else if(state[to]==1&&dep[to]<dep[v]){vector<int>c;for(int x=v;x!=to;x=par[x])c.push_back(x);c.push_back(to);reverse(all(c));return c;}}}return{};
}
inline bool has_cycle_undirected(const vector<vector<int>>&g){return !find_cycle_undirected(g).empty();}

inline vector<int> find_cycle_through_directed(const vector<vector<int>>&g,int x){for(int to:g[x]){if(to==x)return{x};auto p=cycle_detail::path(g,to,x);if(!p.empty()){p.pop_back();p.insert(p.begin(),x);return p;}}return{};}
inline bool has_cycle_through_directed(const vector<vector<int>>&g,int x){return !find_cycle_through_directed(g,x).empty();}
inline vector<int> find_cycle_through_undirected(const vector<vector<int>>&g,int x){
    for(int to:g[x])if(to==x)return{x};
    for(int i=0;i<(int)g[x].size();++i)for(int j=i+1;j<(int)g[x].size();++j){int a=g[x][i],b=g[x][j];auto p=cycle_detail::path(g,a,b,x,{-1,-1},false);if(!p.empty()){p.insert(p.begin(),x);return p;}}
    return{};
}
inline bool has_cycle_through_undirected(const vector<vector<int>>&g,int x){return !find_cycle_through_undirected(g,x).empty();}

inline vector<int> find_cycle_through_edge_directed(const vector<vector<int>>&g,int u,int v){auto p=cycle_detail::path(g,v,u);if(p.empty())return{};p.pop_back();p.insert(p.begin(),u);return p;}
inline bool has_cycle_through_edge_directed(const vector<vector<int>>&g,int u,int v){return !find_cycle_through_edge_directed(g,u,v).empty();}
inline vector<int> find_cycle_through_edge_undirected(const vector<vector<int>>&g,int u,int v){auto p=cycle_detail::path(g,u,v,-1,{u,v},false);return p.empty()?vector<int>{}:p;}
inline bool has_cycle_through_edge_undirected(const vector<vector<int>>&g,int u,int v){return !find_cycle_through_edge_undirected(g,u,v).empty();}

inline vector<int> find_odd_cycle_undirected(const vector<vector<int>>&g){
    int n=g.size();vector<int>color(n,-1),par(n,-1),dep(n);for(int s=0;s<n;++s)if(color[s]<0){queue<int>q;q.push(s);color[s]=0;while(!q.empty()){int v=q.front();q.pop();for(int to:g[v]){if(to==v)return{v};if(color[to]<0)color[to]=color[v]^1,par[to]=v,dep[to]=dep[v]+1,q.push(to);else if(color[to]==color[v]){int a=v,b=to;vector<int>x,y;while(dep[a]>dep[b])x.push_back(a),a=par[a];while(dep[b]>dep[a])y.push_back(b),b=par[b];while(a!=b)x.push_back(a),y.push_back(b),a=par[a],b=par[b];x.push_back(a);reverse(all(y));x.insert(x.end(),all(y));return x;}}}}return{};
}
inline bool has_odd_cycle_undirected(const vector<vector<int>>&g){return !find_odd_cycle_undirected(g).empty();}

inline vector<int> find_even_cycle_undirected(const vector<vector<int>>&g){
    int n=g.size();for(int u=0;u<n;++u)for(int v:g[u])if(u<v){int states=2*n;vector<int>pre(states,-1),pv(states,-1);queue<int>q;int s=2*u;pre[s]=s;q.push(s);while(!q.empty()){int z=q.front();q.pop();int x=z/2,p=z%2;for(int to:g[x]){if((x==u&&to==v)||(x==v&&to==u))continue;int nz=2*to+(p^1);if(pre[nz]<0)pre[nz]=z,pv[nz]=x,q.push(nz);}}int t=2*v+1;if(pre[t]<0)continue;vector<int>p;for(int z=t;;z=pre[z]){p.push_back(z/2);if(z==s)break;}reverse(all(p));if(cycle_detail::distinct(p))return p;}return{};
}
inline bool has_even_cycle_undirected(const vector<vector<int>>&g){return !find_even_cycle_undirected(g).empty();}

inline vector<int> find_shortest_cycle_directed(const vector<vector<int>>&g){vector<int>best;for(int s=0;s<(int)g.size();++s)for(int to:g[s]){auto p=cycle_detail::path(g,to,s);if(!p.empty()){p.pop_back();p.insert(p.begin(),s);if(best.empty()||p.size()<best.size())best=move(p);}}return best;}
inline vector<int> find_shortest_cycle_undirected(const vector<vector<int>>&g){vector<int>best;for(int u=0;u<(int)g.size();++u)for(int v:g[u])if(u<=v){auto p=cycle_detail::path(g,u,v,-1,{u,v},false);if(!p.empty()&&(best.empty()||p.size()<best.size()))best=move(p);}return best;}
inline vector<int> find_cycle_at_most_directed(const vector<vector<int>>&g,int k){auto c=find_shortest_cycle_directed(g);return (int)c.size()<=k?c:vector<int>{};}
inline vector<int> find_cycle_at_most_undirected(const vector<vector<int>>&g,int k){auto c=find_shortest_cycle_undirected(g);return (int)c.size()<=k?c:vector<int>{};}

template<class T=long long> struct BinaryLifting {
    int n=0,log=1;vector<vector<pair<int,T>>>g;vector<vector<int>>up;vector<int>depth;vector<T>root_dist;
    BinaryLifting(int m=0){reset(m);}void reset(int m){n=m;log=1;g.assign(n,{});while((1LL<<log)<=max(1,n))++log;}
    void add_edge(int u,int v,T w=1){g[u].push_back({v,w});g[v].push_back({u,w});}
    void build(int root=0){up.assign(log,vector<int>(n,root));depth.assign(n,-1);root_dist.assign(n,T{});queue<int>q;q.push(root);depth[root]=0;up[0][root]=root;while(!q.empty()){int v=q.front();q.pop();for(auto[to,w]:g[v])if(depth[to]<0)depth[to]=depth[v]+1,root_dist[to]=root_dist[v]+w,up[0][to]=v,q.push(to);}for(int k=1;k<log;++k)for(int v=0;v<n;++v)up[k][v]=up[k-1][up[k-1][v]];}
    int jump(int v,long long k)const{for(int i=0;i<log&&k;++i,k>>=1)if(k&1)v=up[i][v];return v;}
    int lca(int a,int b)const{if(depth[a]<depth[b])swap(a,b);a=jump(a,depth[a]-depth[b]);if(a==b)return a;for(int k=log-1;k>=0;--k)if(up[k][a]!=up[k][b])a=up[k][a],b=up[k][b];return up[0][a];}
    T dist(int a,int b)const{int c=lca(a,b);return root_dist[a]+root_dist[b]-root_dist[c]-root_dist[c];}
};

struct HeavyLightDecomposition {
    int n = 0, timer = 0;
    vector<vector<int>> g;
    vector<int> parent, depth, sub, heavy, head, in, rev;

    HeavyLightDecomposition(int m = 0) : n(m), g(m) {}
    void add_edge(int u, int v){ g[u].push_back(v); g[v].push_back(u); }

    void build(int root = 0){
        parent.assign(n, -1); depth.assign(n, 0); sub.assign(n, 1); heavy.assign(n, -1);
        vector<int> order{root}; parent[root] = root;
        for (int i = 0; i < (int)order.size(); ++i){
            int v = order[i];
            for (int to : g[v]) if (to != parent[v]) parent[to] = v, depth[to] = depth[v] + 1, order.push_back(to);
        }
        assert((int)order.size() == n);
        for (int i = n - 1; i > 0; --i){
            int v = order[i], p = parent[v]; sub[p] += sub[v];
            if (heavy[p] < 0 || sub[heavy[p]] < sub[v]) heavy[p] = v;
        }
        timer = 0; head.assign(n, 0); in.assign(n, 0); rev.assign(n, 0);
        vector<pair<int,int>> chains{{root, root}};
        while (!chains.empty()){
            auto [v, h] = chains.back(); chains.pop_back();
            for (; v != -1; v = heavy[v]){
                head[v] = h; in[v] = timer; rev[timer++] = v;
                for (int to : g[v]) if (to != parent[v] && to != heavy[v]) chains.push_back({to, to});
            }
        }
    }
    int lca(int u, int v) const {
        while (head[u] != head[v]){ if (depth[head[u]] < depth[head[v]]) swap(u, v); u = parent[head[u]]; }
        return depth[u] < depth[v] ? u : v;
    }
    int dist(int u, int v) const { int w = lca(u, v); return depth[u] + depth[v] - 2 * depth[w]; }
    pair<int,int> subtree(int v, bool edge = false) const { return {in[v] + edge, in[v] + sub[v]}; }
    template<class F> void for_each_path(int u, int v, F f, bool edge = false) const {
        while (head[u] != head[v]){
            if (depth[head[u]] < depth[head[v]]) swap(u, v);
            f(in[head[u]], in[u] + 1); u = parent[head[u]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        if (in[u] + edge < in[v] + 1) f(in[u] + edge, in[v] + 1);
    }
};

template<class DP, class Cost, DP (*merge_dp)(DP,DP), DP (*identity_dp)(), DP (*add_edge_dp)(DP,Cost), DP (*add_vertex_dp)(DP,int)>
struct Rerooting {
    struct Edge { int to; Cost cost; };
    int n; vector<vector<Edge>> g; vector<DP> answer;
    Rerooting(int m = 0) : n(m), g(m) {}
    void add_edge(int u, int v, Cost cost = Cost{}){ g[u].push_back({v,cost}); g[v].push_back({u,cost}); }
    const vector<DP>& build(int root = 0){
        vector<int> parent(n, -1), order{root}; vector<Cost> parent_cost(n);
        parent[root] = root;
        for (int i = 0; i < (int)order.size(); ++i) for (auto [to,c] : g[order[i]]) if (parent[to] < 0)
            parent[to] = order[i], parent_cost[to] = c, order.push_back(to);
        vector<DP> down(n, identity_dp()), from_parent(n, identity_dp());
        for (int i = n - 1; i >= 0; --i){ int v = order[i]; DP x = identity_dp(); for (auto [to,c] : g[v]) if (parent[to] == v) x = merge_dp(x, add_edge_dp(down[to], c)); down[v] = add_vertex_dp(x, v); }
        answer.assign(n, identity_dp());
        for (int v : order){
            int m = g[v].size(); vector<DP> pref(m + 1, identity_dp()), suff(m + 1, identity_dp());
            for (int i = 0; i < m; ++i){ auto [to,c] = g[v][i]; DP x = to == parent[v] ? from_parent[v] : add_edge_dp(down[to], c); pref[i + 1] = merge_dp(pref[i], x); }
            for (int i = m - 1; i >= 0; --i){ auto [to,c] = g[v][i]; DP x = to == parent[v] ? from_parent[v] : add_edge_dp(down[to], c); suff[i] = merge_dp(x, suff[i + 1]); }
            answer[v] = add_vertex_dp(pref[m], v);
            for (int i = 0; i < m; ++i){ auto [to,c] = g[v][i]; if (parent[to] == v) from_parent[to] = add_edge_dp(add_vertex_dp(merge_dp(pref[i], suff[i + 1]), v), c); }
        }
        return answer;
    }
};

struct EulerTour {
    int n=0,timer=0;vector<vector<pair<int,long long>>>g;vector<int>in,out,parent;vector<long long>vcost,edge_to_parent;FenwickTree<long long>vsub,vpath,esub,epath;BinaryLifting<long long>bl;
    EulerTour(int m=0):n(m),g(m),vcost(m),edge_to_parent(m),bl(m){}
    void addEdge(int u,int v,long long w=0){g[u].push_back({v,w});g[v].push_back({u,w});bl.add_edge(u,v,w);}
    void addVCost(int v,long long w){vcost[v]=w;}
    void build(int root=0){timer=0;in.assign(n,-1);out.assign(n,-1);parent.assign(n,-1);vector<pair<int,int>>st{{root,0}};parent[root]=root;while(!st.empty()){auto&[v,i]=st.back();if(i==0)in[v]=timer++;if(i==(int)g[v].size()){out[v]=timer;st.pop_back();continue;}auto[to,w]=g[v][i++];if(to==parent[v])continue;parent[to]=v;edge_to_parent[to]=w;st.push_back({to,0});}vector<long long>vs(n),es(n),vp(n+1),ep(n+1);for(int v=0;v<n;++v){vs[in[v]]=vcost[v];es[in[v]]=edge_to_parent[v];vp[in[v]]+=vcost[v];vp[out[v]]-=vcost[v];ep[in[v]]+=edge_to_parent[v];ep[out[v]]-=edge_to_parent[v];}vsub=FenwickTree<long long>(vs);esub=FenwickTree<long long>(es);vpath=FenwickTree<long long>(vp);epath=FenwickTree<long long>(ep);bl.build(root);}
    int lca(int u,int v)const{return bl.lca(u,v);}long long rootE(int v)const{return epath.sum(in[v]+1);}long long rootV(int v)const{return vpath.sum(in[v]+1);}
    long long distE(int u,int v)const{int c=lca(u,v);return rootE(u)+rootE(v)-2*rootE(c);}
    long long partV(int v)const{return vsub.sum(in[v],out[v]);}long long partE(int v)const{return esub.sum(in[v]+1,out[v]);}
    long long distV(int u,int v)const{int c=lca(u,v);return rootV(u)+rootV(v)-2*rootV(c)+vcost[c];}
    void changeECost(int u,int v,long long w){int x=parent[u]==v?u:parent[v]==u?v:-1;assert(x>=0);long long d=w-edge_to_parent[x];edge_to_parent[x]=w;esub.add(in[x],d);epath.add(in[x],d);epath.add(out[x],-d);}
};

struct FunctionalGraph {
    int n=0,log=61;vector<int>to,dist_cycle,cid,entry,component;vector<vector<int>>up,cycles;
    FunctionalGraph()=default;FunctionalGraph(const vector<int>&next){build(next);}
    void build(const vector<int>&next){
        to=next;n=to.size();up.assign(log,vector<int>(n));up[0]=to;for(int k=1;k<log;++k)for(int v=0;v<n;++v)up[k][v]=up[k-1][up[k-1][v]];
        vector<int>deg(n);vector<vector<int>>rev(n);for(int v=0;v<n;++v)++deg[to[v]],rev[to[v]].push_back(v);queue<int>q;vector<char>removed(n);for(int v=0;v<n;++v)if(!deg[v])q.push(v);while(!q.empty()){int v=q.front();q.pop();removed[v]=1;if(!--deg[to[v]])q.push(to[v]);}
        cid.assign(n,-1);entry.assign(n,-1);component.assign(n,-1);dist_cycle.assign(n,-1);cycles.clear();
        for(int s=0;s<n;++s)if(!removed[s]&&cid[s]<0){int id=cycles.size();vector<int>c;for(int v=s;;v=to[v]){cid[v]=component[v]=id;entry[v]=v;dist_cycle[v]=0;c.push_back(v);if(to[v]==s)break;}cycles.push_back(c);}
        queue<int>b;for(auto&c:cycles)for(int v:c)b.push(v);while(!b.empty()){int v=b.front();b.pop();for(int x:rev[v])if(dist_cycle[x]<0)dist_cycle[x]=dist_cycle[v]+1,cid[x]=component[x]=cid[v],entry[x]=entry[v],b.push(x);}
    }
    int jump(int v,unsigned long long k)const{for(int i=0;i<log;++i)if(k>>i&1ULL)v=up[i][v];return v;}
    int dist_to_cycle(int v)const{return dist_cycle[v];}int cycle_id(int v)const{return cid[v];}int entry_vertex(int v)const{return entry[v];}int cycle_size(int v)const{return cycles[cid[v]].size();}
};

template<class T> int lis_length(const vector<T>&a,bool strict=true){vector<T>d;for(auto&x:a){auto it=strict?lower_bound(all(d),x):upper_bound(all(d),x);if(it==d.end())d.push_back(x);else*it=x;}return d.size();}


struct Mo {
    struct Query { int l, r, id; };
    int n; vector<Query> queries;
    Mo(int m = 0) : n(m) {}
    int add_query(int l, int r){ assert(0 <= l && l <= r && r <= n); int id = queries.size(); queries.push_back({l,r,id}); return id; }
    vector<int> order() const {
        int q = queries.size(), block = max(1, (int)(n / max(1.0, sqrt((double)max(1,q))))); vector<Query> sorted = queries;
        sort(all(sorted), [&](const Query& a, const Query& b){ int x = a.l / block, y = b.l / block; if (x != y) return x < y; return x & 1 ? a.r > b.r : a.r < b.r; });
        vector<int> res; res.reserve(q); for (auto query : sorted) res.push_back(query.id); return res;
    }
};
template<class Seq> auto run_length_encoding(const Seq&s){using T=typename Seq::value_type;vector<pair<T,int>>r;for(auto&x:s){if(r.empty()||r.back().first!=x)r.push_back({x,1});else++r.back().second;}return r;}


template<class Seq> vector<int> z_algorithm(const Seq&s){int n=s.size();vector<int>z(n);if(!n)return z;z[0]=n;for(int i=1,j=0;i<n;){while(i+j<n&&s[j]==s[i+j])++j;z[i]=j;if(!j){++i;continue;}int k=1;while(i+k<n&&k+z[k]<j)z[i+k]=z[k],++k;i+=k;j-=k;}return z;}
template<class Seq> vector<int> prefix_function(const Seq&s){int n=s.size();vector<int>p(n);for(int i=1;i<n;++i){int j=p[i-1];while(j&&s[i]!=s[j])j=p[j-1];if(s[i]==s[j])++j;p[i]=j;}return p;}
template<class Seq> vector<int> kmp_search(const Seq&text,const Seq&pattern){vector<int>res;if(pattern.empty()){for(int i=0;i<=(int)text.size();++i)res.push_back(i);return res;}auto p=prefix_function(pattern);for(int i=0,j=0;i<(int)text.size();++i){while(j&&text[i]!=pattern[j])j=p[j-1];if(text[i]==pattern[j])++j;if(j==(int)pattern.size())res.push_back(i-j+1),j=p[j-1];}return res;}
template<class Seq> vector<int> manacher_odd(const Seq&s){int n=s.size();vector<int>d(n);for(int i=0,l=0,r=-1;i<n;++i){int k=i>r?1:min(d[l+r-i],r-i+1);while(i-k>=0&&i+k<n&&s[i-k]==s[i+k])++k;d[i]=k--;if(i+k>r)l=i-k,r=i+k;}return d;}


struct RollingHash {
    using ull=uint64_t;static constexpr ull mod=(1ULL<<61)-1,base=1000003;
    vector<ull>h,p;static ull add(ull a,ull b){a+=b;return a>=mod?a-mod:a;}static ull mul(ull a,ull b){__uint128_t t=(__uint128_t)a*b;t=(t>>61)+(t&mod);ull r=(ull)t;return r>=mod?r-mod:r;}
    RollingHash()=default;template<class Seq>RollingHash(const Seq&s){int n=s.size();h.assign(n+1,0);p.assign(n+1,1);for(int i=0;i<n;++i)h[i+1]=add(mul(h[i],base),(unsigned long long)s[i]+1),p[i+1]=mul(p[i],base);}
    ull get(int l,int r)const{ull x=add(h[r],mod-mul(h[l],p[r-l]));return x;}static ull concat(ull left,ull right,int right_len,const RollingHash&rh){return add(mul(left,rh.p[right_len]),right);}
};


inline vector<int> suffix_array(const string& s){
    int n = s.size(); if (!n) return {}; vector<int> sa(n), rank(n), next_rank(n), count(max(n,256));
    for (unsigned char c : s) ++count[c];
    for (int i = 1; i < 256; ++i) count[i] += count[i-1];
    for (int i = n-1; i >= 0; --i) sa[--count[(unsigned char)s[i]]] = i;
    int classes = 1; rank[sa[0]] = 0; for (int i = 1; i < n; ++i){ if (s[sa[i-1]] != s[sa[i]]) ++classes; rank[sa[i]] = classes - 1; }
    for (int k = 1; k < n; k <<= 1){
        vector<int> second; second.reserve(n); for (int i = n-k; i < n; ++i) second.push_back(i); for (int v : sa) if (v >= k) second.push_back(v-k);
        fill(count.begin(), count.begin()+classes, 0); for (int v : second) ++count[rank[v]]; for (int i = 1; i < classes; ++i) count[i] += count[i-1]; for (int i = n-1; i >= 0; --i) sa[--count[rank[second[i]]]] = second[i];
        next_rank[sa[0]] = 0; int next_classes = 1; for (int i = 1; i < n; ++i){ int a=sa[i-1],b=sa[i]; if (rank[a] != rank[b] || (a+k<n?rank[a+k]:-1) != (b+k<n?rank[b+k]:-1)) ++next_classes; next_rank[b] = next_classes - 1; } rank.swap(next_rank); classes = next_classes; if (classes == n) break;
    }
    return sa;
}
inline vector<int> lcp_array(const string& s, const vector<int>& sa){
    int n = s.size(); if (!n) return {}; vector<int> rank(n), lcp(max(0,n-1)); for (int i = 0; i < n; ++i) rank[sa[i]] = i;
    for (int i = 0, h = 0; i < n; ++i){ int r = rank[i]; if (!r) continue; int j = sa[r-1]; while (i+h<n && j+h<n && s[i+h]==s[j+h]) ++h; lcp[r-1]=h; if(h)--h; }
    return lcp;
}
inline pair<int,int> suffix_array_equal_range(const string& s, const vector<int>& sa, const string& pattern){
    auto cmp = [&](int pos, const string& p){ return s.compare(pos, p.size(), p); };
    int l = lower_bound(all(sa), pattern, [&](int pos, const string& p){ return cmp(pos,p) < 0; }) - sa.begin();
    int r = upper_bound(all(sa), pattern, [&](const string& p, int pos){ return cmp(pos,p) > 0; }) - sa.begin();
    return {l,r};
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return 0;
}
