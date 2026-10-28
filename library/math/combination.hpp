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
