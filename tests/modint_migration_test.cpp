#include "../library/math/modint.hpp"

// These names must work with modint.hpp alone, including old fast-type names.
static_assert(is_same_v<mint, ModInt<998244353>>);
static_assert(is_same_v<amint, ModInt<1000000007>>);
static_assert(is_same_v<mint, fastmint> && is_same_v<amint, fastamint>);
static_assert(is_same_v<mint, MontgomeryModInt<998244353>>);
static_assert(is_same_v<ModInt<1>, BasicModInt<1>>);
static_assert(is_same_v<ModInt<2>, BasicModInt<2>>);
static_assert(is_same_v<ModInt<1073741823>, MontgomeryModInt<1073741823>>);
static_assert(is_same_v<ModInt<2013265921>, BasicModInt<2013265921>>);
static_assert(!is_same_v<mint, BasicModInt<998244353>>);
static_assert(sizeof(mint) == sizeof(uint32_t));

#include "../library/math/convolution.hpp"
#include "../library/math/montgomery_modint.hpp" // Legacy include must remain usable.

long long normalize_reference(long long value, int modulus){
    long long result = value % modulus;
    return result < 0 ? result + modulus : result;
}
long long multiply_reference(long long a, long long b, int modulus){
    return (long long)((__int128)a * b % modulus);
}
long long power_reference(long long a, long long exponent, int modulus){
    long long result = 1 % modulus;
    while (exponent){
        if (exponent & 1) result = multiply_reference(result, a, modulus);
        a = multiply_reference(a, a, modulus); exponent >>= 1;
    }
    return result;
}

template<class T> void check_arithmetic(){
    constexpr int MOD = T::mod();
    vector<long long> edges{LLONG_MIN, LLONG_MIN + 1, INT_MIN, -2LL * MOD,
                           -MOD, -1, 0, 1, MOD - 1, MOD, 2LL * MOD,
                           INT_MAX, LLONG_MAX - 1, LLONG_MAX};
    for (long long value : edges){
        long long expected = normalize_reference(value, MOD);
        T a(value); assert(a.val() == expected && a == T::raw((int)expected));
        T twice = a; twice += twice;
        assert(twice.val() == (2 * expected) % MOD);
        T zero = a; zero -= zero; assert(zero.val() == 0);
        T square = a; square *= square;
        assert(square.val() == multiply_reference(expected, expected, MOD));
        for (long long exponent : {0LL, 1LL, 2LL, 17LL, LLONG_MAX})
            assert(a.pow(exponent).val() == power_reference(expected, exponent, MOD));
        if (gcd(expected, (long long)MOD) == 1){
            assert(multiply_reference(expected, a.inv().val(), MOD) == 1 % MOD);
            T one = a; one /= one; assert(one.val() == 1 % MOD);
        }
    }
    mt19937_64 rng(20261028);
    T actual = 1; long long expected = 1 % MOD;
    for (int step = 0; step < 3000; ++step){
        long long value = (long long)(rng() >> 1);
        if (rng() & 1) value = -value;
        long long residue = normalize_reference(value, MOD);
        switch (step % 5){
            case 0: actual += T(value); expected = (expected + residue) % MOD; break;
            case 1: actual -= T(value); expected = (expected - residue + MOD) % MOD; break;
            case 2: actual *= T(value); expected = multiply_reference(expected, residue, MOD); break;
            case 3:
                if (gcd(residue, (long long)MOD) == 1){
                    T inverse = T(value).inv();
                    assert(multiply_reference(residue, inverse.val(), MOD) == 1 % MOD);
                    actual /= T(value); expected = multiply_reference(expected, inverse.val(), MOD);
                }
                break;
            default: actual = T::raw((int)residue); expected = residue; break;
        }
        assert(actual.val() == expected && actual == T(expected));
    }
    stringstream roundtrip; roundtrip << T(-1) << ' ' << LLONG_MIN;
    T a, b; roundtrip >> a >> b;
    assert(a == T(-1) && b == T(LLONG_MIN));
    for (const char* text : {"", "not-an-integer", "9223372036854775808"}){
        istringstream input(text); T unchanged = 42;
        input >> unchanged;
        assert(input.fail() && unchanged == T(42));
    }
}

template<class T, int Root = 3> void check_convolution_calls(){
    constexpr int MOD = T::mod();
    mt19937 rng(20261028);
    vector<T> a(45), b(52);
    for (auto& x : a) x = (int)(rng() % 2001) - 1000;
    for (auto& x : b) x = (int)(rng() % 2001) - 1000;
    vector<T> want(a.size() + b.size() - 1), want_square(a.size() * 2 - 1);
    for (size_t i = 0; i < a.size(); ++i){
        for (size_t j = 0; j < b.size(); ++j)
            want[i + j] = (want[i + j].val() + multiply_reference(a[i].val(), b[j].val(), MOD)) % MOD;
        for (size_t j = 0; j < a.size(); ++j)
            want_square[i + j] = (want_square[i + j].val() + multiply_reference(a[i].val(), a[j].val(), MOD)) % MOD;
    }
    assert((convolution<MOD,Root>(a,b) == want));
    assert((convolution_square<MOD,Root>(a) == want_square));
    if constexpr (Root == 3){
        assert(convolution(a,b) == want);
        assert(convolution_square(a) == want_square);
    }
    vector<T> transformed(128);
    copy(a.begin(), a.end(), transformed.begin()); auto original = transformed;
    ntt<MOD,Root>(transformed, false); ntt<MOD,Root>(transformed, true);
    assert(transformed == original);
}

int main(){
    check_arithmetic<mint>(); check_arithmetic<amint>();
    check_arithmetic<BasicModInt<998244353>>(); check_arithmetic<ModInt<9>>();
    check_arithmetic<ModInt<1073741823>>();
    check_arithmetic<ModInt<1>>(); check_arithmetic<ModInt<2>>();
    check_arithmetic<ModInt<1073741824>>(); check_arithmetic<ModInt<2147483646>>();
    check_arithmetic<ModInt<INT_MAX>>();
    vector<fastmint> old_name{1, 2, 3}; vector<mint> usual_name = old_name;
    assert(usual_name == old_name);
    check_convolution_calls<mint>();
    check_convolution_calls<BasicModInt<998244353>>();
    check_convolution_calls<ModInt<2013265921>,31>();
    cout << "modint migration tests passed\n";
}
