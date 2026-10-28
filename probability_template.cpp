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
    // Choose r items with repetition from n types; H(0,0)=1.
    T H(long long n, long long r) const {
        if (n < 0 || r < 0) return 0;
        if (!r) return 1;
        if (!n) return 0;
        if (n > LLONG_MAX - (r - 1)) throw overflow_error("H requires n+r-1 <= LLONG_MAX");
        return C(n + (r - 1), r);
    }
    // Permutations of groups of indistinguishable items; same prime-modulus contract as C.
    T multinomial(const vector<long long>& counts) const {
        for (long long count : counts) if (count < 0) return 0;
        long long remaining = 0;
        for (long long count : counts){
            if (count > LLONG_MAX - remaining) throw overflow_error("multinomial total exceeds LLONG_MAX");
            remaining += count;
        }
        T result = 1;
        for (long long count : counts){
            if (count && count != remaining) result *= C(remaining, count);
            remaining -= count;
        }
        return result;
    }
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

namespace cp_subset {
namespace detail {
template<bool Superset, bool Inverse, class T> void transform(vector<T>& a){
    size_t n = a.size();
    if (n && (n & (n - 1))) throw invalid_argument("subset transform requires a power-of-two length");
    for (size_t half = 1; half < n; half <<= 1){
        for (size_t block = 0; block < n; block += half * 2){
            for (size_t j = 0; j < half; ++j){
                auto& lower = a[block + j]; auto& upper = a[block + half + j];
                if constexpr (Superset){ if constexpr (Inverse) lower -= upper; else lower += upper; }
                else { if constexpr (Inverse) upper -= lower; else upper += lower; }
            }
        }
    }
}
} // namespace detail

// In-place, O(B*2^B) time and O(1) extra space. Empty input is a no-op.
// subset_zeta: a[S] <- sum of original a[T] over T subset of S.
template<class T> void subset_zeta(vector<T>& a){ detail::transform<false,false>(a); }
template<class T> void subset_mobius(vector<T>& a){ detail::transform<false,true>(a); }
// superset_zeta: a[S] <- sum of original a[T] over T superset of S.
template<class T> void superset_zeta(vector<T>& a){ detail::transform<true,false>(a); }
template<class T> void superset_mobius(vector<T>& a){ detail::transform<true,true>(a); }

// c[S] = sum_{i|j=S} a[i]*b[j]. Inputs must have equal power-of-two lengths.
template<class T> vector<T> bitwise_or_convolution(vector<T> a, vector<T> b){
    if (a.size() != b.size()) throw invalid_argument("bitwise convolution requires equal lengths");
    subset_zeta(a); subset_zeta(b);
    for (size_t i = 0; i < a.size(); ++i) a[i] *= b[i];
    subset_mobius(a); return a;
}
// c[S] = sum_{i&j=S} a[i]*b[j]. O(B*2^B) time, O(2^B) memory.
template<class T> vector<T> bitwise_and_convolution(vector<T> a, vector<T> b){
    if (a.size() != b.size()) throw invalid_argument("bitwise convolution requires equal lengths");
    superset_zeta(a); superset_zeta(b);
    for (size_t i = 0; i < a.size(); ++i) a[i] *= b[i];
    superset_mobius(a); return a;
}
} // namespace cp_subset

namespace cp_linear {
template<class T> using Matrix = vector<vector<T>>;

namespace matrix_detail {
template<class T> size_t width(const Matrix<T>& a){
    size_t columns = a.empty() ? 0 : a.front().size();
    for (const auto& row : a) if (row.size() != columns) throw invalid_argument("matrix must be rectangular");
    return columns;
}
} // namespace matrix_detail

template<class T> Matrix<T> matrix_identity(size_t n){
    Matrix<T> result(n, vector<T>(n, T(0)));
    for (size_t i = 0; i < n; ++i) result[i][i] = T(1);
    return result;
}

// O(rows(a)*cols(a)*cols(b)); scalar arithmetic must remain valid in T.
// An empty outer vector represents 0x0; a zero-row nonzero-width shape is not stored.
template<class T> Matrix<T> matrix_multiply(const Matrix<T>& a, const Matrix<T>& b){
    size_t inner = matrix_detail::width(a), columns = matrix_detail::width(b);
    if (inner != b.size()) throw invalid_argument("incompatible matrix dimensions");
    Matrix<T> result(a.size(), vector<T>(columns, T(0)));
    for (size_t i = 0; i < a.size(); ++i) for (size_t k = 0; k < inner; ++k)
        for (size_t j = 0; j < columns; ++j) result[i][j] += a[i][k] * b[k][j];
    return result;
}

// O(n^3 log(exponent+1)) time, O(n^2) extra space.
template<class T> Matrix<T> matrix_power(Matrix<T> a, long long exponent){
    if (exponent < 0) throw invalid_argument("matrix exponent must be nonnegative");
    if (matrix_detail::width(a) != a.size()) throw invalid_argument("matrix power requires a square matrix");
    auto result = matrix_identity<T>(a.size());
    while (exponent){
        if (exponent & 1) result = matrix_multiply(result, a);
        exponent >>= 1;
        if (exponent) a = matrix_multiply(a, a);
    }
    return result;
}
} // namespace cp_linear

namespace cp_linear {
template<class T> struct LinearSolution {
    bool consistent = true;
    int rank = 0; // Coefficient-matrix rank, not solution-space dimension.
    vector<T> particular;
    Matrix<T> kernel;
};

namespace linear_detail {
template<class T, bool Real> LinearSolution<T> eliminate(Matrix<T> a, vector<T> b, int variables, long double eps){
    size_t width = matrix_detail::width(a);
    if (variables < -1 || b.size() != a.size()) throw invalid_argument("invalid linear-system dimensions");
    if (a.empty()) width = variables < 0 ? 0 : (size_t)variables;
    else if (variables >= 0 && width != (size_t)variables) throw invalid_argument("variable count differs from matrix width");
    if (a.size() > INT_MAX || width > INT_MAX) throw length_error("linear system is too large");
    int n = (int)a.size(), m = (int)width;
    auto zero = [eps](const T& x){
        if constexpr (Real) return fabsl(x) <= eps;
        else return x == T(0);
    };
    auto check_finite = [](const T& x){
        if constexpr (Real) if (!isfinite(x)) throw overflow_error("nonfinite linear-system intermediate");
    };
    if constexpr (Real){
        if (!isfinite(eps) || eps <= 0) throw invalid_argument("epsilon must be finite and positive");
        for (const auto& row : a) for (auto x : row) if (!isfinite(x)) throw invalid_argument("matrix entries must be finite");
        for (auto x : b) if (!isfinite(x)) throw invalid_argument("right-hand side must be finite");
    }
    vector<int> where(m, -1);
    LinearSolution<T> result;
    for (int column = 0; column < m && (result.rank) < n; ++column){
        int row = result.rank, pivot = row;
        if constexpr (Real){
            for (int i = row + 1; i < n; ++i) if (fabsl(a[i][column]) > fabsl(a[pivot][column])) pivot = i;
        } else {
            while (pivot < n && zero(a[pivot][column])) ++pivot;
            if (pivot == n) continue;
        }
        if (zero(a[pivot][column])) continue;
        swap(a[pivot], a[row]); swap(b[pivot], b[row]);
        T divisor = a[row][column];
        if constexpr (Real){
            for (int j = column + 1; j < m; ++j){ a[row][j] /= divisor; check_finite(a[row][j]); }
            b[row] /= divisor; check_finite(b[row]);
        } else {
            T inverse = T(1) / divisor;
            for (int j = column + 1; j < m; ++j) a[row][j] *= inverse;
            b[row] *= inverse;
        }
        a[row][column] = T(1);
        for (int i = 0; i < n; ++i) if (i != row){
            T factor = a[i][column];
            if (factor == T(0)) continue;
            for (int j = column + 1; j < m; ++j){ a[i][j] -= factor * a[row][j]; check_finite(a[i][j]); }
            b[i] -= factor * b[row]; check_finite(b[i]);
            a[i][column] = T(0);
        }
        where[column] = row; ++result.rank;
    }
    for (int i = result.rank; i < n; ++i){
        bool all_zero = true;
        for (auto x : a[i]) if (!zero(x)){ all_zero = false; break; }
        if (all_zero && !zero(b[i])){ result.consistent = false; return result; }
    }
    result.particular.assign(m, T(0));
    for (int j = 0; j < m; ++j) if (where[j] >= 0) result.particular[j] = b[where[j]];
    for (int free_column = 0; free_column < m; ++free_column) if (where[free_column] < 0){
        vector<T> basis(m, T(0)); basis[free_column] = T(1);
        for (int j = 0; j < m; ++j) if (where[j] >= 0) basis[j] = T(0) - a[where[j]][free_column];
        result.kernel.push_back(move(basis));
    }
    return result;
}
} // namespace linear_detail

// Exact field arithmetic (e.g. ModInt with prime modulus), not integer division.
// O(n*m*min(n,m) + m^2) time, O(n*m + m^2) space including the kernel basis.
// With no rows, `variables` supplies the otherwise unrepresentable column count.
template<class T> LinearSolution<T> gauss_jordan(Matrix<T> a, vector<T> b, int variables = -1){
    static_assert(!is_arithmetic_v<T>, "use a field type for exact solving, or solve_linear_real for floating point");
    return linear_detail::eliminate<T,false>(move(a), move(b), variables, 0);
}

// Absolute epsilon, partial pivoting; rank/consistency are numerical decisions.
// Rescale ill-conditioned problems or use exact arithmetic when possible.
inline LinearSolution<long double> solve_linear_real(Matrix<long double> a, vector<long double> b, long double eps = 1e-12L, int variables = -1){
    return linear_detail::eliminate<long double,true>(move(a), move(b), variables, eps);
}
} // namespace cp_linear

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

namespace cp_probability {
namespace distribution_detail {
template<class T> void check_probability(const T& p){
    static_assert(!is_integral_v<T>, "use a floating-point or modular probability type");
    if constexpr (is_floating_point_v<T>){
        if (!isfinite(p) || p < 0 || p > 1) throw invalid_argument("probability must be finite and in [0,1]");
    }
}
template<class T> void check_pmf(const vector<T>& pmf){
    if (pmf.empty()) throw invalid_argument("PMF must be nonempty and normalized");
    if constexpr (is_floating_point_v<T>){
        long double total = 0;
        for (T p : pmf){ check_probability(p); total += (long double)p; }
        long double tolerance = max(1e-12L, 64.0L * numeric_limits<T>::epsilon());
        if (fabsl(total - 1) > tolerance) throw invalid_argument("PMF must sum to one");
    } else {
        T total = 0; for (const T& p : pmf){ check_probability(p); total += p; }
        if (total != T(1)) throw invalid_argument("PMF must sum to one in the current field");
    }
}
} // namespace distribution_detail

// Independent Bernoulli trials; result[k] = P(exactly k successes).
// O(N^2) time, O(N) memory. Modular p must represent probabilities in a field.
template<class T> vector<T> bernoulli_sum_distribution(const vector<T>& probabilities){
    vector<T> result(probabilities.size() + 1); result[0] = 1;
    for (size_t i = 0; i < probabilities.size(); ++i){
        T p = probabilities[i]; distribution_detail::check_probability(p); T q = T(1) - p;
        for (size_t k = i + 1; k > 0; --k) result[k] = result[k] * q + result[k - 1] * p;
        result[0] *= q;
    }
    return result;
}

// Identical independent trials. O(N) real time, O(N+log MOD) modular time.
// Modular T requires a prime modulus and N < MOD, except p=0/1 endpoints.
// Real weights start at their mode, avoiding underflow of the initial tail.
template<class T> vector<T> binomial_distribution(int n, T p){
    if (n < 0) throw invalid_argument("binomial_distribution requires nonnegative n");
    distribution_detail::check_probability(p);
    if constexpr (!is_floating_point_v<T>){
        if (p != T(0) && p != T(1) && n >= T::mod())
            throw invalid_argument("modular binomial_distribution requires n < modulus");
    }
    vector<T> result((size_t)n + 1);
    if (!n || p == T(0)){ result[0] = 1; return result; }
    if (p == T(1)){ result[n] = 1; return result; }
    if constexpr (is_floating_point_v<T>){
        long double probability = (long double)p, q = 1 - probability;
        int mode = (int)min((long double)n, floorl(((long double)n + 1) * probability));
        vector<long double> weights((size_t)n + 1); weights[mode] = 1;
        for (int k = mode; k > 0; --k) weights[k - 1] = weights[k] * k * q / (((long double)n - k + 1) * probability);
        for (int k = mode; k < n; ++k) weights[k + 1] = weights[k] * (n - k) * probability / (((long double)k + 1) * q);
        long double total = accumulate(weights.begin(), weights.end(), 0.0L);
        for (size_t k = 0; k < result.size(); ++k) result[k] = (T)(weights[k] / total);
    } else {
        vector<T> divisors(n); for (int k = 0; k < n; ++k) divisors[k] = k + 1;
        auto inverses = batch_inverse(divisors); T q = T(1) - p, ratio = p / q;
        result[0] = q.pow(n);
        for (size_t k = 1; k < result.size(); ++k) result[k] = result[k - 1] * T((long long)n - (long long)k + 1) * inverses[k - 1] * ratio;
    }
    return result;
}

// The nonempty PMF must sum to one. Floating tolerance: max(1e-12,64*epsilon).
// No automatic normalization. Both moments take O(N) time and O(1) extra space.
template<class T> T expectation(const vector<T>& pmf){
    distribution_detail::check_pmf(pmf); T result = 0;
    for (size_t i = 0; i < pmf.size(); ++i) result += T((long long)i) * pmf[i];
    return result;
}
template<class T> T variance(const vector<T>& pmf){
    T mean = expectation(pmf), result = 0;
    for (size_t i = 0; i < pmf.size(); ++i){ T difference = T((long long)i) - mean; result += pmf[i] * difference * difference; }
    return result;
}

// Solves E = immediate + weighted_other + stay*E; not a general cyclic solver.
// Modular division requires a field and a nonzero denominator.
template<class T> T self_loop_expectation(T immediate, T weighted_other, T stay){
    distribution_detail::check_probability(stay);
    if constexpr (is_floating_point_v<T>){
        if (!isfinite(immediate) || !isfinite(weighted_other)) throw invalid_argument("expected-value terms must be finite");
    }
    if (stay == T(1)) throw domain_error("self-loop equation has zero denominator");
    T result = (immediate + weighted_other) / (T(1) - stay);
    if constexpr (is_floating_point_v<T>) if (!isfinite(result)) throw overflow_error("expected value exceeds the floating-point range");
    return result;
}
} // namespace cp_probability

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return 0;
}
