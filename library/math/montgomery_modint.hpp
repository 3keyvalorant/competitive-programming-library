#pragma once
#include "modint.hpp"

template<int MOD> class MontgomeryModInt {
    static_assert(MOD > 1 && MOD < (1 << 30) && (MOD & 1), "MontgomeryModInt requires odd 1 < MOD < 2^30");
    using u32 = uint32_t;
    using u64 = uint64_t;
    u32 x = 0;
    static constexpr u32 negative_inverse(){
        u32 r = MOD;
        for (int i = 0; i < 5; ++i) r *= 2u - (u32)MOD * r;
        return 0u - r;
    }
    static constexpr u32 R2 = (0ull - (u64)MOD) % MOD;
    // x stays in [0, 2*MOD); MOD < 2^30 keeps products below MOD*2^32.
    static u32 reduce(u64 t){ return (t + (u64)(u32)((u32)t * negative_inverse()) * MOD) >> 32; }
public:
    MontgomeryModInt() = default;
    MontgomeryModInt(long long value){
        long long r = value % MOD; if (r < 0) r += MOD;
        x = reduce((u64)r * R2);
    }
    static constexpr int mod(){ return MOD; }
    static MontgomeryModInt raw(int value){
        assert(0 <= value && value < MOD);
        MontgomeryModInt r; r.x = reduce((u64)value * R2); return r;
    }
    int val() const { u32 r = reduce(x); return r >= MOD ? r - MOD : r; }
    MontgomeryModInt& operator+=(const MontgomeryModInt& o){ x += o.x; if (x >= 2u * MOD) x -= 2u * MOD; return *this; }
    MontgomeryModInt& operator-=(const MontgomeryModInt& o){ x += 2u * MOD - o.x; if (x >= 2u * MOD) x -= 2u * MOD; return *this; }
    MontgomeryModInt& operator*=(const MontgomeryModInt& o){ x = reduce((u64)x * o.x); return *this; }
    MontgomeryModInt& operator/=(const MontgomeryModInt& o){ return *this *= o.inv(); }
    MontgomeryModInt pow(long long n) const {
        assert(n >= 0); MontgomeryModInt a = *this, r = 1;
        while (n){ if (n & 1) r *= a; a *= a; n >>= 1; } return r;
    }
    MontgomeryModInt inv() const { return raw(ModInt<MOD>(val()).inv().val()); }
    friend MontgomeryModInt operator+(MontgomeryModInt a, const MontgomeryModInt& b){ return a += b; }
    friend MontgomeryModInt operator-(MontgomeryModInt a, const MontgomeryModInt& b){ return a -= b; }
    friend MontgomeryModInt operator*(MontgomeryModInt a, const MontgomeryModInt& b){ return a *= b; }
    friend MontgomeryModInt operator/(MontgomeryModInt a, const MontgomeryModInt& b){ return a /= b; }
    friend bool operator==(const MontgomeryModInt& a, const MontgomeryModInt& b){
        return (a.x >= MOD ? a.x - MOD : a.x) == (b.x >= MOD ? b.x - MOD : b.x);
    }
    friend bool operator!=(const MontgomeryModInt& a, const MontgomeryModInt& b){ return !(a == b); }
    friend ostream& operator<<(ostream& os, const MontgomeryModInt& a){ return os << a.val(); }
    friend istream& operator>>(istream& is, MontgomeryModInt& a){ long long value; if (is >> value) a = MontgomeryModInt(value); return is; }
};
using fastmint = MontgomeryModInt<998244353>;
using fastamint = MontgomeryModInt<1000000007>;
