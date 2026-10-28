#include "../library/convolution/exact.hpp"

template<class Exception, class Fn> void expect_throw(Fn fn){
    bool thrown = false;
    try { fn(); } catch (const Exception&) { thrown = true; }
    assert(thrown);
}

vector<long long> brute_ll(const vector<long long>& a, const vector<long long>& b){
    if (a.empty() || b.empty()) return {};
    vector<__int128> sums(a.size() + b.size() - 1);
    for (size_t i = 0; i < a.size(); ++i) for (size_t j = 0; j < b.size(); ++j) sums[i + j] += (__int128)a[i] * b[j];
    vector<long long> result(sums.size());
    for (size_t i = 0; i < sums.size(); ++i) result[i] = cp_transform::exact_detail::checked_long_long(sums[i]);
    return result;
}
vector<int> brute_mod(const vector<long long>& a, const vector<long long>& b, int modulus){
    if (a.empty() || b.empty()) return {};
    vector<int> result(a.size() + b.size() - 1);
    for (size_t i = 0; i < a.size(); ++i) for (size_t j = 0; j < b.size(); ++j){
        __int128 value = (__int128)a[i] * b[j] % modulus;
        value = (value + result[i + j]) % modulus;
        if (value < 0) value += modulus;
        result[i + j] = value;
    }
    return result;
}
int main(){
    using cp_transform::convolution_ll; using cp_transform::convolution_mod;
    assert(ModInt<167772161>(3).pow((167772161 - 1) / 2).val() != 1);
    assert(ModInt<167772161>(3).pow((167772161 - 1) / 5).val() != 1);
    assert(ModInt<469762049>(3).pow((469762049 - 1) / 2).val() != 1);
    assert(ModInt<469762049>(3).pow((469762049 - 1) / 7).val() != 1);
    assert(ModInt<754974721>(11).pow((754974721 - 1) / 2).val() != 1);
    assert(ModInt<754974721>(11).pow((754974721 - 1) / 3).val() != 1);
    assert(ModInt<754974721>(11).pow((754974721 - 1) / 5).val() != 1);
    assert(cp_transform::exact_detail::restore(167772160, 469762048, 754974720) == cp_transform::exact_detail::PRODUCT - 1);
    assert(convolution_ll({}, {1}).empty());
    assert(convolution_mod({1}, {}, 7).empty());
    assert(convolution_ll({1, 2, 3}, {4, 5}) == vector<long long>({4, 13, 22, 15}));
    assert(convolution_ll({LLONG_MIN}, {1}) == vector<long long>({LLONG_MIN}));
    assert(convolution_ll({LLONG_MAX}, {1}) == vector<long long>({LLONG_MAX}));
    assert(convolution_ll({LLONG_MIN}, {0}) == vector<long long>({0}));
    assert(convolution_ll({LLONG_MAX, LLONG_MAX}, {1, -1}) == vector<long long>({LLONG_MAX, 0, -LLONG_MAX}));
    expect_throw<overflow_error>([]{ convolution_ll({LLONG_MIN}, {-1}); });
    expect_throw<overflow_error>([]{ convolution_ll({LLONG_MAX}, {2}); });
    expect_throw<overflow_error>([]{ convolution_ll({LLONG_MAX, LLONG_MAX}, {1, 1}); });
    expect_throw<overflow_error>([]{ convolution_ll(vector<long long>(33, LLONG_MAX), vector<long long>(33, LLONG_MAX)); });
    expect_throw<invalid_argument>([]{ convolution_mod({}, {}, 0); });
    expect_throw<invalid_argument>([]{ convolution_mod({1}, {1}, -1); });
    expect_throw<length_error>([]{ cp_transform::exact_detail::output_size((size_t(1) << 24), 2); });
    assert(cp_transform::exact_detail::output_size((size_t(1) << 24), 1) == (size_t(1) << 24));
    mt19937_64 rng(20261028);
    for (int trial = 0; trial < 350; ++trial){
        int n = rng() % 100, m = rng() % 100;
        vector<long long> a(n), b(m);
        for (auto& x : a) x = (long long)(rng() % 2000001) - 1000000;
        for (auto& x : b) x = (long long)(rng() % 2000001) - 1000000;
        assert(convolution_ll(a, b) == brute_ll(a, b));
        int modulus = trial % 3 == 0 ? 1000000007 : trial % 3 == 1 ? INT_MAX : 12;
        assert(convolution_mod(a, b, modulus) == brute_mod(a, b, modulus));
    }
    for (int n : {33, 64, 97}){
        vector<long long> a(n);
        for (auto& x : a) x = (long long)(rng() % 2001) - 1000;
        assert(convolution_ll(a, a) == brute_ll(a, a));
        auto separate = a;
        assert(convolution_ll(a, separate) == convolution_ll(a, a));
    }
    for (int modulus : {1, 2, 12, 998244353, 1000000007, INT_MAX}){
        vector<long long> a(65), b(67);
        for (size_t i = 0; i < a.size(); ++i) a[i] = i % 2 ? LLONG_MIN : LLONG_MAX;
        for (size_t i = 0; i < b.size(); ++i) b[i] = i % 3 ? LLONG_MIN : LLONG_MAX;
        assert(convolution_mod(a, b, modulus) == brute_mod(a, b, modulus));
    }
    vector<long long> ones(40, 1), edge(40); edge[17] = LLONG_MIN;
    auto result = convolution_ll(edge, ones);
    for (int i = 0; i < 79; ++i) assert(result[i] == (17 <= i && i < 57 ? LLONG_MIN : 0));
    edge[17] = LLONG_MAX; result = convolution_ll(edge, ones);
    for (int i = 0; i < 79; ++i) assert(result[i] == (17 <= i && i < 57 ? LLONG_MAX : 0));
    vector<long long> a(90, 1000000000), b(100, -1000000000);
    expect_throw<overflow_error>([&]{ convolution_ll(a, b); });
    cout << "exact convolution tests passed\n";
}
