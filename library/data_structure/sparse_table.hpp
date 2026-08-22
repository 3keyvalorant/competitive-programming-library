#pragma once
#include "../basic/base.hpp"

template<class T, T (*op)(T,T)> struct SparseTable {
    vector<int> lg; vector<vector<T>> st;
    SparseTable() = default;
    SparseTable(const vector<T>& a){ build(a); }
    void build(const vector<T>& a){
        int n = a.size(); lg.assign(n + 1, 0); for (int i = 2; i <= n; ++i) lg[i] = lg[i / 2] + 1;
        st.assign(n ? lg[n] + 1 : 0, vector<T>(n)); if (!n) return; st[0] = a;
        for (int k = 1; k < (int)st.size(); ++k) for (int i = 0; i + (1 << k) <= n; ++i) st[k][i] = op(st[k-1][i], st[k-1][i + (1 << (k-1))]);
    }
    T prod(int l, int r) const { assert(0 <= l && l < r && !st.empty() && r <= (int)st[0].size()); int k = lg[r-l]; return op(st[k][l], st[k][r - (1 << k)]); }
    T query(int l, int r) const { return prod(l, r); }
};

