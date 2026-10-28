#pragma once
#include "modint.hpp"

// Every entry must be invertible; zero/non-unit inputs violate T::inv()'s precondition.
// Nonempty input: one inverse and 3*(N-1) multiplications; O(N) extra space.
template<class T> vector<T> batch_inverse(const vector<T>& a){
    if (a.empty()) return {};
    vector<T> result(a.size()); result[0] = a[0];
    for (size_t i = 1; i < a.size(); ++i) result[i] = result[i - 1] * a[i];
    T inverse = result.back().inv();
    for (size_t i = a.size() - 1; i > 0; --i){
        result[i] = inverse * result[i - 1];
        inverse *= a[i];
    }
    result[0] = inverse;
    return result;
}
