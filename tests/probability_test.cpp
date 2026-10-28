#include "../library/probability/distribution.hpp"
#include "../library/math/montgomery_modint.hpp"

using namespace cp_probability;

template<class T> bool close_value(T a, T b){
    if constexpr (is_floating_point_v<T>) return fabsl((long double)a - b) <= 1e-9L * (1 + fabsl((long double)b));
    else return a == b;
}
template<class Exception, class F> void expect_error(F f){
    bool caught = false; try { f(); } catch (const Exception&) { caught = true; } assert(caught);
}
template<class T> void check_distributions(){
    mt19937 rng(20261028);
    for (int trial = 0; trial < 120; ++trial){
        int n = rng() % 11; vector<T> p(n);
        for (auto& x : p){ int denominator = 2 + rng() % 7; x = T(rng() % (denominator + 1)) / T(denominator); }
        vector<T> want(n + 1);
        for (int mask = 0; mask < (1 << n); ++mask){
            T probability = 1;
            for (int i = 0; i < n; ++i) probability *= (mask >> i & 1) ? p[i] : T(1) - p[i];
            want[__builtin_popcount((unsigned)mask)] += probability;
        }
        auto got = bernoulli_sum_distribution(p); T want_mean = 0, want_variance = 0, total = 0;
        for (T x : p){ want_mean += x; want_variance += x * (T(1) - x); }
        for (int k = 0; k <= n; ++k){ assert(close_value(got[k], want[k])); total += got[k]; }
        assert(close_value(total, T(1)));
        assert(close_value(expectation(got), want_mean));
        assert(close_value(variance(got), want_variance));
    }
    for (int n = 0; n <= 60; ++n) for (int numerator : {0, 1, 3, 6, 7}){
        T p = T(numerator) / T(7); auto got = cp_probability::binomial_distribution(n, p);
        auto want = bernoulli_sum_distribution(vector<T>(n, p));
        for (int k = 0; k <= n; ++k) assert(close_value(got[k], want[k]));
        assert(close_value(expectation(got), T(n) * p));
        assert(close_value(variance(got), T(n) * p * (T(1) - p)));
    }
    assert(close_value(self_loop_expectation(T(1), T(0), T(1) / T(2)), T(2)));
    assert(close_value(self_loop_expectation(T(2), T(3), T(1) / T(4)), T(20) / T(3)));
    expect_error<invalid_argument>([]{ cp_probability::binomial_distribution(-1, T(0)); });
    expect_error<invalid_argument>([]{ expectation(vector<T>{}); });
    expect_error<invalid_argument>([]{ variance(vector<T>{T(0)}); });
    expect_error<domain_error>([]{ self_loop_expectation(T(1), T(0), T(1)); });
}

int main(){
    check_distributions<mint>(); check_distributions<fastmint>();
    check_distributions<long double>(); check_distributions<double>();
    auto broad = cp_probability::binomial_distribution(10000, 0.5L);
    assert(broad[5000] > 0 && close_value(expectation(broad), 5000.0L) && close_value(variance(broad), 2500.0L));
    for (long double p : {1e-30L, 1 - 1e-18L}){
        auto distribution = cp_probability::binomial_distribution(100, p);
        assert(close_value(expectation(distribution), 100 * p));
    }
    vector<long double> near_deterministic(100001); near_deterministic[100000] = 1 - 1e-12L; near_deterministic[99999] = 1e-12L;
    long double v = variance(near_deterministic);
    assert(v >= 0 && fabsl(v - 1e-12L * (1 - 1e-12L)) < 1e-20L);
    using m7 = ModInt<7>;
    for (int n = 0; n < 7; ++n) for (int p = 0; p < 7; ++p)
        assert(cp_probability::binomial_distribution(n, m7(p)) == bernoulli_sum_distribution(vector<m7>(n, m7(p))));
    expect_error<invalid_argument>([]{ cp_probability::binomial_distribution(7, m7(2)); });
    auto certain = cp_probability::binomial_distribution(10, m7(1)), impossible = cp_probability::binomial_distribution(10, m7(0));
    assert(certain.size() == 11 && certain[10] == m7(1) && impossible[0] == m7(1));
    for (long double invalid : {-0.01L, 1.01L, numeric_limits<long double>::infinity(), numeric_limits<long double>::quiet_NaN()}){
        expect_error<invalid_argument>([&]{ cp_probability::binomial_distribution(3, invalid); });
        expect_error<invalid_argument>([&]{ bernoulli_sum_distribution(vector<long double>{invalid}); });
        expect_error<invalid_argument>([&]{ self_loop_expectation(1.0L, 0.0L, invalid); });
    }
    expect_error<invalid_argument>([]{ expectation(vector<long double>{0.2L, 0.3L}); });
    expect_error<invalid_argument>([]{ expectation(vector<long double>{-0.1L, 1.1L}); });
    expect_error<invalid_argument>([]{ expectation(vector<mint>{mint(2), mint(3)}); });
    expect_error<invalid_argument>([]{ self_loop_expectation(numeric_limits<long double>::infinity(), 0.0L, 0.5L); });
    cout << "probability tests passed\n";
}
