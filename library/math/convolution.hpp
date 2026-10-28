#pragma once
#include "montgomery_modint.hpp"

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

