#pragma once
#include "matrix.hpp"

namespace cp_linear {
template<class T> struct LinearSolution {
    bool consistent = true;
    int rank = 0; // Coefficient-matrix rank, not solution-space dimension.
    vector<T> particular;
    Matrix<T> kernel;
};

namespace linear_detail {
template<class T, bool Real> LinearSolution<T> eliminate(Matrix<T> a, vector<T> b, int variables, long double eps){
    size_t width = matrix_detail::width(a);
    if (variables < -1 || b.size() != a.size()) throw invalid_argument("invalid linear-system dimensions");
    if (a.empty()) width = variables < 0 ? 0 : (size_t)variables;
    else if (variables >= 0 && width != (size_t)variables) throw invalid_argument("variable count differs from matrix width");
    if (a.size() > INT_MAX || width > INT_MAX) throw length_error("linear system is too large");
    int n = (int)a.size(), m = (int)width;
    auto zero = [eps](const T& x){
        if constexpr (Real) return fabsl(x) <= eps;
        else return x == T(0);
    };
    auto check_finite = [](const T& x){
        if constexpr (Real) if (!isfinite(x)) throw overflow_error("nonfinite linear-system intermediate");
    };
    if constexpr (Real){
        if (!isfinite(eps) || eps <= 0) throw invalid_argument("epsilon must be finite and positive");
        for (const auto& row : a) for (auto x : row) if (!isfinite(x)) throw invalid_argument("matrix entries must be finite");
        for (auto x : b) if (!isfinite(x)) throw invalid_argument("right-hand side must be finite");
    }
    vector<int> where(m, -1);
    LinearSolution<T> result;
    for (int column = 0; column < m && result.rank < n; ++column){
        int row = result.rank, pivot = row;
        if constexpr (Real){
            for (int i = row + 1; i < n; ++i) if (fabsl(a[i][column]) > fabsl(a[pivot][column])) pivot = i;
        } else {
            while (pivot < n && zero(a[pivot][column])) ++pivot;
            if (pivot == n) continue;
        }
        if (zero(a[pivot][column])) continue;
        swap(a[pivot], a[row]); swap(b[pivot], b[row]);
        T divisor = a[row][column];
        if constexpr (Real){
            for (int j = column + 1; j < m; ++j){ a[row][j] /= divisor; check_finite(a[row][j]); }
            b[row] /= divisor; check_finite(b[row]);
        } else {
            T inverse = T(1) / divisor;
            for (int j = column + 1; j < m; ++j) a[row][j] *= inverse;
            b[row] *= inverse;
        }
        a[row][column] = T(1);
        for (int i = 0; i < n; ++i) if (i != row){
            T factor = a[i][column];
            if (factor == T(0)) continue;
            for (int j = column + 1; j < m; ++j){ a[i][j] -= factor * a[row][j]; check_finite(a[i][j]); }
            b[i] -= factor * b[row]; check_finite(b[i]);
            a[i][column] = T(0);
        }
        where[column] = row; ++result.rank;
    }
    for (int i = result.rank; i < n; ++i){
        bool all_zero = true;
        for (auto x : a[i]) if (!zero(x)){ all_zero = false; break; }
        if (all_zero && !zero(b[i])){ result.consistent = false; return result; }
    }
    result.particular.assign(m, T(0));
    for (int j = 0; j < m; ++j) if (where[j] >= 0) result.particular[j] = b[where[j]];
    for (int free_column = 0; free_column < m; ++free_column) if (where[free_column] < 0){
        vector<T> basis(m, T(0)); basis[free_column] = T(1);
        for (int j = 0; j < m; ++j) if (where[j] >= 0) basis[j] = T(0) - a[where[j]][free_column];
        result.kernel.push_back(move(basis));
    }
    return result;
}
} // namespace linear_detail

// Exact field arithmetic (e.g. ModInt with prime modulus), not integer division.
// O(n*m*min(n,m) + m^2) time, O(n*m + m^2) space including the kernel basis.
// With no rows, `variables` supplies the otherwise unrepresentable column count.
template<class T> LinearSolution<T> gauss_jordan(Matrix<T> a, vector<T> b, int variables = -1){
    static_assert(!is_arithmetic_v<T>, "use a field type for exact solving, or solve_linear_real for floating point");
    return linear_detail::eliminate<T,false>(move(a), move(b), variables, 0);
}

// Absolute epsilon, partial pivoting; rank/consistency are numerical decisions.
// Rescale ill-conditioned problems or use exact arithmetic when possible.
inline LinearSolution<long double> solve_linear_real(Matrix<long double> a, vector<long double> b, long double eps = 1e-12L, int variables = -1){
    return linear_detail::eliminate<long double,true>(move(a), move(b), variables, eps);
}
} // namespace cp_linear
