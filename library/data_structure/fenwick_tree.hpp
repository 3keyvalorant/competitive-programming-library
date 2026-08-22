#pragma once
#include "../basic/base.hpp"

template<class T> struct FenwickTree {
    int n = 0; vector<T> bit;
    FenwickTree(int m = 0){ reset(m); }
    FenwickTree(const vector<T>& a){ n = a.size(); bit.assign(n + 1, T{}); for (int i = 0; i < n; ++i) bit[i + 1] += a[i]; for (int i = 1; i <= n; ++i) if (i + (i & -i) <= n) bit[i + (i & -i)] += bit[i]; }
    void reset(int m){ n = m; bit.assign(n + 1, T{}); }
    void add(int i, T x){ assert(0 <= i && i < n); for (++i; i <= n; i += i & -i) bit[i] += x; }
    T sum(int r) const { assert(0 <= r && r <= n); T s{}; for (; r; r -= r & -r) s += bit[r]; return s; }
    T sum(int l, int r) const { return sum(r) - sum(l); }
    T get(int i) const { return sum(i, i + 1); }
    int lower_bound(T x) const { if (x <= T{}) return 0; int k = 1, i = 0; T s{}; while ((k << 1) <= n) k <<= 1; for (; k; k >>= 1) if (i + k <= n && s + bit[i + k] < x) s += bit[i += k]; return min(i, n); }
};
