#pragma once
#include "modint.hpp"

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
        if (n < (long long)fact.size()) return fact[n] * ifact[r] * ifact[n - r];
        r = min(r, n - r); T res = 1;
        for (long long i = 1; i <= r; ++i) res *= T(n - r + i), res /= T(i);
        return res;
    }
    T get(long long n, long long r) const {
        if (r < 0 || n < r) return 0;
        const long long modulus = T::mod(); T res = 1;
        while (n || r){ long long ni = n % modulus, ri = r % modulus; if (ni < ri) return 0; res *= small_C(ni, ri); n /= modulus; r /= modulus; }
        return res;
    }
    T C(long long n, long long r) const { return get(n, r); }
    T permutation(long long n, long long r) const {
        if (r < 0 || n < r) return 0;
        const long long modulus = T::mod(); if (r >= modulus || (n >= modulus && r > n % modulus)) return 0;
        if (n < (long long)fact.size()) return fact[n] * ifact[n - r];
        T res = 1; for (long long i = 0; i < r; ++i) res *= T(n - i); return res;
    }
    T P(long long n, long long r) const { return permutation(n, r); }
    T calu(long long n, long long r) const { return get(n, r); }
};
