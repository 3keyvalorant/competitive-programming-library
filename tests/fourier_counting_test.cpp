#include "../library/convolution/fft.hpp"
#include "../library/convolution/counting.hpp"

using namespace cp_transform;

template<class Exception, class F> void expect_error(F f){
    bool caught = false;
    try { f(); } catch (const Exception&) { caught = true; }
    assert(caught);
}

int main(){
    mt19937 rng(20261028);
    auto close = [](long double a, long double b){ return fabsl(a - b) <= 1e-8L * (1 + fabsl(b)); };
    for (int n : {1, 2, 4, 8, 16, 64}){
        vector<complex<long double>> a(n), want(n);
        for (auto& x : a) x = {(long double)(int)(rng() % 11) - 5, (long double)(int)(rng() % 11) - 5};
        auto before = a;
        for (int k = 0; k < n; ++k) for (int j = 0; j < n; ++j){
            long double angle = -2 * acosl(-1.0L) * j * k / n;
            want[k] += a[j] * complex<long double>(cosl(angle), sinl(angle));
        }
        fft(a);
        for (int k = 0; k < n; ++k) assert(abs(a[k] - want[k]) < 1e-8L);
        fft(a, true);
        for (int i = 0; i < n; ++i) assert(abs(a[i] - before[i]) < 1e-8L);
    }
    vector<complex<long double>> empty; fft(empty); assert(empty.empty());
    expect_error<invalid_argument>([]{ vector<complex<long double>> a(3); fft(a); });
    for (int trial = 0; trial < 100; ++trial){
        int n = rng() % 91, m = rng() % 91;
        vector<long double> a(n), b(m), want(n && m ? n + m - 1 : 0);
        for (auto& x : a) x = ((int)(rng() % 101) - 50) / 7.0L;
        for (auto& x : b) x = ((int)(rng() % 101) - 50) / 9.0L;
        for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) want[i + j] += a[i] * b[j];
        auto got = convolution_real(a, b);
        assert(got.size() == want.size());
        for (size_t i = 0; i < want.size(); ++i) assert(close(got[i], want[i]));
    }
    for (int trial = 0; trial < 200; ++trial){
        int n = rng() % 31, m = rng() % 31;
        vector<int> a(n), b(m);
        for (auto& x : a) x = rng() % 41;
        for (auto& x : b) x = rng() % 41;
        vector<long long> want(n && m ? *max_element(a.begin(), a.end()) + *max_element(b.begin(), b.end()) + 1 : 0);
        for (int x : a) for (int y : b) ++want[x + y];
        assert(pair_sum_counts(a, b) == want);
        vector<long long> unordered_want(n ? 2 * *max_element(a.begin(), a.end()) + 1 : 0);
        for (int i = 0; i < n; ++i) for (int j = i + 1; j < n; ++j) ++unordered_want[a[i] + a[j]];
        assert(unordered_pair_sum_counts(a) == unordered_want);
    }
    vector<int> zeros(100000);
    assert(pair_sum_counts(zeros, zeros) == vector<long long>{10000000000LL});
    assert(unordered_pair_sum_counts(zeros) == vector<long long>{4999950000LL});
    expect_error<invalid_argument>([]{ pair_sum_counts({-1}, {0}); });
    expect_error<invalid_argument>([]{ pair_sum_counts({}, {-1}); });
    expect_error<invalid_argument>([]{ unordered_pair_sum_counts({-1}); });
    expect_error<length_error>([]{ pair_sum_counts({INT_MAX}, {0}); });
    expect_error<length_error>([]{ unordered_pair_sum_counts({INT_MAX}); });
    for (int trial = 0; trial < 100; ++trial){
        int n = rng() % 81, picks = rng() % 7, max_sum = rng() % 151;
        vector<long long> ways(n); for (auto& x : ways) x = rng() % 4;
        vector<mint> want(max_sum + 1); want[0] = 1;
        for (int p = 0; p < picks; ++p){
            vector<mint> next(max_sum + 1);
            for (int s = 0; s <= max_sum; ++s) for (int v = 0; v < n && s + v <= max_sum; ++v) next[s + v] += want[s] * ways[v];
            want = move(next);
        }
        assert(sum_distribution_mod(ways, picks, max_sum) == want);
    }
    assert(sum_distribution_mod({}, 0, 3) == vector<mint>({1, 0, 0, 0}));
    assert(sum_distribution_mod({}, 5, 3) == vector<mint>({0, 0, 0, 0}));
    assert(sum_distribution_mod({0, 1}, 3, 2) == vector<mint>({0, 0, 0}));
    assert(sum_distribution_mod({2}, LLONG_MAX, 0) == vector<mint>({mint(2).pow(LLONG_MAX)}));
    assert(sum_distribution_mod({LLONG_MAX}, 1, 0) == vector<mint>({mint(LLONG_MAX)}));
    expect_error<invalid_argument>([]{ sum_distribution_mod({1}, -1, 0); });
    expect_error<invalid_argument>([]{ sum_distribution_mod({1}, 0, -1); });
    expect_error<invalid_argument>([]{ sum_distribution_mod({1, -1}, 0, 0); });
    expect_error<length_error>([]{ sum_distribution_mod({1}, 1, INT_MAX); });
    cout << "fourier/counting tests passed\n";
}
