#pragma once
#include "../basic/base.hpp"

template<bool Minimum = true> struct LiChaoTree {
    struct Line { long long a = 0, b = 0; __int128 eval(long long x) const { return (__int128)a * x + b; } };
    vector<long long> xs; vector<Line> seg; vector<char> used;
    LiChaoTree(vector<long long> x) : xs(move(x)) { sort(all(xs)); xs.erase(unique(all(xs)), xs.end()); seg.resize(xs.size() * 4 + 4); used.assign(seg.size(), false); }
    bool better(__int128 a, __int128 b) const { return Minimum ? a < b : a > b; }
    void add_line(Line line){ assert(!xs.empty()); add_line(line, 1, 0, xs.size()); }
    void add_segment(Line line, long long xl, long long xr){ int l = lower_bound(all(xs), xl) - xs.begin(), r = lower_bound(all(xs), xr) - xs.begin(); add_segment(line, l, r, 1, 0, xs.size()); }
    long long query(long long x) const {
        int p = lower_bound(all(xs), x) - xs.begin(); assert(p < (int)xs.size() && xs[p] == x); __int128 ans = Minimum ? (__int128)LLONG_MAX : (__int128)LLONG_MIN;
        for (int k = 1, l = 0, r = xs.size();;){ if (used[k] && better(seg[k].eval(x), ans)) ans = seg[k].eval(x); if (r - l == 1) break; int m = (l + r) / 2; if (p < m) k *= 2, r = m; else k = k * 2 + 1, l = m; }
        return (long long)ans;
    }
private:
    void add_line(Line line, int k, int l, int r){
        if (!used[k]){ seg[k] = line; used[k] = true; return; }
        int m = (l + r) / 2; bool left = better(line.eval(xs[l]), seg[k].eval(xs[l])), mid = better(line.eval(xs[m]), seg[k].eval(xs[m]));
        if (mid) swap(line, seg[k]);
        if (r - l == 1) return;
        if (left != mid) add_line(line, k * 2, l, m); else add_line(line, k * 2 + 1, m, r);
    }
    void add_segment(Line line, int ql, int qr, int k, int l, int r){ if (qr <= l || r <= ql) return; if (ql <= l && r <= qr){ add_line(line, k, l, r); return; } int m = (l + r) / 2; add_segment(line, ql, qr, k * 2, l, m); add_segment(line, ql, qr, k * 2 + 1, m, r); }
};
