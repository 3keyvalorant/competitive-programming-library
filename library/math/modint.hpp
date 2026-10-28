#pragma once
#include "../basic/base.hpp"

template<int MOD, bool UseMontgomery = (MOD > 1 && MOD < (1 << 30) && (MOD & 1))>
class ModInt {
    static_assert(MOD > 0, "ModInt requires a positive modulus");
    static_assert(!UseMontgomery || (MOD > 1 && MOD < (1 << 30) && (MOD & 1)), "Montgomery requires odd 1 < MOD < 2^30");
    using u32 = uint32_t;
    using u64 = uint64_t;
    u32 x = 0;
    static constexpr u32 RANGE = UseMontgomery ? 2u * MOD : (u32)MOD;
    static constexpr u32 negative_inverse(){
        u32 r = MOD;
        for (int i = 0; i < 5; ++i) r *= 2u - (u32)MOD * r;
        return 0u - r;
    }
    static constexpr u32 R2 = (0ull - (u64)MOD) % MOD;
    // Lazy Montgomery residues stay in [0,2*MOD); the fallback stays in [0,MOD).
    static u32 reduce(u64 t){ return (t + (u64)(u32)((u32)t * negative_inverse()) * MOD) >> 32; }
public:
    ModInt() = default;
    ModInt(long long value){
        long long r = value % MOD; if (r < 0) r += MOD;
        if constexpr (UseMontgomery) x = reduce((u64)r * R2);
        else x = (u32)r;
    }
    static constexpr int mod(){ return MOD; }
    static ModInt raw(int value){
        assert(0 <= value && value < MOD);
        ModInt r;
        if constexpr (UseMontgomery) r.x = reduce((u64)value * R2);
        else r.x = (u32)value;
        return r;
    }
    int val() const {
        if constexpr (UseMontgomery){ u32 r = reduce(x); return r >= MOD ? r - MOD : r; }
        else return x;
    }
    ModInt& operator+=(const ModInt& o){ x += o.x; if (x >= RANGE) x -= RANGE; return *this; }
    ModInt& operator-=(const ModInt& o){ x += RANGE - o.x; if (x >= RANGE) x -= RANGE; return *this; }
    ModInt& operator*=(const ModInt& o){
        if constexpr (UseMontgomery) x = reduce((u64)x * o.x);
        else x = (u64)x * o.x % MOD;
        return *this;
    }
    ModInt& operator/=(const ModInt& o){ return *this *= o.inv(); }
    ModInt pow(long long n) const { assert(n >= 0); ModInt a = *this, r = 1; while (n){ if (n & 1) r *= a; a *= a; n >>= 1; } return r; }
    ModInt inv() const {
        int a = val(), b = MOD; long long coefficient = 1, next = 0;
        while (b){ int q = a / b; a -= q * b; swap(a, b); coefficient -= q * next; swap(coefficient, next); }
        assert(a == 1);
        // Euclid's coefficient is in (-MOD, MOD), so no remainder is needed.
        return raw((int)(coefficient < 0 ? coefficient + MOD : coefficient));
    }
    friend ModInt operator+(ModInt a, const ModInt& b){ return a += b; }
    friend ModInt operator-(ModInt a, const ModInt& b){ return a -= b; }
    friend ModInt operator*(ModInt a, const ModInt& b){ return a *= b; }
    friend ModInt operator/(ModInt a, const ModInt& b){ return a /= b; }
    friend bool operator==(const ModInt& a, const ModInt& b){
        if constexpr (UseMontgomery) return (a.x >= MOD ? a.x - MOD : a.x) == (b.x >= MOD ? b.x - MOD : b.x);
        else return a.x == b.x;
    }
    friend bool operator!=(const ModInt& a, const ModInt& b){ return !(a == b); }
    friend ostream& operator<<(ostream& os, const ModInt& x){ return os << x.val(); }
    friend istream& operator>>(istream& is, ModInt& x){ long long value; if (is >> value) x = ModInt(value); return is; }
};
template<int MOD> using BasicModInt = ModInt<MOD,false>;
template<int MOD> using MontgomeryModInt = ModInt<MOD,true>;
using mint = ModInt<998244353>;
using amint = ModInt<1000000007>;
using fastmint = mint;
using fastamint = amint;

