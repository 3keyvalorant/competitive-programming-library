// https://judge.yosupo.jp/problem/system_of_linear_equations
#include "../library/math/modint.hpp"
#include "../library/math/linear_equations.hpp"
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m; cin >> n >> m;
    cp_linear::Matrix<mint> a(n, vector<mint>(m)); vector<mint> b(n);
    for (auto& row : a) for (auto& x : row) cin >> x;
    for (auto& x : b) cin >> x;
    auto result = cp_linear::gauss_jordan(move(a), move(b), m);
    if (!result.consistent){ cout << -1 << '\n'; return 0; }
    cout << result.kernel.size() << '\n';
    auto print_row = [](const vector<mint>& row){
        for (size_t i = 0; i < row.size(); ++i) cout << row[i] << (i + 1 == row.size() ? '\n' : ' ');
    };
    print_row(result.particular); for (const auto& row : result.kernel) print_row(row);
}
