#pragma once
#include "modint.hpp"

template<class T> struct combination {
    vector<T> fact, ifact;
    combination(int n = 0){ reset(n); }
    void reset(int n){
        fact.assign(n + 1, 1); ifact.assign(n + 1, 1);
        for (int i = 1; i <= n; ++i) fact[i] = fact[i - 1] * i;
        if (n){ ifact[n] = fact[n].inv(); for (int i = n; i; --i) ifact[i - 1] = ifact[i] * i; }
    }
    T get(int n, int r) const { return r < 0 || n < r || n >= (int)fact.size() ? T(0) : fact[n] * ifact[r] * ifact[n - r]; }
    T C(int n, int r) const { return get(n, r); }
    T permutation(int n, int r) const { return r < 0 || n < r || n >= (int)fact.size() ? T(0) : fact[n] * ifact[n - r]; }
    T P(int n, int r) const { return permutation(n, r); }
    T calu(int n, int r) const { return get(n, r); }
};

