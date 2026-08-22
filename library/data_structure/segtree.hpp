#pragma once
#include "../basic/base.hpp"

template<class S, S (*op)(S, S), S (*e)()> struct segtree {
    int n = 0, size = 1, log = 0; vector<S> d;
    segtree(int m = 0) : segtree(vector<S>(m, e())) {}
    segtree(const vector<S>& v){ n = v.size(); while (size < n) size <<= 1, ++log; d.assign(2 * size, e()); copy(v.begin(), v.end(), d.begin() + size); for (int i = size - 1; i; --i) update(i); }
    void update(int k){ d[k] = op(d[2 * k], d[2 * k + 1]); }
    void set(int p, S x){ assert(0 <= p && p < n); d[p += size] = x; while (p >>= 1) update(p); }
    S get(int p) const { assert(0 <= p && p < n); return d[p + size]; }
    S prod(int l, int r) const { assert(0 <= l && l <= r && r <= n); S a = e(), b = e(); for (l += size, r += size; l < r; l >>= 1, r >>= 1){ if (l & 1) a = op(a, d[l++]); if (r & 1) b = op(d[--r], b); } return op(a, b); }
    S all_prod() const { return d[1]; }
    template<class F> int max_right(int l, F f) const {
        assert(0 <= l && l <= n && f(e())); if (l == n) return n; l += size; S sm = e();
        do { while (!(l & 1)) l >>= 1; if (!f(op(sm, d[l]))){ while (l < size){ l <<= 1; if (f(op(sm, d[l]))) sm = op(sm, d[l++]); } return l - size; } sm = op(sm, d[l++]); } while ((l & -l) != l);
        return n;
    }
    template<class F> int min_left(int r, F f) const {
        assert(0 <= r && r <= n && f(e())); if (!r) return 0; r += size; S sm = e();
        do { --r; while (r > 1 && (r & 1)) r >>= 1; if (!f(op(d[r], sm))){ while (r < size){ r = 2 * r + 1; if (f(op(d[r], sm))) sm = op(d[r--], sm); } return r + 1 - size; } sm = op(d[r], sm); } while ((r & -r) != r);
        return 0;
    }
};
