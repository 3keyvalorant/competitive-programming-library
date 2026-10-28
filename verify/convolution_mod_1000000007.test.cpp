// https://judge.yosupo.jp/problem/convolution_mod_1000000007
#include "../library/convolution/exact.hpp"
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m; cin >> n >> m; vector<long long> a(n), b(m);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;
    auto c = cp_transform::convolution_mod(move(a), move(b), 1000000007);
    for (int i = 0; i < (int)c.size(); ++i) cout << c[i] << " \n"[i + 1 == (int)c.size()];
}
