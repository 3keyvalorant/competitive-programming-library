#pragma once
#include "../math/batch_inverse.hpp"

namespace cp_probability {
namespace distribution_detail {
template<class T> void check_probability(const T& p){
    static_assert(!is_integral_v<T>, "use a floating-point or modular probability type");
    if constexpr (is_floating_point_v<T>){
        if (!isfinite(p) || p < 0 || p > 1) throw invalid_argument("probability must be finite and in [0,1]");
    }
}
template<class T> void check_pmf(const vector<T>& pmf){
    if (pmf.empty()) throw invalid_argument("PMF must be nonempty and normalized");
    if constexpr (is_floating_point_v<T>){
        long double total = 0;
        for (T p : pmf){ check_probability(p); total += (long double)p; }
        long double tolerance = max(1e-12L, 64.0L * numeric_limits<T>::epsilon());
        if (fabsl(total - 1) > tolerance) throw invalid_argument("PMF must sum to one");
    } else {
        T total = 0; for (const T& p : pmf){ check_probability(p); total += p; }
        if (total != T(1)) throw invalid_argument("PMF must sum to one in the current field");
    }
}
} // namespace distribution_detail

// Independent Bernoulli trials; result[k] = P(exactly k successes).
// O(N^2) time, O(N) memory. Modular p must represent probabilities in a field.
template<class T> vector<T> bernoulli_sum_distribution(const vector<T>& probabilities){
    vector<T> result(probabilities.size() + 1); result[0] = 1;
    for (size_t i = 0; i < probabilities.size(); ++i){
        T p = probabilities[i]; distribution_detail::check_probability(p); T q = T(1) - p;
        for (size_t k = i + 1; k > 0; --k) result[k] = result[k] * q + result[k - 1] * p;
        result[0] *= q;
    }
    return result;
}

// Identical independent trials. O(N) real time, O(N+log MOD) modular time.
// Modular T requires a prime modulus and N < MOD, except p=0/1 endpoints.
// Real weights start at their mode, avoiding underflow of the initial tail.
template<class T> vector<T> binomial_distribution(int n, T p){
    if (n < 0) throw invalid_argument("binomial_distribution requires nonnegative n");
    distribution_detail::check_probability(p);
    if constexpr (!is_floating_point_v<T>){
        if (p != T(0) && p != T(1) && n >= T::mod())
            throw invalid_argument("modular binomial_distribution requires n < modulus");
    }
    vector<T> result((size_t)n + 1);
    if (!n || p == T(0)){ result[0] = 1; return result; }
    if (p == T(1)){ result[n] = 1; return result; }
    if constexpr (is_floating_point_v<T>){
        long double probability = (long double)p, q = 1 - probability;
        int mode = (int)min((long double)n, floorl(((long double)n + 1) * probability));
        vector<long double> weights((size_t)n + 1); weights[mode] = 1;
        for (int k = mode; k > 0; --k) weights[k - 1] = weights[k] * k * q / (((long double)n - k + 1) * probability);
        for (int k = mode; k < n; ++k) weights[k + 1] = weights[k] * (n - k) * probability / (((long double)k + 1) * q);
        long double total = accumulate(weights.begin(), weights.end(), 0.0L);
        for (size_t k = 0; k < result.size(); ++k) result[k] = (T)(weights[k] / total);
    } else {
        vector<T> divisors(n); for (int k = 0; k < n; ++k) divisors[k] = k + 1;
        auto inverses = batch_inverse(divisors); T q = T(1) - p, ratio = p / q;
        result[0] = q.pow(n);
        for (size_t k = 1; k < result.size(); ++k) result[k] = result[k - 1] * T((long long)n - (long long)k + 1) * inverses[k - 1] * ratio;
    }
    return result;
}

// The nonempty PMF must sum to one. Floating tolerance: max(1e-12,64*epsilon).
// No automatic normalization. Both moments take O(N) time and O(1) extra space.
template<class T> T expectation(const vector<T>& pmf){
    distribution_detail::check_pmf(pmf); T result = 0;
    for (size_t i = 0; i < pmf.size(); ++i) result += T((long long)i) * pmf[i];
    return result;
}
template<class T> T variance(const vector<T>& pmf){
    T mean = expectation(pmf), result = 0;
    for (size_t i = 0; i < pmf.size(); ++i){ T difference = T((long long)i) - mean; result += pmf[i] * difference * difference; }
    return result;
}

// Solves E = immediate + weighted_other + stay*E; not a general cyclic solver.
// Modular division requires a field and a nonzero denominator.
template<class T> T self_loop_expectation(T immediate, T weighted_other, T stay){
    distribution_detail::check_probability(stay);
    if constexpr (is_floating_point_v<T>){
        if (!isfinite(immediate) || !isfinite(weighted_other)) throw invalid_argument("expected-value terms must be finite");
    }
    if (stay == T(1)) throw domain_error("self-loop equation has zero denominator");
    T result = (immediate + weighted_other) / (T(1) - stay);
    if constexpr (is_floating_point_v<T>) if (!isfinite(result)) throw overflow_error("expected value exceeds the floating-point range");
    return result;
}
} // namespace cp_probability
