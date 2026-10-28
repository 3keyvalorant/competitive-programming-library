#pragma once
#include "modint.hpp"

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

template<int MOD, int PrimitiveRoot = 3, bool Fast = (MOD > 1 && MOD < (1 << 30) && (MOD & 1))>
void ntt(vector<ModInt<MOD,Fast>>& a, bool inverse){ convolution_detail::ntt<ModInt<MOD,Fast>,PrimitiveRoot>(a, inverse); }

template<int MOD, int PrimitiveRoot = 3, bool Fast = (MOD > 1 && MOD < (1 << 30) && (MOD & 1))>
vector<ModInt<MOD,Fast>> convolution(vector<ModInt<MOD,Fast>> a, vector<ModInt<MOD,Fast>> b){
    return convolution_detail::convolution<ModInt<MOD,Fast>,PrimitiveRoot>(move(a), move(b));
}

// Reuses the forward transform: two NTTs instead of three for a*a.
template<int MOD, int PrimitiveRoot = 3, bool Fast = (MOD > 1 && MOD < (1 << 30) && (MOD & 1))>
vector<ModInt<MOD,Fast>> convolution_square(vector<ModInt<MOD,Fast>> a){
    return convolution_detail::square<ModInt<MOD,Fast>,PrimitiveRoot>(move(a));
}

