#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
template<class T> using minpq = priority_queue<T, vector<T>, greater<T>>;
template<class T> using maxpq = priority_queue<T>;

constexpr int INF = numeric_limits<int>::max() / 2;
constexpr ll LINF = numeric_limits<ll>::max() / 4;

#define rep(i,n) for (long long i = 0; i < (long long)(n); ++i)
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)

template<class T, class U> bool chmin(T& a, const U& b){ if (b < a) return a = b, true; return false; }
template<class T, class U> bool chmax(T& a, const U& b){ if (a < b) return a = b, true; return false; }

inline void Yes(){ cout << "Yes\n"; }
inline void No(){ cout << "No\n"; }
inline void YN(bool ok){ ok ? Yes() : No(); }

template<class T> T ceil_div(T a, T b){
    assert(b != 0);
    T q = a / b, r = a % b;
    return q + (r != 0 && ((r > 0) == (b > 0)));
}
inline bool is_in_grid(int i, int j, int h, int w){ return 0 <= i && i < h && 0 <= j && j < w; }
template<class T> T manhattan_distance(T x1, T y1, T x2, T y2){ return abs(x1 - x2) + abs(y1 - y2); }
template<class T> long double euclidean_distance(T x1, T y1, T x2, T y2){ return hypot((long double)(x1 - x2), (long double)(y1 - y2)); }

template<class T> vector<T> compressed_values(vector<T> xs){ sort(all(xs)); xs.erase(unique(all(xs)), xs.end()); return xs; }
template<class T> vector<int> coordinate_compress(const vector<T>& a){
    auto xs = compressed_values(a);
    vector<int> res(a.size());
    for (int i = 0; i < (int)a.size(); ++i) res[i] = lower_bound(all(xs), a[i]) - xs.begin();
    return res;
}


template<class T> vector<T> prefix_sum(const vector<T>& a){
    vector<T> s(a.size() + 1);
    for (int i = 0; i < (int)a.size(); ++i) s[i + 1] = s[i] + a[i];
    return s;
}
template<class T> T range_sum(const vector<T>& s, int l, int r){ assert(0 <= l && l <= r && r < (int)s.size()); return s[r] - s[l]; }
template<class T> vector<vector<T>> prefix_sum_2d(const vector<vector<T>>& a){
    int h = a.size(), w = h ? a[0].size() : 0;
    vector s(h + 1, vector<T>(w + 1));
    for (int i = 0; i < h; ++i) for (int j = 0; j < w; ++j)
        s[i + 1][j + 1] = a[i][j] + s[i][j + 1] + s[i + 1][j] - s[i][j];
    return s;
}
template<class T> T range_sum_2d(const vector<vector<T>>& s, int x1, int y1, int x2, int y2){
    return s[x2][y2] - s[x1][y2] - s[x2][y1] + s[x1][y1];
}
template<class T> void rotate_grid(vector<vector<T>>& a, bool counterclockwise = false){
    if (a.empty() || a[0].empty()) return;
    int h = a.size(), w = a[0].size();
    vector b(w, vector<T>(h));
    for (int i = 0; i < h; ++i) for (int j = 0; j < w; ++j)
        if (counterclockwise) b[w - 1 - j][i] = a[i][j]; else b[j][h - 1 - i] = a[i][j];
    a = move(b);
}


template<int MOD> struct ModInt {
    int v;
    ModInt(long long x = 0) : v((int)(x % MOD)){ if (v < 0) v += MOD; }
    static constexpr int mod(){ return MOD; }
    int val() const { return v; }
    ModInt& operator+=(const ModInt& o){ if ((v += o.v) >= MOD) v -= MOD; return *this; }
    ModInt& operator-=(const ModInt& o){ if ((v -= o.v) < 0) v += MOD; return *this; }
    ModInt& operator*=(const ModInt& o){ v = (int)((long long)v * o.v % MOD); return *this; }
    ModInt& operator/=(const ModInt& o){ return *this *= o.inv(); }
    ModInt pow(long long n) const { assert(n >= 0); ModInt a = *this, r = 1; while (n){ if (n & 1) r *= a; a *= a; n >>= 1; } return r; }
    ModInt inv() const { long long a = v, b = MOD, x = 1, y = 0; while (b){ long long q = a / b; a -= q * b; swap(a, b); x -= q * y; swap(x, y); } assert(a == 1); return ModInt(x); }
    friend ModInt operator+(ModInt a, const ModInt& b){ return a += b; }
    friend ModInt operator-(ModInt a, const ModInt& b){ return a -= b; }
    friend ModInt operator*(ModInt a, const ModInt& b){ return a *= b; }
    friend ModInt operator/(ModInt a, const ModInt& b){ return a /= b; }
    friend bool operator==(const ModInt& a, const ModInt& b){ return a.v == b.v; }
    friend bool operator!=(const ModInt& a, const ModInt& b){ return !(a == b); }
    friend ostream& operator<<(ostream& os, const ModInt& x){ return os << x.v; }
    friend istream& operator>>(istream& is, ModInt& x){ long long v; is >> v; x = ModInt(v); return is; }
};
using mint = ModInt<998244353>;
using amint = ModInt<1000000007>;


template<class T> struct combination {
    vector<T> fact, ifact;
    combination(int n = 0){ reset(n); }
    void reset(int n){
        fact.assign(n + 1, 1); ifact.assign(n + 1, 1);
        for (int i = 1; i <= n; ++i) fact[i] = fact[i - 1] * i;
        if (n){ ifact[n] = fact[n].inv(); for (int i = n; i; --i) ifact[i - 1] = ifact[i] * i; }
    }
    T get(int n, int r) const { return r < 0 || n < r || n >= (int)fact.size() ? T(0) : fact[n] * ifact[r] * ifact[n - r]; }
    T C(int n, int r) const { return get(n, r); }
    T permutation(int n, int r) const { return r < 0 || n < r || n >= (int)fact.size() ? T(0) : fact[n] * ifact[n - r]; }
    T P(int n, int r) const { return permutation(n, r); }
    T calu(int n, int r) const { return get(n, r); }
};


inline long long modpow(long long a, long long n, long long mod){ long long r = 1 % mod; for (a %= mod; n; n >>= 1, a = (long long)((__int128)a * a % mod)) if (n & 1) r = (long long)((__int128)r * a % mod); return r; }
inline long long safe_mod_multiply(long long a, long long b, long long mod){ return (long long)((__int128)a * b % mod); }
inline long long extgcd(long long a, long long b, long long& x, long long& y){ if (!b){ x = a >= 0 ? 1 : -1; y = 0; return abs(a); } long long g = extgcd(b, a % b, y, x); y -= a / b * x; return g; }
inline optional<long long> modular_inverse(long long a, long long mod){ long long x, y, g = extgcd(a, mod, x, y); if (g != 1) return nullopt; return (x % mod + mod) % mod; }
inline pair<long long, long long> crt(const vector<long long>& r, const vector<long long>& m){
    assert(r.size() == m.size()); long long r0 = 0, m0 = 1;
    for (int i = 0; i < (int)r.size(); ++i){
        assert(m[i] > 0); long long r1 = (r[i] % m[i] + m[i]) % m[i], m1 = m[i];
        long long x, y, g = extgcd(m0, m1, x, y); if ((r1 - r0) % g) return {0, 0};
        long long u = m1 / g, t = safe_mod_multiply((r1 - r0) / g, x, u);
        r0 += m0 * t; m0 *= u; r0 = (r0 % m0 + m0) % m0;
    }
    return {r0, m0};
}
inline vector<int> eratosthenes(int n){ vector<int> prime(n + 1, true); if (n >= 0) prime[0] = false; if (n >= 1) prime[1] = false; for (long long i = 2; i * i <= n; ++i) if (prime[i]) for (long long j = i * i; j <= n; j += i) prime[j] = false; return prime; }
inline vector<int> primes_up_to(int n){ auto p = eratosthenes(n); vector<int> res; for (int i = 2; i <= n; ++i) if (p[i]) res.push_back(i); return res; }
inline bool is_prime(long long n){ if (n < 2) return false; for (long long p = 2; p * p <= n; ++p) if (n % p == 0) return false; return true; }
inline map<long long, int> prime_factorize(long long n){ map<long long, int> f; for (long long p = 2; p * p <= n; ++p) while (n % p == 0) ++f[p], n /= p; if (n > 1) ++f[n]; return f; }
inline vector<long long> divisors(long long n){ vector<long long> d; for (long long i = 1; i * i <= n; ++i) if (n % i == 0){ d.push_back(i); if (i * i != n) d.push_back(n / i); } sort(all(d)); return d; }
inline long long integer_sqrt(long long n){ assert(n >= 0); long long x = sqrt((long double)n); while ((__int128)(x + 1) * (x + 1) <= n) ++x; while ((__int128)x * x > n) --x; return x; }


struct UnionFind {
    vector<int> p;
    UnionFind(int n = 0){ reset(n); }
    void reset(int n){ p.assign(n, -1); }
    int leader(int a){ assert(0 <= a && a < (int)p.size()); while (p[a] >= 0){ if (p[p[a]] >= 0) p[a] = p[p[a]]; a = p[a]; } return a; }
    bool merge(int a, int b){ a = leader(a); b = leader(b); if (a == b) return false; if (-p[a] < -p[b]) swap(a, b); p[a] += p[b]; p[b] = a; return true; }
    bool marge(int a, int b){ return merge(a, b); }
    bool same(int a, int b){ return leader(a) == leader(b); }
    int size(int a){ return -p[leader(a)]; }
    vector<vector<int>> groups(){ vector<vector<int>> g(p.size()); for (int i = 0; i < (int)p.size(); ++i) g[leader(i)].push_back(i); g.erase(remove_if(all(g), [](auto& v){ return v.empty(); }), g.end()); return g; }
};
template<class T = int> using unionfind = UnionFind;

template<class T> struct WeightedUnionFind {
    vector<int> p; vector<T> diff;
    WeightedUnionFind(int n = 0){ reset(n); }
    void reset(int n){ p.assign(n, -1); diff.assign(n, T{}); }
    int leader(int x){ if (p[x] < 0) return x; int q = p[x]; p[x] = leader(q); diff[x] += diff[q]; return p[x]; }
    T potential(int x){ leader(x); return diff[x]; }
    bool same(int x, int y){ return leader(x) == leader(y); }
    T difference(int x, int y){ assert(same(x, y)); return potential(y) - potential(x); }
    bool merge(int x, int y, T w){ w += potential(x) - potential(y); x = leader(x); y = leader(y); if (x == y) return w == T{}; if (-p[x] < -p[y]) swap(x, y), w = -w; p[x] += p[y]; p[y] = x; diff[y] = w; return true; }
    int size(int x){ return -p[leader(x)]; }
};


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


inline vector<int> bfs(const vector<vector<int>>& g, const vector<int>& starts){
    vector<int> d(g.size(), -1); queue<int> q; for (int s : starts) if (d[s] < 0) d[s] = 0, q.push(s);
    while (!q.empty()){ int v = q.front(); q.pop(); for (int to : g[v]) if (d[to] < 0) d[to] = d[v] + 1, q.push(to); }
    return d;
}
inline vector<int> bfs(const vector<vector<int>>& g, int s){ return bfs(g, vector<int>{s}); }

template<class T> vector<T> bfs01(const vector<vector<pair<int,T>>>& g, int s){
    const T inf = numeric_limits<T>::max() / 4; vector<T> d(g.size(), inf); deque<int> q; d[s] = 0; q.push_back(s);
    while (!q.empty()){ int v = q.front(); q.pop_front(); for (auto [to,w] : g[v]){ assert(w == 0 || w == 1); if (d[to] > d[v] + w){ d[to] = d[v] + w; w ? q.push_back(to) : q.push_front(to); } } }
    return d;
}

template<class T = long long> struct Dijkstra {
    int n = 0, start = -1; vector<vector<pair<int,T>>> g; vector<T> dist; vector<int> prev;
    Dijkstra(int m = 0){ reset(m); }
    void reset(int m){ n = m; g.assign(n, {}); dist.clear(); prev.clear(); }
    void make_directedgraph(int u, int v, T w){ g[u].push_back({v,w}); }
    void make_indirectedgraph(int u, int v, T w){ make_directedgraph(u,v,w); make_directedgraph(v,u,w); }
    const vector<T>& do_dijkstra(int s){
        start = s; T inf = numeric_limits<T>::max() / 4; dist.assign(n, inf); prev.assign(n, -1); minpq<pair<T,int>> q; dist[s] = 0; q.push({0,s});
        while (!q.empty()){ auto [d,v] = q.top(); q.pop(); if (d != dist[v]) continue; for (auto [to,w] : g[v]) if (chmin(dist[to], d+w)) prev[to] = v, q.push({dist[to],to}); }
        return dist;
    }
    T output(int v) const { return dist[v]; }
    vector<int> path(int v) const { if (dist.empty() || dist[v] == numeric_limits<T>::max()/4) return {}; vector<int> p; for (; v != -1; v = prev[v]) p.push_back(v); reverse(all(p)); return p; }
};

template<class T> struct BellmanFordResult { vector<T> dist; vector<char> negative; bool has_negative_cycle; };
template<class T> BellmanFordResult<T> bellman_ford(int n, const vector<tuple<int,int,T>>& edges, int s){
    T inf = numeric_limits<T>::max()/4; vector<T> d(n,inf); vector<char> neg(n); d[s]=0;
    for (int i=0;i<n;++i) for (auto [u,v,w]:edges) if (d[u]!=inf && d[v]>max(-inf,d[u]+w)){ d[v]=max(-inf,d[u]+w); if(i==n-1) neg[v]=1; }
    for(int i=0;i<n;++i) for(auto [u,v,w]:edges) if(neg[u]) neg[v]=1;
    return {d,neg,any_of(all(neg),[](char x){return x;})};
}

template<class T> void floyd_warshall(vector<vector<T>>& d){
    int n=d.size(); T inf=numeric_limits<T>::max()/4;
    for(int k=0;k<n;++k)for(int i=0;i<n;++i)if(d[i][k]!=inf)for(int j=0;j<n;++j)if(d[k][j]!=inf)chmin(d[i][j],d[i][k]+d[k][j]);
}

inline optional<vector<int>> topological_sort(const vector<vector<int>>& g){
    int n=g.size(); vector<int> deg(n),res; for(auto& es:g)for(int v:es)++deg[v]; queue<int>q; for(int i=0;i<n;++i)if(!deg[i])q.push(i);
    while(!q.empty()){int v=q.front();q.pop();res.push_back(v);for(int to:g[v])if(!--deg[to])q.push(to);} if((int)res.size()!=n)return nullopt; return res;
}

struct SCC {
    int n=0,scc_count=0; vector<vector<int>> g,rg,groups,dag; vector<int> comp,indeg,outdeg;
    SCC(int m=0){reset(m);} void reset(int m){n=m;g.assign(n,{});rg.assign(n,{});}
    void add_edge(int u,int v){g[u].push_back(v);rg[v].push_back(u);}
    int do_scc(){
        vector<char> used(n); vector<int> order;
        for(int s=0;s<n;++s)if(!used[s]){ vector<pair<int,int>> st{{s,0}};used[s]=1; while(!st.empty()){auto&[v,i]=st.back();if(i<(int)g[v].size()){int to=g[v][i++];if(!used[to])used[to]=1,st.push_back({to,0});}else order.push_back(v),st.pop_back();}}
        comp.assign(n,-1);scc_count=0;reverse(all(order)); for(int s:order)if(comp[s]<0){stack<int>st;st.push(s);comp[s]=scc_count;while(!st.empty()){int v=st.top();st.pop();for(int to:rg[v])if(comp[to]<0)comp[to]=scc_count,st.push(to);}++scc_count;}
        groups.assign(scc_count,{});for(int v=0;v<n;++v)groups[comp[v]].push_back(v);dag.assign(scc_count,{});indeg.assign(scc_count,0);outdeg.assign(scc_count,0);
        vector<pair<int,int>> es;for(int v=0;v<n;++v)for(int to:g[v])if(comp[v]!=comp[to])es.push_back({comp[v],comp[to]});sort(all(es));es.erase(unique(all(es)),es.end());for(auto[a,b]:es)dag[a].push_back(b),++outdeg[a],++indeg[b];
        return scc_count;
    }
};

struct TwoSAT {
    int n; SCC scc; vector<bool> ans;
    TwoSAT(int m=0):n(m),scc(2*m),ans(m){}
    int id(int i,bool f)const{return 2*i+(f?0:1);}
    void add_clause(int i,bool f,int j,bool g){scc.add_edge(id(i,!f),id(j,g));scc.add_edge(id(j,!g),id(i,f));}
    bool satisfiable(){scc.do_scc();for(int i=0;i<n;++i){if(scc.comp[id(i,0)]==scc.comp[id(i,1)])return false;ans[i]=scc.comp[id(i,1)]>scc.comp[id(i,0)];}return true;}
    vector<bool> answer()const{return ans;}
};

template<class T> struct KruskalResult{T cost{};vector<tuple<int,int,T>> edges;bool connected=false;};
template<class T> KruskalResult<T> kruskal(int n,vector<tuple<int,int,T>> edges){
    sort(all(edges),[](auto&a,auto&b){return get<2>(a)<get<2>(b);});UnionFind uf(n);KruskalResult<T>r;
    for(auto[u,v,w]:edges)if(uf.merge(u,v)){r.cost+=w;r.edges.push_back({u,v,w});}
    r.connected=n==0||(int)r.edges.size()==n-1;return r;
}

template<class T> struct Dinic {
    struct Edge{int to,rev;T cap;}; int n;vector<vector<Edge>>g;vector<int>level,it;
    Dinic(int m=0):n(m),g(m),level(m),it(m){}
    void add_edge(int u,int v,T cap){int a=g[u].size(),b=g[v].size();g[u].push_back({v,b,cap});g[v].push_back({u,a,T{}});}
    bool bfs_level(int s,int t){fill(all(level),-1);queue<int>q;q.push(s);level[s]=0;while(!q.empty()){int v=q.front();q.pop();for(auto&e:g[v])if(e.cap>0&&level[e.to]<0)level[e.to]=level[v]+1,q.push(e.to);}return level[t]>=0;}
    T dfs(int v,int t,T f){if(v==t)return f;for(int&i=it[v];i<(int)g[v].size();++i){Edge&e=g[v][i];if(e.cap>0&&level[v]<level[e.to]){T d=dfs(e.to,t,min(f,e.cap));if(d>0){e.cap-=d;g[e.to][e.rev].cap+=d;return d;}}}return T{};}
    T flow(int s,int t,T limit=numeric_limits<T>::max()){T res{};while(res<limit&&bfs_level(s,t)){fill(all(it),0);while(T f=dfs(s,t,limit-res))res+=f;}return res;}
};

namespace cycle_detail {
inline vector<int> path(const vector<vector<int>>& g,int s,int t,int banned_vertex=-1,pair<int,int> banned_edge={-1,-1},bool directed=true){
    if(s==banned_vertex||t==banned_vertex)return{};
    vector<int>pre(g.size(),-1);queue<int>q;pre[s]=s;q.push(s);
    while(!q.empty()){int v=q.front();q.pop();for(int to:g[v]){bool bad=v==banned_edge.first&&to==banned_edge.second;if(!directed)bad=bad||(v==banned_edge.second&&to==banned_edge.first);if(bad||to==banned_vertex||pre[to]>=0)continue;pre[to]=v;q.push(to);}}
    if(pre[t]<0)return{};
    vector<int>p;for(int v=t;;v=pre[v]){p.push_back(v);if(v==s)break;}reverse(all(p));return p;
}
inline bool distinct(const vector<int>& p){auto q=p;sort(all(q));return adjacent_find(all(q))==q.end();}
}

inline vector<int> find_cycle_directed(const vector<vector<int>>& g){
    int n=g.size();vector<int>state(n),pos(n,-1),st;for(int s=0;s<n;++s)if(!state[s]){vector<pair<int,int>>dfs{{s,0}};state[s]=1;pos[s]=st.size();st.push_back(s);while(!dfs.empty()){auto&[v,i]=dfs.back();if(i==(int)g[v].size()){state[v]=2;pos[v]=-1;st.pop_back();dfs.pop_back();continue;}int to=g[v][i++];if(!state[to])state[to]=1,pos[to]=st.size(),st.push_back(to),dfs.push_back({to,0});else if(state[to]==1)return vector<int>(st.begin()+pos[to],st.end());}}return{};
}
inline bool has_cycle_directed(const vector<vector<int>>&g){return !find_cycle_directed(g).empty();}

inline vector<int> find_cycle_undirected(const vector<vector<int>>&g){
    int n=g.size();vector<int>par(n,-1),dep(n),state(n);for(int s=0;s<n;++s)if(!state[s]){vector<pair<int,int>>st{{s,0}};state[s]=1;while(!st.empty()){auto&[v,i]=st.back();if(i==(int)g[v].size()){state[v]=2;st.pop_back();continue;}int to=g[v][i++];if(to==v)return{v};if(to==par[v])continue;if(!state[to])par[to]=v,dep[to]=dep[v]+1,state[to]=1,st.push_back({to,0});else if(state[to]==1&&dep[to]<dep[v]){vector<int>c;for(int x=v;x!=to;x=par[x])c.push_back(x);c.push_back(to);reverse(all(c));return c;}}}return{};
}
inline bool has_cycle_undirected(const vector<vector<int>>&g){return !find_cycle_undirected(g).empty();}

inline vector<int> find_cycle_through_directed(const vector<vector<int>>&g,int x){for(int to:g[x]){if(to==x)return{x};auto p=cycle_detail::path(g,to,x);if(!p.empty()){p.pop_back();p.insert(p.begin(),x);return p;}}return{};}
inline bool has_cycle_through_directed(const vector<vector<int>>&g,int x){return !find_cycle_through_directed(g,x).empty();}
inline vector<int> find_cycle_through_undirected(const vector<vector<int>>&g,int x){
    for(int to:g[x])if(to==x)return{x};
    for(int i=0;i<(int)g[x].size();++i)for(int j=i+1;j<(int)g[x].size();++j){int a=g[x][i],b=g[x][j];auto p=cycle_detail::path(g,a,b,x,{-1,-1},false);if(!p.empty()){p.insert(p.begin(),x);return p;}}
    return{};
}
inline bool has_cycle_through_undirected(const vector<vector<int>>&g,int x){return !find_cycle_through_undirected(g,x).empty();}

inline vector<int> find_cycle_through_edge_directed(const vector<vector<int>>&g,int u,int v){auto p=cycle_detail::path(g,v,u);if(p.empty())return{};p.pop_back();p.insert(p.begin(),u);return p;}
inline bool has_cycle_through_edge_directed(const vector<vector<int>>&g,int u,int v){return !find_cycle_through_edge_directed(g,u,v).empty();}
inline vector<int> find_cycle_through_edge_undirected(const vector<vector<int>>&g,int u,int v){auto p=cycle_detail::path(g,u,v,-1,{u,v},false);return p.empty()?vector<int>{}:p;}
inline bool has_cycle_through_edge_undirected(const vector<vector<int>>&g,int u,int v){return !find_cycle_through_edge_undirected(g,u,v).empty();}

inline vector<int> find_odd_cycle_undirected(const vector<vector<int>>&g){
    int n=g.size();vector<int>color(n,-1),par(n,-1),dep(n);for(int s=0;s<n;++s)if(color[s]<0){queue<int>q;q.push(s);color[s]=0;while(!q.empty()){int v=q.front();q.pop();for(int to:g[v]){if(to==v)return{v};if(color[to]<0)color[to]=color[v]^1,par[to]=v,dep[to]=dep[v]+1,q.push(to);else if(color[to]==color[v]){int a=v,b=to;vector<int>x,y;while(dep[a]>dep[b])x.push_back(a),a=par[a];while(dep[b]>dep[a])y.push_back(b),b=par[b];while(a!=b)x.push_back(a),y.push_back(b),a=par[a],b=par[b];x.push_back(a);reverse(all(y));x.insert(x.end(),all(y));return x;}}}}return{};
}
inline bool has_odd_cycle_undirected(const vector<vector<int>>&g){return !find_odd_cycle_undirected(g).empty();}

inline vector<int> find_even_cycle_undirected(const vector<vector<int>>&g){
    int n=g.size();for(int u=0;u<n;++u)for(int v:g[u])if(u<v){int states=2*n;vector<int>pre(states,-1),pv(states,-1);queue<int>q;int s=2*u;pre[s]=s;q.push(s);while(!q.empty()){int z=q.front();q.pop();int x=z/2,p=z%2;for(int to:g[x]){if((x==u&&to==v)||(x==v&&to==u))continue;int nz=2*to+(p^1);if(pre[nz]<0)pre[nz]=z,pv[nz]=x,q.push(nz);}}int t=2*v+1;if(pre[t]<0)continue;vector<int>p;for(int z=t;;z=pre[z]){p.push_back(z/2);if(z==s)break;}reverse(all(p));if(cycle_detail::distinct(p))return p;}return{};
}
inline bool has_even_cycle_undirected(const vector<vector<int>>&g){return !find_even_cycle_undirected(g).empty();}

inline vector<int> find_shortest_cycle_directed(const vector<vector<int>>&g){vector<int>best;for(int s=0;s<(int)g.size();++s)for(int to:g[s]){auto p=cycle_detail::path(g,to,s);if(!p.empty()){p.pop_back();p.insert(p.begin(),s);if(best.empty()||p.size()<best.size())best=move(p);}}return best;}
inline vector<int> find_shortest_cycle_undirected(const vector<vector<int>>&g){vector<int>best;for(int u=0;u<(int)g.size();++u)for(int v:g[u])if(u<=v){auto p=cycle_detail::path(g,u,v,-1,{u,v},false);if(!p.empty()&&(best.empty()||p.size()<best.size()))best=move(p);}return best;}
inline vector<int> find_cycle_at_most_directed(const vector<vector<int>>&g,int k){auto c=find_shortest_cycle_directed(g);return (int)c.size()<=k?c:vector<int>{};}
inline vector<int> find_cycle_at_most_undirected(const vector<vector<int>>&g,int k){auto c=find_shortest_cycle_undirected(g);return (int)c.size()<=k?c:vector<int>{};}

template<class T=long long> struct BinaryLifting {
    int n=0,log=1;vector<vector<pair<int,T>>>g;vector<vector<int>>up;vector<int>depth;vector<T>root_dist;
    BinaryLifting(int m=0){reset(m);}void reset(int m){n=m;log=1;g.assign(n,{});while((1LL<<log)<=max(1,n))++log;}
    void add_edge(int u,int v,T w=1){g[u].push_back({v,w});g[v].push_back({u,w});}
    void build(int root=0){up.assign(log,vector<int>(n,root));depth.assign(n,-1);root_dist.assign(n,T{});queue<int>q;q.push(root);depth[root]=0;up[0][root]=root;while(!q.empty()){int v=q.front();q.pop();for(auto[to,w]:g[v])if(depth[to]<0)depth[to]=depth[v]+1,root_dist[to]=root_dist[v]+w,up[0][to]=v,q.push(to);}for(int k=1;k<log;++k)for(int v=0;v<n;++v)up[k][v]=up[k-1][up[k-1][v]];}
    int jump(int v,long long k)const{for(int i=0;i<log&&k;++i,k>>=1)if(k&1)v=up[i][v];return v;}
    int lca(int a,int b)const{if(depth[a]<depth[b])swap(a,b);a=jump(a,depth[a]-depth[b]);if(a==b)return a;for(int k=log-1;k>=0;--k)if(up[k][a]!=up[k][b])a=up[k][a],b=up[k][b];return up[0][a];}
    T dist(int a,int b)const{int c=lca(a,b);return root_dist[a]+root_dist[b]-root_dist[c]-root_dist[c];}
};

struct EulerTour {
    int n=0,timer=0;vector<vector<pair<int,long long>>>g;vector<int>in,out,parent;vector<long long>vcost,edge_to_parent;FenwickTree<long long>vsub,vpath,esub,epath;BinaryLifting<long long>bl;
    EulerTour(int m=0):n(m),g(m),vcost(m),edge_to_parent(m),bl(m){}
    void addEdge(int u,int v,long long w=0){g[u].push_back({v,w});g[v].push_back({u,w});bl.add_edge(u,v,w);}
    void addVCost(int v,long long w){vcost[v]=w;}
    void build(int root=0){timer=0;in.assign(n,-1);out.assign(n,-1);parent.assign(n,-1);vector<pair<int,int>>st{{root,0}};parent[root]=root;while(!st.empty()){auto&[v,i]=st.back();if(i==0)in[v]=timer++;if(i==(int)g[v].size()){out[v]=timer;st.pop_back();continue;}auto[to,w]=g[v][i++];if(to==parent[v])continue;parent[to]=v;edge_to_parent[to]=w;st.push_back({to,0});}vector<long long>vs(n),es(n),vp(n+1),ep(n+1);for(int v=0;v<n;++v){vs[in[v]]=vcost[v];es[in[v]]=edge_to_parent[v];vp[in[v]]+=vcost[v];vp[out[v]]-=vcost[v];ep[in[v]]+=edge_to_parent[v];ep[out[v]]-=edge_to_parent[v];}vsub=FenwickTree<long long>(vs);esub=FenwickTree<long long>(es);vpath=FenwickTree<long long>(vp);epath=FenwickTree<long long>(ep);bl.build(root);}
    int lca(int u,int v)const{return bl.lca(u,v);}long long rootE(int v)const{return epath.sum(in[v]+1);}long long rootV(int v)const{return vpath.sum(in[v]+1);}
    long long distE(int u,int v)const{int c=lca(u,v);return rootE(u)+rootE(v)-2*rootE(c);}
    long long partV(int v)const{return vsub.sum(in[v],out[v]);}long long partE(int v)const{return esub.sum(in[v]+1,out[v]);}
    long long distV(int u,int v)const{int c=lca(u,v);return rootV(u)+rootV(v)-2*rootV(c)+vcost[c];}
    void changeECost(int u,int v,long long w){int x=parent[u]==v?u:parent[v]==u?v:-1;assert(x>=0);long long d=w-edge_to_parent[x];edge_to_parent[x]=w;esub.add(in[x],d);epath.add(in[x],d);epath.add(out[x],-d);}
};

struct FunctionalGraph {
    int n=0,log=61;vector<int>to,dist_cycle,cid,entry,component;vector<vector<int>>up,cycles;
    FunctionalGraph()=default;FunctionalGraph(const vector<int>&next){build(next);}
    void build(const vector<int>&next){
        to=next;n=to.size();up.assign(log,vector<int>(n));up[0]=to;for(int k=1;k<log;++k)for(int v=0;v<n;++v)up[k][v]=up[k-1][up[k-1][v]];
        vector<int>deg(n);vector<vector<int>>rev(n);for(int v=0;v<n;++v)++deg[to[v]],rev[to[v]].push_back(v);queue<int>q;vector<char>removed(n);for(int v=0;v<n;++v)if(!deg[v])q.push(v);while(!q.empty()){int v=q.front();q.pop();removed[v]=1;if(!--deg[to[v]])q.push(to[v]);}
        cid.assign(n,-1);entry.assign(n,-1);component.assign(n,-1);dist_cycle.assign(n,-1);cycles.clear();
        for(int s=0;s<n;++s)if(!removed[s]&&cid[s]<0){int id=cycles.size();vector<int>c;for(int v=s;;v=to[v]){cid[v]=component[v]=id;entry[v]=v;dist_cycle[v]=0;c.push_back(v);if(to[v]==s)break;}cycles.push_back(c);}
        queue<int>b;for(auto&c:cycles)for(int v:c)b.push(v);while(!b.empty()){int v=b.front();b.pop();for(int x:rev[v])if(dist_cycle[x]<0)dist_cycle[x]=dist_cycle[v]+1,cid[x]=component[x]=cid[v],entry[x]=entry[v],b.push(x);}
    }
    int jump(int v,unsigned long long k)const{for(int i=0;i<log;++i)if(k>>i&1ULL)v=up[i][v];return v;}
    int dist_to_cycle(int v)const{return dist_cycle[v];}int cycle_id(int v)const{return cid[v];}int entry_vertex(int v)const{return entry[v];}int cycle_size(int v)const{return cycles[cid[v]].size();}
};

template<class T> int lis_length(const vector<T>&a,bool strict=true){vector<T>d;for(auto&x:a){auto it=strict?lower_bound(all(d),x):upper_bound(all(d),x);if(it==d.end())d.push_back(x);else*it=x;}return d.size();}

template<class Seq> auto run_length_encoding(const Seq&s){using T=typename Seq::value_type;vector<pair<T,int>>r;for(auto&x:s){if(r.empty()||r.back().first!=x)r.push_back({x,1});else++r.back().second;}return r;}


template<class Seq> vector<int> z_algorithm(const Seq&s){int n=s.size();vector<int>z(n);if(!n)return z;z[0]=n;for(int i=1,j=0;i<n;){while(i+j<n&&s[j]==s[i+j])++j;z[i]=j;if(!j){++i;continue;}int k=1;while(i+k<n&&k+z[k]<j)z[i+k]=z[k],++k;i+=k;j-=k;}return z;}
template<class Seq> vector<int> prefix_function(const Seq&s){int n=s.size();vector<int>p(n);for(int i=1;i<n;++i){int j=p[i-1];while(j&&s[i]!=s[j])j=p[j-1];if(s[i]==s[j])++j;p[i]=j;}return p;}
template<class Seq> vector<int> kmp_search(const Seq&text,const Seq&pattern){vector<int>res;if(pattern.empty()){for(int i=0;i<=(int)text.size();++i)res.push_back(i);return res;}auto p=prefix_function(pattern);for(int i=0,j=0;i<(int)text.size();++i){while(j&&text[i]!=pattern[j])j=p[j-1];if(text[i]==pattern[j])++j;if(j==(int)pattern.size())res.push_back(i-j+1),j=p[j-1];}return res;}
template<class Seq> vector<int> manacher_odd(const Seq&s){int n=s.size();vector<int>d(n);for(int i=0,l=0,r=-1;i<n;++i){int k=i>r?1:min(d[l+r-i],r-i+1);while(i-k>=0&&i+k<n&&s[i-k]==s[i+k])++k;d[i]=k--;if(i+k>r)l=i-k,r=i+k;}return d;}


struct RollingHash {
    using ull=uint64_t;static constexpr ull mod=(1ULL<<61)-1,base=1000003;
    vector<ull>h,p;static ull add(ull a,ull b){a+=b;return a>=mod?a-mod:a;}static ull mul(ull a,ull b){__uint128_t t=(__uint128_t)a*b;t=(t>>61)+(t&mod);ull r=(ull)t;return r>=mod?r-mod:r;}
    RollingHash()=default;template<class Seq>RollingHash(const Seq&s){int n=s.size();h.assign(n+1,0);p.assign(n+1,1);for(int i=0;i<n;++i)h[i+1]=add(mul(h[i],base),(unsigned long long)s[i]+1),p[i+1]=mul(p[i],base);}
    ull get(int l,int r)const{ull x=add(h[r],mod-mul(h[l],p[r-l]));return x;}static ull concat(ull left,ull right,int right_len,const RollingHash&rh){return add(mul(left,rh.p[right_len]),right);}
};

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return 0;
}
