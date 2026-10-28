#include "../library/probability/all.hpp"

int main(){
    combination<mint> co(100);
    assert(co.H(3, 4) == mint(15));
    assert(co.multinomial({2, 1, 1}) == mint(12));

    auto distribution = cp_probability::bernoulli_sum_distribution(vector<long double>{0.5L, 0.25L});
    assert(fabsl(cp_probability::expectation(distribution) - 0.75L) < 1e-12L);
    assert(fabsl(cp_probability::variance(distribution) - 0.4375L) < 1e-12L);

    mint half = mint(1) / 2, quarter = mint(1) / 4;
    auto binomial = cp_probability::binomial_distribution(3, half);
    assert(cp_probability::expectation(binomial) == mint(3) / 2);
    assert(cp_probability::variance(binomial) == mint(3) / 4);

    // Acyclic DP: advance by one or two with equal probability, stopping at goal.
    const int goal = 3;
    vector<mint> expected(goal + 1);
    for (int i = goal - 1; i >= 0; --i)
        expected[i] = 1 + half * expected[i + 1] + half * expected[min(goal, i + 2)];
    assert(expected[0] == mint(9) / 4);

    // Collect three equally likely coupon types, allowing repeated draws.
    vector<mint> coupon(4);
    for (int have = 2; have >= 0; --have){
        mint stay = mint(have) / 3;
        coupon[have] = cp_probability::self_loop_expectation(mint(1), (mint(1) - stay) * coupon[have + 1], stay);
    }
    assert(coupon[0] == mint(11) / 2);

    // E0=1+E0/2+E1/2, E1=1+E0/4; finite answers are E0=4,E1=2.
    cp_linear::Matrix<mint> equations{{mint(1) - half, mint(0) - half}, {mint(0) - quarter, 1}};
    auto solution = cp_linear::gauss_jordan(equations, vector<mint>{1, 1});
    assert(solution.consistent && solution.kernel.empty() && solution.particular == vector<mint>({4, 2}));
    auto real_solution = cp_linear::solve_linear_real({{.5L, -.5L}, {-.25L, 1.0L}}, {1.0L, 1.0L});
    assert(real_solution.consistent && fabsl(real_solution.particular[0] - 4) < 1e-12L);

    cp_linear::Matrix<long double> transition{{.5L, .5L}, {.25L, .75L}};
    auto two_steps = cp_linear::matrix_power(transition, 2);
    auto state = cp_linear::matrix_multiply(cp_linear::Matrix<long double>{{1, 0}}, two_steps)[0];
    assert(state == vector<long double>({.375L, .625L}));

    vector<mint> counts{1, 2, 3, 4};
    cp_subset::subset_zeta(counts); assert(counts == vector<mint>({1, 3, 4, 10}));
    cp_subset::subset_mobius(counts); assert(counts == vector<mint>({1, 2, 3, 4}));

    cout << "H(3,4)=" << co.H(3, 4) << ", multinomial(2,1,1)=" << co.multinomial({2, 1, 1}) << '\n';
    cout << "coin mean=" << cp_probability::expectation(distribution)
         << ", variance=" << cp_probability::variance(distribution) << '\n';
    cout << "cyclic expectation=" << real_solution.particular[0] << '\n';
}
