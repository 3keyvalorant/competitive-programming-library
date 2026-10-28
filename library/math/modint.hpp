#pragma once
#include "../basic/base.hpp"

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

