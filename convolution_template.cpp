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

namespace cp_transform {
inline constexpr size_t MAX_FFT_SIZE = size_t(1) << 23;

// Forward: exp(-2*pi*i*k/n); inverse divides by n. Empty input is a no-op.
// O(n log n) time, O(1) extra memory; floating-point results are approximate.
inline void fft(vector<complex<long double>>& a, bool inverse = false){
    size_t n = a.size();
    if (!n) return;
    if ((n & (n - 1)) || n > MAX_FFT_SIZE) throw invalid_argument("fft requires a power-of-two size <= 2^23");
    for (size_t i = 1, j = 0; i < n; ++i){
        size_t bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    const long double pi = acosl(-1.0L);
    for (size_t len = 2; len <= n; len <<= 1){
        long double angle = (inverse ? 2 : -2) * pi / len;
        complex<long double> root(cosl(angle), sinl(angle));
        for (size_t i = 0; i < n; i += len){
            complex<long double> w(1, 0);
            for (size_t j = 0; j < len / 2; ++j){
                auto u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v; a[i + j + len / 2] = u - v; w *= root;
            }
        }
    }
    if (inverse) for (auto& x : a) x /= (long double)n;
}

// Approximate real convolution; for exact integer counts use convolution_ll.
inline vector<long double> convolution_real(const vector<long double>& a, const vector<long double>& b){
    if (a.empty() || b.empty()) return {};
    if (a.size() > MAX_FFT_SIZE || b.size() > MAX_FFT_SIZE || a.size() + b.size() - 1 > MAX_FFT_SIZE)
        throw length_error("convolution_real requires padded length <= 2^23");
    size_t need = a.size() + b.size() - 1;
    if (min(a.size(), b.size()) <= 32){
        vector<long double> result(need);
        for (size_t i = 0; i < a.size(); ++i) for (size_t j = 0; j < b.size(); ++j) result[i + j] += a[i] * b[j];
        return result;
    }
    size_t n = 1; while (n < need) n <<= 1;
    vector<complex<long double>> x(n), y(n);
    copy(a.begin(), a.end(), x.begin()); copy(b.begin(), b.end(), y.begin());
    fft(x); fft(y);
    for (size_t i = 0; i < n; ++i) x[i] *= y[i];
    fft(x, true);
    vector<long double> result(need);
    for (size_t i = 0; i < need; ++i) result[i] = x[i].real();
    return result;
}
} // namespace cp_transform

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


namespace cp_transform {
namespace exact_detail {
constexpr int P1 = 167772161, P2 = 469762049, P3 = 754974721;
constexpr size_t MAX_SIZE = size_t(1) << 24;
constexpr long long P12 = (long long)P1 * P2;
constexpr __int128 PRODUCT = (__int128)P12 * P3;
static_assert(PRODUCT > ((__int128)1 << 85));

inline size_t output_size(size_t n, size_t m){
    if (!n || !m) return 0;
    if (n > MAX_SIZE || m > MAX_SIZE || n > MAX_SIZE + 1 - m)
        throw length_error("exact convolution output exceeds 2^24 coefficients");
    return n + m - 1;
}
template<int MOD> vector<int> residue_convolution(const vector<long long>& a, const vector<long long>& b){
    vector<MontgomeryModInt<MOD>> x(a.size()), z;
    for (size_t i = 0; i < a.size(); ++i) x[i] = a[i];
    if (&a == &b) z = ::convolution_square<MOD, MOD == P3 ? 11 : 3>(move(x));
    else {
        vector<MontgomeryModInt<MOD>> y(b.size());
        for (size_t i = 0; i < b.size(); ++i) y[i] = b[i];
        z = ::convolution<MOD, MOD == P3 ? 11 : 3>(move(x), move(y));
    }
    vector<int> result(z.size());
    for (size_t i = 0; i < z.size(); ++i) result[i] = z[i].val();
    return result;
}
inline __int128 restore(int a, int b, int c){
    static const long long inv12 = ModInt<P2>(P1).inv().val();
    static const long long inv123 = ModInt<P3>(P12).inv().val();
    long long t = (b - (long long)a + P2) * inv12 % P2;
    long long x = a + (long long)P1 * t;
    long long u = (c - x % P3 + P3) * inv123 % P3;
    return x + (__int128)P12 * u;
}
inline long long checked_long_long(__int128 x){
    if (x < LLONG_MIN || x > LLONG_MAX) throw overflow_error("convolution coefficient does not fit long long");
    return (long long)x;
}
inline unsigned long long max_abs(const vector<long long>& a){
    unsigned long long result = 0;
    for (long long x : a) result = max(result, x < 0 ? 0ull - (unsigned long long)x : (unsigned long long)x);
    return result;
}
} // namespace exact_detail

// Exact signed coefficients, O(N log N), output length <= 2^24.
// Passing the same vector twice reuses each forward transform.
// Except scalar products, min(n,m)*maxabs(a)*maxabs(b) must fit PRODUCT/2.
// This conservative CRT guard can reject valid cancellation-heavy inputs.
// Unsupported bounds or long long result overflow throw overflow_error.
// Excess output length throws length_error.
inline vector<long long> convolution_ll(const vector<long long>& a, const vector<long long>& b){
    using namespace exact_detail;
    size_t size = output_size(a.size(), b.size()); if (!size) return {};
    const auto& small = a.size() <= b.size() ? a : b;
    const auto& large = a.size() <= b.size() ? b : a;
    if (small.size() == 1){
        vector<long long> result(size);
        for (size_t i = 0; i < size; ++i) result[i] = checked_long_long((__int128)small[0] * large[i]);
        return result;
    }
    unsigned __int128 bound = (unsigned __int128)small.size() * max_abs(a);
    unsigned long long other = max_abs(b);
    if (bound && other > (unsigned __int128)(PRODUCT / 2) / bound)
        throw overflow_error("convolution_ll coefficient bound exceeds exact CRT range");
    if (small.size() <= 32){
        vector<long long> result(size);
        for (size_t k = 0; k < size; ++k){
            __int128 value = 0;
            size_t first = k >= large.size() ? k - large.size() + 1 : 0;
            for (size_t i = first; i < min(small.size(), k + 1); ++i) value += (__int128)small[i] * large[k - i];
            result[k] = checked_long_long(value);
        }
        return result;
    }
    auto x = residue_convolution<P1>(a, b), y = residue_convolution<P2>(a, b), z = residue_convolution<P3>(a, b);
    vector<long long> result(size);
    for (size_t i = 0; i < size; ++i){
        __int128 value = restore(x[i], y[i], z[i]);
        if (value > PRODUCT / 2) value -= PRODUCT;
        result[i] = checked_long_long(value);
    }
    return result;
}

// Exact coefficients modulo any 1 <= modulus <= INT_MAX, O(N log N).
// The output length must be <= 2^24; inputs may be negative long long values.
// Invalid modulus / excess length throw invalid_argument / length_error.
inline vector<int> convolution_mod(vector<long long> a, vector<long long> b, int modulus){
    using namespace exact_detail;
    if (modulus <= 0) throw invalid_argument("convolution_mod requires a positive modulus");
    size_t size = output_size(a.size(), b.size()); if (!size) return {};
    vector<int> result(size);
    if (modulus == 1) return result;
    for (auto& x : a){ x %= modulus; if (x < 0) x += modulus; }
    for (auto& x : b){ x %= modulus; if (x < 0) x += modulus; }
    if (min(a.size(), b.size()) <= 32){
        for (size_t i = 0; i < a.size(); ++i) for (size_t j = 0; j < b.size(); ++j)
            result[i + j] = (result[i + j] + a[i] * b[j]) % modulus;
        return result;
    }
    // min(n,m) <= 2^23 and residues < 2^31 make every integer coefficient < 2^85 < PRODUCT.
    auto x = residue_convolution<P1>(a, b), y = residue_convolution<P2>(a, b), z = residue_convolution<P3>(a, b);
    for (size_t i = 0; i < size; ++i) result[i] = restore(x[i], y[i], z[i]) % modulus;
    return result;
}
} // namespace cp_transform

namespace cp_transform {
// Dense nonnegative values only. result[s] counts pairs (a[i], b[j]) with sum s.
// Padded output length <= 2^24; all exact intermediate coefficients must fit LL.
inline vector<long long> pair_sum_counts(const vector<int>& a, const vector<int>& b){
    int max_a = 0, max_b = 0;
    for (int x : a){ if (x < 0) throw invalid_argument("pair_sum_counts requires nonnegative values"); max_a = max(max_a, x); }
    for (int x : b){ if (x < 0) throw invalid_argument("pair_sum_counts requires nonnegative values"); max_b = max(max_b, x); }
    if (a.empty() || b.empty()) return {};
    if ((long long)max_a + max_b + 1 > (1 << 24)) throw length_error("pair_sum_counts dense output exceeds 2^24");
    vector<long long> fa((size_t)max_a + 1), fb((size_t)max_b + 1);
    for (int x : a) ++fa[x];
    for (int x : b) ++fb[x];
    return convolution_ll(fa, fb);
}

// result[s] counts distinct index pairs i < j, including equal-valued elements.
inline vector<long long> unordered_pair_sum_counts(const vector<int>& values){
    if (values.empty()) return {};
    int largest = 0;
    for (int x : values){ if (x < 0) throw invalid_argument("unordered_pair_sum_counts requires nonnegative values"); largest = max(largest, x); }
    if (2LL * largest + 1 > (1 << 24)) throw length_error("unordered_pair_sum_counts dense output exceeds 2^24");
    vector<long long> frequency((size_t)largest + 1);
    for (int x : values) ++frequency[x];
    auto result = convolution_ll(frequency, frequency);
    for (int x : values) --result[2 * (size_t)x];
    for (auto& x : result) x /= 2;
    return result;
}

// ways[v] is the number of choices of value v. Make `picks` ordered choices,
// with replacement; return counts modulo 998244353 for sums 0..max_sum.
// O(L log L log picks) time, O(L) memory; max_sum <= 2^22-1 (NTT limit).
inline vector<mint> sum_distribution_mod(const vector<long long>& ways, long long picks, int max_sum){
    if (picks < 0 || max_sum < 0) throw invalid_argument("sum_distribution_mod requires nonnegative picks and max_sum");
    if (max_sum >= (1 << 22)) throw length_error("sum_distribution_mod requires max_sum < 2^22");
    for (long long x : ways) if (x < 0) throw invalid_argument("sum_distribution_mod requires nonnegative counts");
    size_t limit = (size_t)max_sum + 1;
    if (!picks){ vector<mint> result(limit); result[0] = 1; return result; }
    vector<mint> base(min(ways.size(), limit));
    for (size_t i = 0; i < base.size(); ++i) base[i] = ways[i];
    auto truncate = [limit](vector<mint> a){
        if (a.size() > limit) a.resize(limit);
        while (!a.empty() && a.back() == mint(0)) a.pop_back();
        return a;
    };
    base = truncate(move(base));
    vector<mint> result{1};
    while (picks && !base.empty()){
        if (picks & 1) result = truncate(::convolution(move(result), base));
        picks >>= 1;
        if (picks) base = truncate(::convolution_square(move(base)));
    }
    if (picks) result.clear();
    result.resize(limit);
    return result;
}
} // namespace cp_transform

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return 0;
}
