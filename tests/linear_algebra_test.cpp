#include "../library/math/linear_equations.hpp"
#include "../library/math/modint.hpp"

using namespace cp_linear;

template<class Exception, class F> void expect_error(F f){
    bool caught = false;
    try { f(); } catch (const Exception&) { caught = true; }
    assert(caught);
}
template<class T> vector<T> apply_matrix(const Matrix<T>& a, const vector<T>& x){
    vector<T> result(a.size());
    for (size_t i = 0; i < a.size(); ++i) for (size_t j = 0; j < x.size(); ++j) result[i] += a[i][j] * x[j];
    return result;
}

void check_modular(){
    using T = ModInt<7>;
    mt19937 rng(20261028);
    for (int trial = 0; trial < 250; ++trial){
        int n = rng() % 5, m = rng() % 5;
        Matrix<T> a(n, vector<T>(m)); vector<T> b(n);
        for (auto& row : a) for (auto& x : row) x = rng() % 7;
        for (auto& x : b) x = rng() % 7;
        auto result = gauss_jordan(a, b, m);
        int possibilities = 1; for (int j = 0; j < m; ++j) possibilities *= 7;
        int solutions = 0;
        for (int mask = 0; mask < possibilities; ++mask){
            vector<T> x(m); int state = mask;
            for (auto& v : x){ v = state % 7; state /= 7; }
            solutions += apply_matrix(a, x) == b;
        }
        assert(result.consistent == (solutions != 0));
        if (!result.consistent){ assert(result.particular.empty() && result.kernel.empty()); continue; }
        assert((int)result.particular.size() == m && apply_matrix(a, result.particular) == b);
        assert((int)result.kernel.size() == m - result.rank);
        int predicted = 1; for (const auto& basis : result.kernel){
            assert((int)basis.size() == m && apply_matrix(a, basis) == vector<T>(n)); predicted *= 7;
        }
        assert(predicted == solutions);
        // The standard free-variable coordinates also establish basis independence.
        Matrix<T> transpose(m, vector<T>(result.kernel.size()));
        for (int i = 0; i < m; ++i) for (size_t j = 0; j < result.kernel.size(); ++j) transpose[i][j] = result.kernel[j][i];
        auto independent = gauss_jordan(transpose, vector<T>(m), (int)result.kernel.size());
        assert(independent.rank == (int)result.kernel.size());
    }
    mint half = mint(1) / mint(2), quarter = mint(1) / mint(4);
    auto expectations = gauss_jordan(Matrix<mint>{{mint(1) - half, mint(0) - half}, {mint(0) - quarter, 1}}, vector<mint>{1,1});
    assert(expectations.consistent && expectations.rank == 2 && expectations.kernel.empty());
    assert(expectations.particular == vector<mint>({4,2}));
    auto no_equations = gauss_jordan(Matrix<T>{}, vector<T>{}, 3);
    assert(no_equations.consistent && no_equations.rank == 0 && no_equations.kernel == matrix_identity<T>(3));
    auto no_variables = gauss_jordan(Matrix<T>{{},{}}, vector<T>{0,0});
    assert(no_variables.consistent && no_variables.particular.empty() && no_variables.rank == 0);
    assert(!gauss_jordan(Matrix<T>{{}}, vector<T>{1}).consistent);
    expect_error<invalid_argument>([]{ gauss_jordan(Matrix<T>{{1},{1,2}}, vector<T>{1,1}); });
    expect_error<invalid_argument>([]{ gauss_jordan(Matrix<T>{{1}}, vector<T>{}); });
    expect_error<invalid_argument>([]{ gauss_jordan(Matrix<T>{{1}}, vector<T>{1}, 2); });
    expect_error<invalid_argument>([]{ gauss_jordan(Matrix<T>{}, vector<T>{}, -2); });
}

void check_real(){
    auto close = [](long double a, long double b){ return fabsl(a - b) <= 1e-9L * (1 + fabsl(b)); };
    auto check_result = [&](const Matrix<long double>& a, const vector<long double>& b, const LinearSolution<long double>& result){
        assert(result.consistent);
        auto product = apply_matrix(a, result.particular);
        for (size_t i = 0; i < b.size(); ++i) assert(close(product[i], b[i]));
        for (const auto& basis : result.kernel){
            auto zero = apply_matrix(a, basis);
            for (auto x : zero) assert(fabsl(x) <= 1e-9L);
        }
    };
    auto expected = solve_linear_real({{.5L,-.5L},{-.25L,1}}, {1,1});
    assert(expected.consistent && expected.rank == 2 && expected.kernel.empty());
    assert(close(expected.particular[0], 4) && close(expected.particular[1], 2));
    Matrix<long double> singular{{1,2,3},{2,4,6},{0,1,1}}; vector<long double> b{6,12,2};
    auto result = solve_linear_real(singular, b); check_result(singular, b, result);
    assert(result.rank == 2 && result.kernel.size() == 1);
    assert(!solve_linear_real({{1,2},{2,4}}, {3,7}).consistent);
    assert(solve_linear_real({}, {}, 1e-12L, 3).kernel == matrix_identity<long double>(3));
    assert(solve_linear_real({{},{}}, {0,0}).consistent);
    assert(!solve_linear_real({{}}, {1}).consistent);
    Matrix<long double> tiny_factor{{1,1e10L},{1e-13L,.003L}};
    auto tiny_b = apply_matrix(tiny_factor, vector<long double>{7,1});
    auto tiny = solve_linear_real(tiny_factor, tiny_b);
    assert(tiny.consistent && close(tiny.particular[1], 1));
    assert(fabsl(tiny.particular[0] - 7) < 1e-4L);
    mt19937 rng(20261028);
    for (int trial = 0; trial < 100; ++trial){
        int n = 1 + rng() % 6;
        Matrix<long double> a(n, vector<long double>(n)); vector<long double> x(n);
        for (int i = 0; i < n; ++i){
            for (int j = 0; j < n; ++j) a[i][j] = (int)(rng() % 11) - 5;
            a[i][i] += 40; x[i] = (int)(rng() % 11) - 5;
        }
        auto rhs = apply_matrix(a, x); auto got = solve_linear_real(a, rhs);
        check_result(a, rhs, got); assert(got.rank == n && got.kernel.empty());
        for (int i = 0; i < n; ++i) assert(close(got.particular[i], x[i]));
    }
    long double infinity = numeric_limits<long double>::infinity();
    long double nan = numeric_limits<long double>::quiet_NaN();
    expect_error<invalid_argument>([]{ solve_linear_real({{1}}, {1}, 0); });
    expect_error<invalid_argument>([&]{ solve_linear_real({{1}}, {1}, infinity); });
    expect_error<invalid_argument>([&]{ solve_linear_real({{nan}}, {1}); });
    expect_error<invalid_argument>([&]{ solve_linear_real({{1}}, {infinity}); });
    expect_error<invalid_argument>([]{ solve_linear_real({{1,2},{3}}, {1,2}); });
    expect_error<overflow_error>([]{
        long double large = numeric_limits<long double>::max();
        solve_linear_real({{large,large},{large,-large}}, {0,0});
    });
}

void check_matrices(){
    mt19937 rng(20261028);
    for (int trial = 0; trial < 100; ++trial){
        int n = 1 + rng() % 5, k = 1 + rng() % 5, m = 1 + rng() % 5;
        Matrix<mint> a(n, vector<mint>(k)), b(k, vector<mint>(m)), want(n, vector<mint>(m));
        for (auto& row : a) for (auto& x : row) x = rng() % 100;
        for (auto& row : b) for (auto& x : row) x = rng() % 100;
        for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) for (int z = 0; z < k; ++z) want[i][j] += a[i][z] * b[z][j];
        assert(matrix_multiply(a,b) == want);
    }
    for (int n = 0; n <= 4; ++n){
        Matrix<mint> a(n, vector<mint>(n)); for (auto& row : a) for (auto& x : row) x = rng() % 7;
        auto want = matrix_identity<mint>(n);
        for (int power = 0; power <= 10; ++power){ assert(matrix_power(a,power) == want); want = matrix_multiply(want,a); }
    }
    assert(matrix_power(Matrix<mint>{{1,1},{1,0}},10) == Matrix<mint>({{89,55},{55,34}}));
    assert(matrix_power(Matrix<long double>{{.5L,.5L},{0,1}},2) == Matrix<long double>({{.25L,.75L},{0,1}}));
    assert(matrix_multiply(Matrix<mint>{{},{}}, Matrix<mint>{}) == Matrix<mint>({{}, {}}));
    expect_error<invalid_argument>([]{ matrix_multiply(Matrix<mint>{{1,2}}, Matrix<mint>{{1}}); });
    expect_error<invalid_argument>([]{ matrix_multiply(Matrix<mint>{{1},{1,2}}, Matrix<mint>{{1}}); });
    expect_error<invalid_argument>([]{ matrix_power(Matrix<mint>{{1,2}}, 2); });
    expect_error<invalid_argument>([]{ matrix_power(Matrix<mint>{{1}}, -1); });
}

int main(){
    check_matrices(); check_modular(); check_real();
    cout << "linear algebra tests passed\n";
}
