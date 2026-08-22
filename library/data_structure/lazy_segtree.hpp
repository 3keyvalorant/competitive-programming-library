#pragma once
#include "../basic/base.hpp"

template<class S, S (*op)(S,S), S (*e)(), class F, S (*mapping)(F,S), F (*composition)(F,F), F (*id)()>
struct lazy_segtree {
    int n = 0, size = 1, log = 0; vector<S> d; vector<F> lz;
    lazy_segtree(int m = 0) : lazy_segtree(vector<S>(m, e())) {}
    lazy_segtree(const vector<S>& v){ n = v.size(); while (size < n) size <<= 1, ++log; d.assign(2 * size, e()); lz.assign(size, id()); copy(v.begin(), v.end(), d.begin() + size); for (int i = size - 1; i; --i) update(i); }
    void update(int k){ d[k] = op(d[2*k], d[2*k+1]); }
    void all_apply(int k, F f){ d[k] = mapping(f, d[k]); if (k < size) lz[k] = composition(f, lz[k]); }
    void push(int k){ all_apply(2*k, lz[k]); all_apply(2*k+1, lz[k]); lz[k] = id(); }
    void set(int p, S x){ assert(0 <= p && p < n); p += size; for (int i = log; i; --i) push(p >> i); d[p] = x; for (int i = 1; i <= log; ++i) update(p >> i); }
    S get(int p){ assert(0 <= p && p < n); p += size; for (int i = log; i; --i) push(p >> i); return d[p]; }
    S prod(int l, int r){
        assert(0 <= l && l <= r && r <= n); if (l == r) return e(); l += size; r += size;
        for (int i = log; i; --i){ if ((l >> i) << i != l) push(l >> i); if ((r >> i) << i != r) push((r - 1) >> i); }
        S a = e(), b = e(); for (; l < r; l >>= 1, r >>= 1){ if (l & 1) a = op(a, d[l++]); if (r & 1) b = op(d[--r], b); } return op(a, b);
    }
    S all_prod() const { return d[1]; }
    void apply(int p, F f){ assert(0 <= p && p < n); p += size; for (int i = log; i; --i) push(p >> i); d[p] = mapping(f, d[p]); for (int i = 1; i <= log; ++i) update(p >> i); }
    void apply(int l, int r, F f){
        assert(0 <= l && l <= r && r <= n); if (l == r) return; l += size; r += size;
        for (int i = log; i; --i){ if ((l >> i) << i != l) push(l >> i); if ((r >> i) << i != r) push((r - 1) >> i); }
        int l2 = l, r2 = r; for (; l < r; l >>= 1, r >>= 1){ if (l & 1) all_apply(l++, f); if (r & 1) all_apply(--r, f); }
        l = l2; r = r2; for (int i = 1; i <= log; ++i){ if ((l >> i) << i != l) update(l >> i); if ((r >> i) << i != r) update((r - 1) >> i); }
    }
    template<class G> int max_right(int l, G g){
        assert(0 <= l && l <= n && g(e())); if (l == n) return n; l += size; for (int i = log; i; --i) push(l >> i); S sm = e();
        do { while (!(l & 1)) l >>= 1; if (!g(op(sm, d[l]))){ while (l < size){ push(l); l <<= 1; if (g(op(sm, d[l]))) sm = op(sm, d[l++]); } return l - size; } sm = op(sm, d[l++]); } while ((l & -l) != l); return n;
    }
    template<class G> int min_left(int r, G g){
        assert(0 <= r && r <= n && g(e())); if (!r) return 0; r += size; for (int i = log; i; --i) push((r - 1) >> i); S sm = e();
        do { --r; while (r > 1 && (r & 1)) r >>= 1; if (!g(op(d[r], sm))){ while (r < size){ push(r); r = 2*r+1; if (g(op(d[r], sm))) sm = op(d[r--], sm); } return r + 1 - size; } sm = op(d[r], sm); } while ((r & -r) != r); return 0;
    }
};
