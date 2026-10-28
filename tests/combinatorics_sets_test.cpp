#include "../library/math/combination.hpp"
#include "../library/math/subset_transform.hpp"

template<class Exception, class F> void expect_exception(F fn){
    bool caught = false;
    try { fn(); } catch (const Exception&) { caught = true; }
    assert(caught);
}

template<int MOD> void check_combinatorics(){
    using T = ModInt<MOD>;
    combination<T> table(min(100, MOD - 1)), sparse(1000000000LL);
    for (int types = 0; types <= 8; ++types){
        vector<long long> ways(21); ways[0] = 1;
        for (int i = 0; i < types; ++i) for (int r = 1; r <= 20; ++r) ways[r] += ways[r - 1];
        for (int r = 0; r <= 20; ++r){
            assert(table.H(types, r) == T(ways[r]));
            assert(sparse.H(types, r) == T(ways[r]));
        }
    }
    for (int groups = 0; groups <= 4; ++groups){
        int configurations = 1 << (2 * groups);
        for (int mask = 0; mask < configurations; ++mask){
            vector<long long> counts(groups); int total = 0;
            for (int i = 0; i < groups; ++i){ counts[i] = (mask >> (2 * i)) & 3; total += counts[i]; }
            long long numerator = 1, denominator = 1;
            for (int i = 2; i <= total; ++i) numerator *= i;
            for (long long count : counts) for (int i = 2; i <= count; ++i) denominator *= i;
            T want(numerator / denominator);
            assert(table.multinomial(counts) == want && sparse.multinomial(counts) == want);
        }
    }
    assert(table.H(-1, 0) == T(0) && table.H(0, -1) == T(0));
    assert(sparse.H(LLONG_MAX, 0) == T(1));
    assert(sparse.H(LLONG_MAX, 1) == T(LLONG_MAX));
    assert(sparse.H(1, LLONG_MAX) == T(1));
    expect_exception<overflow_error>([&]{ sparse.H(2, LLONG_MAX); });
    assert(sparse.multinomial({}) == T(1));
    assert(sparse.multinomial({0, 0}) == T(1));
    assert(sparse.multinomial({LLONG_MAX}) == T(1));
    assert(sparse.multinomial({0, LLONG_MAX, 0}) == T(1));
    assert(sparse.multinomial({LLONG_MAX - 1, 1}) == T(LLONG_MAX));
    assert(sparse.multinomial({LLONG_MAX, LLONG_MAX, -1}) == T(0));
    expect_exception<overflow_error>([&]{ sparse.multinomial({LLONG_MAX, 1}); });
}

template<class T> void check_subsets(){
    using namespace cp_subset;
    mt19937 rng(20261028);
    vector<T> empty;
    subset_zeta(empty); subset_mobius(empty); superset_zeta(empty); superset_mobius(empty);
    assert(bitwise_or_convolution(empty, empty).empty() && bitwise_and_convolution(empty, empty).empty());
    for (int bits = 0; bits <= 7; ++bits){
        int n = 1 << bits;
        for (int trial = 0; trial < 20; ++trial){
            vector<T> a(n), b(n), sub(n), super(n), want_or(n), want_and(n);
            for (auto& x : a) x = (int)(rng() % 21) - 10;
            for (auto& x : b) x = (int)(rng() % 21) - 10;
            for (int mask = 0; mask < n; ++mask) for (int s = 0; s < n; ++s){
                if ((s & mask) == s) sub[mask] += a[s];
                if ((s | mask) == s) super[mask] += a[s];
                want_or[mask | s] += a[mask] * b[s];
                want_and[mask & s] += a[mask] * b[s];
            }
            auto got = a; subset_zeta(got); assert(got == sub); subset_mobius(got); assert(got == a);
            got = a; superset_zeta(got); assert(got == super); superset_mobius(got); assert(got == a);
            assert(bitwise_or_convolution(a, b) == want_or);
            assert(bitwise_and_convolution(a, b) == want_and);
        }
    }
    expect_exception<invalid_argument>([]{ vector<T> a(3); subset_zeta(a); });
    expect_exception<invalid_argument>([]{ vector<T> a(3); subset_mobius(a); });
    expect_exception<invalid_argument>([]{ vector<T> a(3); superset_zeta(a); });
    expect_exception<invalid_argument>([]{ vector<T> a(3); superset_mobius(a); });
    expect_exception<invalid_argument>([]{ bitwise_or_convolution(vector<T>(2), vector<T>(4)); });
    expect_exception<invalid_argument>([]{ bitwise_and_convolution(vector<T>{}, vector<T>(1)); });
    expect_exception<invalid_argument>([]{ bitwise_and_convolution(vector<T>(3), vector<T>(3)); });
}

int main(){
    check_combinatorics<2>(); check_combinatorics<7>(); check_combinatorics<998244353>();
    check_subsets<long long>(); check_subsets<mint>();
    cout << "combinatorics and subset tests passed\n";
}
