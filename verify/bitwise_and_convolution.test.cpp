// https://judge.yosupo.jp/problem/bitwise_and_convolution
#include "../library/math/modint.hpp"
#include "../library/math/subset_transform.hpp"

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int bits; cin >> bits; int n = 1 << bits;
    vector<mint> a(n), b(n); for (auto& x : a) cin >> x; for (auto& x : b) cin >> x;
    auto c = cp_subset::bitwise_and_convolution(move(a), move(b));
    for (int i = 0; i < n; ++i) cout << c[i] << " \n"[i + 1 == n];
}
