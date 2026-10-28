#pragma once
#include "../basic/base.hpp"

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
