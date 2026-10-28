#include "../library/math/combination.hpp"
#include "../library/math/convolution.hpp"

template<class T> void check_modint(){
    constexpr int MOD = T::mod();
    auto normalize = [](long long x){ long long r = x % MOD; return r < 0 ? r + MOD : r; };
    auto multiply = [](long long a, long long b){ return (long long)((__int128)a * b % MOD); };
    auto check_pair = [&](long long x, long long y){
        T a(x), b(y); long long av = normalize(x), bv = normalize(y);
        assert(a.val() == av && b.val() == bv);
        assert((a + b).val() == (av + bv) % MOD);
        assert((a - b).val() == (av - bv + MOD) % MOD);
        assert((a * b).val() == multiply(av, bv));
        T c = a; c += c; assert(c.val() == av * 2 % MOD);
        c = a; c -= c; assert(c.val() == 0);
        c = a; c *= c; assert(c.val() == multiply(av, av));
        assert((a == b) == (av == bv) && (a != b) == (av != bv));
        if (gcd(bv, (long long)MOD) == 1){
            long long inverse = b.inv().val();
            assert(0 <= inverse && inverse < MOD);
            assert(multiply(bv, inverse) == 1 % MOD);
            assert((a / b).val() == multiply(av, inverse));
        }
    };
    vector<long long> edges{LLONG_MIN, LLONG_MIN + 1, INT_MIN, -2LL * MOD, -MOD, -1,
                           0, 1, MOD - 1, MOD, 2LL * MOD, INT_MAX, LLONG_MAX - 1, LLONG_MAX};
    for (long long x : edges) for (long long y : edges) check_pair(x, y);
    if constexpr (MOD <= 32) for (int a = 0; a < MOD; ++a) for (int b = 0; b < MOD; ++b) check_pair(a, b);
    mt19937_64 rng(20261028);
    for (int i = 0; i < 20000; ++i){
        long long x = (long long)(rng() >> 1), y = (long long)(rng() >> 1);
        if (rng() & 1) x = -x;
        if (rng() & 1) y = -y;
        check_pair(x, y);
        if (i < 1000){
            int exponent = rng() % 100; long long want = 1 % MOD;
            for (int j = 0; j < exponent; ++j) want = multiply(want, normalize(x));
            assert(T(x).pow(exponent).val() == want);
        }
    }
    T running = MOD - 1; long long want_running = MOD - 1;
    for (int i = 0; i < 10000; ++i){
        long long value = rng() % MOD;
        if (i % 3 == 0){ running += T(value); want_running = (want_running + value) % MOD; }
        else if (i % 3 == 1){ running -= T(value); want_running = (want_running - value + MOD) % MOD; }
        else { running *= T(value); want_running = multiply(want_running, value); }
        assert(running.val() == want_running && running == T(want_running));
    }
    stringstream stream; stream << T(-1) << ' ' << LLONG_MIN;
    T a, b; stream >> a >> b;
    assert(a.val() == normalize(-1) && b.val() == normalize(LLONG_MIN));
}

int main(){
    check_modint<ModInt<1>>(); check_modint<ModInt<2>>(); check_modint<ModInt<7>>(); check_modint<ModInt<12>>();
    check_modint<mint>(); check_modint<amint>();
    check_modint<ModInt<1073741824>>(); check_modint<ModInt<2147483646>>(); check_modint<ModInt<INT_MAX>>();
    check_modint<MontgomeryModInt<3>>(); check_modint<MontgomeryModInt<7>>(); check_modint<MontgomeryModInt<9>>();
    check_modint<fastmint>(); check_modint<fastamint>(); check_modint<MontgomeryModInt<1073741823>>();
    assert(mint(-1).v == mint::mod() - 1);
    combination<mint> co(1000);
    vector<long long> row(1002); row[0] = 1;
    for (int n = 0; n <= 1000; ++n){
        for (int r = 0; r <= n; ++r) assert(co.C(n, r).val() == row[r]);
        for (int r = n + 1; r > 0; --r) row[r] = (row[r] + row[r - 1]) % mint::mod();
    }
    combination<fastmint> fast_co(1000);
    combination<mint> large_co(1000000000LL);
    combination<fastmint> fast_large_co(1000000000LL);
    for (int n = 0; n <= 1000; n += 17) for (int r = 0; r <= n; ++r){
        assert(fast_co.C(n, r).val() == co.C(n, r).val());
        assert(large_co.C(n, r) == co.C(n, r));
        assert(fast_large_co.C(n, r).val() == co.C(n, r).val());
    }
    mint old_formula = 1; long long huge_n = 1000000000LL;
    for (int r = 1; r <= 1000; ++r){
        old_formula *= mint(huge_n - r + 1); old_formula /= mint(r);
        assert(large_co.C(huge_n, r) == old_formula);
        assert(fast_large_co.C(huge_n, r).val() == old_formula.val());
    }
    mt19937 rng(20261028);
    for (int trial = 0; trial < 20; ++trial){
        int n = 33 + rng() % 100, m = 33 + rng() % 100;
        vector<mint> a(n), b(m); vector<long long> want(n + m - 1);
        for (auto& x : a) x = rng();
        for (auto& x : b) x = rng();
        for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j)
            want[i + j] = (want[i + j] + (long long)a[i].val() * b[j].val()) % mint::mod();
        auto got = convolution(a, b);
        for (int i = 0; i < (int)want.size(); ++i) assert(got[i].val() == want[i]);
        vector<fastmint> x(n), y(m);
        for (int i = 0; i < n; ++i) x[i] = fastmint::raw(a[i].val());
        for (int i = 0; i < m; ++i) y[i] = fastmint::raw(b[i].val());
        auto fast_got = convolution(x, y);
        for (int i = 0; i < (int)want.size(); ++i) assert(fast_got[i].val() == want[i]);
    }
    assert(convolution(vector<fastmint>{}, vector<fastmint>{1}).empty());
    for (int n : {1, 5, 32}){
        vector<fastmint> a(n, -1), b(80, 1); auto c = convolution(a, b);
        for (int i = 0; i < n + 79; ++i) assert(c[i] == fastmint(-min({i + 1, n, n + 79 - i})));
    }
    assert(fastmint::raw(0) == fastmint(0) && fastmint::raw(fastmint::mod() - 1) == fastmint(-1));
    using small_ntt = ModInt<167772161>;
    vector<small_ntt> small_a(40, -1), small_b(40, 1); auto small_c = convolution(small_a, small_b);
    for (int i = 0; i < 79; ++i) assert(small_c[i] == small_ntt(-min(i + 1, 79 - i)));
    for (int n : {1, 2, 16, 1024}){
        vector<fastmint> a(n);
        for (auto& x : a) x = rng();
        auto before = a; ntt(a, false); ntt(a, true); assert(a == before);
        vector<mint> b(n); for (int i = 0; i < n; ++i) b[i] = a[i].val();
        auto normal_before = b; ntt<998244353>(b, false); ntt<998244353>(b, true); assert(b == normal_before);
    }
    // 2013265921 is outside the Montgomery range: exercise the normal fallback.
    using wide = ModInt<2013265921>;
    vector<wide> a(40, 1), b(40, 1); auto c = convolution<2013265921,31>(a, b);
    for (int i = 0; i < 79; ++i) assert(c[i].val() == min(i + 1, 79 - i));
    cout << "modint tests passed\n";
}
