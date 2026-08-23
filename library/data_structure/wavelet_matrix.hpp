#pragma once
#include "../basic/base.hpp"

template<class UInt = unsigned long long, int B = numeric_limits<UInt>::digits>
struct WaveletMatrix {
    static_assert(is_unsigned<UInt>::value, "WaveletMatrix requires an unsigned integer type");
    int n = 0; vector<int> mid; vector<vector<int>> ones;
    WaveletMatrix() = default; WaveletMatrix(const vector<UInt>& a){ build(a); }
    void build(vector<UInt> a){
        if constexpr (B < numeric_limits<UInt>::digits) for (UInt x : a) assert((x >> B) == 0);
        n = a.size(); mid.assign(B, 0); ones.assign(B, vector<int>(n + 1));
        vector<UInt> zero, one; zero.reserve(n); one.reserve(n);
        for (int level = 0; level < B; ++level){
            int bit = B - 1 - level; zero.clear(); one.clear();
            for (int i = 0; i < n; ++i){ int b = a[i] >> bit & 1; ones[level][i+1] = ones[level][i] + b; (b ? one : zero).push_back(a[i]); }
            mid[level] = zero.size(); copy(all(zero), a.begin()); copy(all(one), a.begin() + mid[level]);
        }
    }
    UInt kth_smallest(int l, int r, int k) const {
        assert(0 <= l && l <= r && r <= n && 0 <= k && k < r - l); UInt res = 0;
        for (int level = 0; level < B; ++level){ int ol = ones[level][l], orr = ones[level][r], zeros = (r-l) - (orr-ol); if (k < zeros) l -= ol, r -= orr; else res |= UInt(1) << (B-1-level), k -= zeros, l = mid[level]+ol, r = mid[level]+orr; }
        return res;
    }
    int rank(UInt x, int l, int r) const {
        assert(0 <= l && l <= r && r <= n);
        if constexpr (B < numeric_limits<UInt>::digits) if (x >> B) return 0;
        for (int level = 0; level < B; ++level){ int ol = ones[level][l], orr = ones[level][r]; if (x >> (B-1-level) & 1) l = mid[level]+ol, r = mid[level]+orr; else l -= ol, r -= orr; }
        return r - l;
    }
    int count_less(int l, int r, UInt x) const {
        assert(0 <= l && l <= r && r <= n); int res = 0;
        if constexpr (B < numeric_limits<UInt>::digits) if (x >> B) return r - l;
        for (int level = 0; level < B; ++level){ int ol = ones[level][l], orr = ones[level][r], zeros = (r-l) - (orr-ol); if (x >> (B-1-level) & 1) res += zeros, l = mid[level]+ol, r = mid[level]+orr; else l -= ol, r -= orr; }
        return res;
    }
    int range_freq(int l, int r, UInt lower, UInt upper) const { return count_less(l,r,upper) - count_less(l,r,lower); }
    optional<UInt> prev_value(int l, int r, UInt upper) const { int k = count_less(l,r,upper); if (!k) return nullopt; return kth_smallest(l,r,k-1); }
    optional<UInt> next_value(int l, int r, UInt lower) const { int k = count_less(l,r,lower); if (k == r-l) return nullopt; return kth_smallest(l,r,k); }
};
