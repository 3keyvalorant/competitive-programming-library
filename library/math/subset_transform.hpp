#pragma once
#include "../basic/base.hpp"

namespace cp_subset {
namespace detail {
template<bool Superset, bool Inverse, class T> void transform(vector<T>& a){
    size_t n = a.size();
    if (n && (n & (n - 1))) throw invalid_argument("subset transform requires a power-of-two length");
    for (size_t half = 1; half < n; half <<= 1){
        for (size_t block = 0; block < n; block += half * 2){
            for (size_t j = 0; j < half; ++j){
                auto& lower = a[block + j]; auto& upper = a[block + half + j];
                if constexpr (Superset){ if constexpr (Inverse) lower -= upper; else lower += upper; }
                else { if constexpr (Inverse) upper -= lower; else upper += lower; }
            }
        }
    }
}
} // namespace detail

// In-place, O(B*2^B) time and O(1) extra space. Empty input is a no-op.
// subset_zeta: a[S] <- sum of original a[T] over T subset of S.
template<class T> void subset_zeta(vector<T>& a){ detail::transform<false,false>(a); }
template<class T> void subset_mobius(vector<T>& a){ detail::transform<false,true>(a); }
// superset_zeta: a[S] <- sum of original a[T] over T superset of S.
template<class T> void superset_zeta(vector<T>& a){ detail::transform<true,false>(a); }
template<class T> void superset_mobius(vector<T>& a){ detail::transform<true,true>(a); }

// c[S] = sum_{i|j=S} a[i]*b[j]. Inputs must have equal power-of-two lengths.
template<class T> vector<T> bitwise_or_convolution(vector<T> a, vector<T> b){
    if (a.size() != b.size()) throw invalid_argument("bitwise convolution requires equal lengths");
    subset_zeta(a); subset_zeta(b);
    for (size_t i = 0; i < a.size(); ++i) a[i] *= b[i];
    subset_mobius(a); return a;
}
// c[S] = sum_{i&j=S} a[i]*b[j]. O(B*2^B) time, O(2^B) memory.
template<class T> vector<T> bitwise_and_convolution(vector<T> a, vector<T> b){
    if (a.size() != b.size()) throw invalid_argument("bitwise convolution requires equal lengths");
    superset_zeta(a); superset_zeta(b);
    for (size_t i = 0; i < a.size(); ++i) a[i] *= b[i];
    superset_mobius(a); return a;
}
} // namespace cp_subset
