#include "../library/math/convolution.hpp"

template<class T, int Root = 3> void check_square(){
    mt19937 rng(20261028);
    for (int n : {0, 1, 2, 7, 31, 32, 33, 40, 65, 129}){
        for (int trial = 0; trial < 10; ++trial){
            vector<T> a(n); for (auto& x : a) x = (int)(rng() % 2001) - 1000;
            vector<long long> want(n ? 2 * n - 1 : 0);
            for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j)
                want[i + j] = (want[i + j] + (long long)a[i].val() * a[j].val()) % T::mod();
            auto got = convolution_square<T::mod(),Root>(a);
            assert(got.size() == want.size());
            for (int i = 0; i < (int)want.size(); ++i) assert(got[i].val() == want[i]);
        }
    }
}
int main(){
    check_square<mint>(); check_square<fastmint>();
    check_square<ModInt<167772161>>(); check_square<ModInt<2013265921>,31>();
    bool caught = false;
    try { convolution_square(vector<ModInt<17>>(33)); } catch (const length_error&) { caught = true; }
    assert(caught);
    cout << "convolution square tests passed\n";
}
