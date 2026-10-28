#include "../library/math/combination.hpp"
#include "../library/math/convolution.hpp"

template<int MOD> void check_modint(){
    using T = ModInt<MOD>;
    auto normalize = [](long long x){ long long r = x % MOD; return r < 0 ? r + MOD : r; };
    auto multiply = [](long long a, long long b){ return (long long)((__int128)a * b % MOD); };
    auto check_pair = [&](long long x, long long y){
        T a(x), b(y); long long av = normalize(x), bv = normalize(y);
        assert(a.val() == av && b.val() == bv && a.v == av);
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
    stringstream stream; stream << T(-1) << ' ' << LLONG_MIN;
    T a, b; stream >> a >> b;
    assert(a.val() == normalize(-1) && b.val() == normalize(LLONG_MIN));
}

int main(){
    check_modint<1>(); check_modint<2>(); check_modint<7>(); check_modint<12>();
    check_modint<998244353>(); check_modint<1000000007>();
    check_modint<1073741824>(); check_modint<2147483646>(); check_modint<INT_MAX>();
    combination<mint> co(1000);
    vector<long long> row(1002); row[0] = 1;
    for (int n = 0; n <= 1000; ++n){
        for (int r = 0; r <= n; ++r) assert(co.C(n, r).val() == row[r]);
        for (int r = n + 1; r > 0; --r) row[r] = (row[r] + row[r - 1]) % mint::mod();
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
    }
    cout << "modint tests passed\n";
}
