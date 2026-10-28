#pragma once
#include "../math/convolution.hpp"

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
