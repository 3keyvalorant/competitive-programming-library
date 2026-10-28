#pragma once
#include "exact.hpp"

namespace cp_transform {
// Dense nonnegative values only. result[s] counts pairs (a[i], b[j]) with sum s.
// Padded output length <= 2^24; all exact intermediate coefficients must fit LL.
inline vector<long long> pair_sum_counts(const vector<int>& a, const vector<int>& b){
    int max_a = 0, max_b = 0;
    for (int x : a){ if (x < 0) throw invalid_argument("pair_sum_counts requires nonnegative values"); max_a = max(max_a, x); }
    for (int x : b){ if (x < 0) throw invalid_argument("pair_sum_counts requires nonnegative values"); max_b = max(max_b, x); }
    if (a.empty() || b.empty()) return {};
    if ((long long)max_a + max_b + 1 > (1 << 24)) throw length_error("pair_sum_counts dense output exceeds 2^24");
    vector<long long> fa((size_t)max_a + 1), fb((size_t)max_b + 1);
    for (int x : a) ++fa[x];
    for (int x : b) ++fb[x];
    return convolution_ll(fa, fb);
}

// result[s] counts distinct index pairs i < j, including equal-valued elements.
inline vector<long long> unordered_pair_sum_counts(const vector<int>& values){
    if (values.empty()) return {};
    int largest = 0;
    for (int x : values){ if (x < 0) throw invalid_argument("unordered_pair_sum_counts requires nonnegative values"); largest = max(largest, x); }
    if (2LL * largest + 1 > (1 << 24)) throw length_error("unordered_pair_sum_counts dense output exceeds 2^24");
    vector<long long> frequency((size_t)largest + 1);
    for (int x : values) ++frequency[x];
    auto result = convolution_ll(frequency, frequency);
    for (int x : values) --result[2 * (size_t)x];
    for (auto& x : result) x /= 2;
    return result;
}

// ways[v] is the number of choices of value v. Make `picks` ordered choices,
// with replacement; return counts modulo 998244353 for sums 0..max_sum.
// O(L log L log picks) time, O(L) memory; max_sum <= 2^22-1 (NTT limit).
inline vector<mint> sum_distribution_mod(const vector<long long>& ways, long long picks, int max_sum){
    if (picks < 0 || max_sum < 0) throw invalid_argument("sum_distribution_mod requires nonnegative picks and max_sum");
    if (max_sum >= (1 << 22)) throw length_error("sum_distribution_mod requires max_sum < 2^22");
    for (long long x : ways) if (x < 0) throw invalid_argument("sum_distribution_mod requires nonnegative counts");
    size_t limit = (size_t)max_sum + 1;
    if (!picks){ vector<mint> result(limit); result[0] = 1; return result; }
    vector<mint> base(min(ways.size(), limit));
    for (size_t i = 0; i < base.size(); ++i) base[i] = ways[i];
    auto truncate = [limit](vector<mint> a){
        if (a.size() > limit) a.resize(limit);
        while (!a.empty() && a.back() == mint(0)) a.pop_back();
        return a;
    };
    base = truncate(move(base));
    vector<mint> result{1};
    while (picks && !base.empty()){
        if (picks & 1) result = truncate(::convolution(move(result), base));
        picks >>= 1;
        if (picks) base = truncate(::convolution_square(move(base)));
    }
    if (picks) result.clear();
    result.resize(limit);
    return result;
}
} // namespace cp_transform
