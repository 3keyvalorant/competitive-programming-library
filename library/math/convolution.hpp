#pragma once
#include "modint.hpp"

template<int MOD, int PrimitiveRoot = 3>
void ntt(vector<ModInt<MOD>>& a, bool inverse){
    int n = a.size(); assert(n && (n & (n - 1)) == 0 && (MOD - 1) % n == 0);
    for (int i = 1, j = 0; i < n; ++i){
        int bit = n >> 1; for (; j & bit; bit >>= 1) j ^= bit; j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1){
        ModInt<MOD> root = ModInt<MOD>(PrimitiveRoot).pow((MOD - 1) / len); if (inverse) root = root.inv();
        for (int i = 0; i < n; i += len){ ModInt<MOD> w = 1; for (int j = 0; j < len / 2; ++j){ auto u = a[i+j], v = a[i+j+len/2] * w; a[i+j] = u + v; a[i+j+len/2] = u - v; w *= root; } }
    }
    if (inverse){ ModInt<MOD> inv_n = ModInt<MOD>(n).inv(); for (auto& x : a) x *= inv_n; }
}

template<int MOD, int PrimitiveRoot = 3>
vector<ModInt<MOD>> convolution(vector<ModInt<MOD>> a, vector<ModInt<MOD>> b){
    if (a.empty() || b.empty()) return {};
    if (min(a.size(), b.size()) <= 32){ vector<ModInt<MOD>> c(a.size() + b.size() - 1); for (int i = 0; i < (int)a.size(); ++i) for (int j = 0; j < (int)b.size(); ++j) c[i+j] += a[i] * b[j]; return c; }
    int need = a.size() + b.size() - 1, n = 1; while (n < need) n <<= 1; assert((MOD - 1) % n == 0);
    a.resize(n); b.resize(n); ntt<MOD,PrimitiveRoot>(a, false); ntt<MOD,PrimitiveRoot>(b, false); for (int i = 0; i < n; ++i) a[i] *= b[i]; ntt<MOD,PrimitiveRoot>(a, true); a.resize(need); return a;
}

