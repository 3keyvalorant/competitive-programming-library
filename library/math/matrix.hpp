#pragma once
#include "../basic/base.hpp"

namespace cp_linear {
template<class T> using Matrix = vector<vector<T>>;

namespace matrix_detail {
template<class T> size_t width(const Matrix<T>& a){
    size_t columns = a.empty() ? 0 : a.front().size();
    for (const auto& row : a) if (row.size() != columns) throw invalid_argument("matrix must be rectangular");
    return columns;
}
} // namespace matrix_detail

template<class T> Matrix<T> matrix_identity(size_t n){
    Matrix<T> result(n, vector<T>(n, T(0)));
    for (size_t i = 0; i < n; ++i) result[i][i] = T(1);
    return result;
}

// O(rows(a)*cols(a)*cols(b)); scalar arithmetic must remain valid in T.
// An empty outer vector represents 0x0; a zero-row nonzero-width shape is not stored.
template<class T> Matrix<T> matrix_multiply(const Matrix<T>& a, const Matrix<T>& b){
    size_t inner = matrix_detail::width(a), columns = matrix_detail::width(b);
    if (inner != b.size()) throw invalid_argument("incompatible matrix dimensions");
    Matrix<T> result(a.size(), vector<T>(columns, T(0)));
    for (size_t i = 0; i < a.size(); ++i) for (size_t k = 0; k < inner; ++k)
        for (size_t j = 0; j < columns; ++j) result[i][j] += a[i][k] * b[k][j];
    return result;
}

// O(n^3 log(exponent+1)) time, O(n^2) extra space.
template<class T> Matrix<T> matrix_power(Matrix<T> a, long long exponent){
    if (exponent < 0) throw invalid_argument("matrix exponent must be nonnegative");
    if (matrix_detail::width(a) != a.size()) throw invalid_argument("matrix power requires a square matrix");
    auto result = matrix_identity<T>(a.size());
    while (exponent){
        if (exponent & 1) result = matrix_multiply(result, a);
        exponent >>= 1;
        if (exponent) a = matrix_multiply(a, a);
    }
    return result;
}
} // namespace cp_linear
