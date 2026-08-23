#pragma once
#include "base.hpp"

using pii = pair<int,int>;
using pll = pair<long long,long long>;
using vi = vector<int>;
using vll = vector<long long>;
using vvi = vector<vector<int>>;
using vvll = vector<vector<long long>>;

#define reps(i,l,r) for (long long i = (long long)(l); i < (long long)(r); ++i)
#define rrep(i,n) for (long long i = (long long)(n) - 1; i >= 0; --i)
#define each(x,a) for (auto& x : (a))

constexpr int di4[] = {-1,0,1,0};
constexpr int dj4[] = {0,1,0,-1};
constexpr int di8[] = {-1,-1,0,1,1,1,0,-1};
constexpr int dj8[] = {0,1,1,1,0,-1,-1,-1};

template<class C> int sz(const C& c){ return (int)c.size(); }

template<class T> void scan(T& x){ cin >> x; }
template<class T, class U> void scan(pair<T,U>& p){ scan(p.first); scan(p.second); }
template<class T> void scan(vector<T>& a){ for (auto& x : a) scan(x); }
template<class T, class U, class... Ts> void scan(T& x, U& y, Ts&... xs){ scan(x); scan(y, xs...); }
template<class T> void scan1(T& x){ scan(x); --x; }
template<class T, class... Ts> void scan1(T& x, Ts&... xs){ scan1(x); scan1(xs...); }

template<class T> vector<T> read_vector(int n){ vector<T> a(n); scan(a); return a; }
template<class T> vector<vector<T>> read_matrix(int h, int w){ vector a(h, vector<T>(w)); scan(a); return a; }
inline vector<string> read_grid(int h){ return read_vector<string>(h); }

template<class T, class... Ts> void print(const T& x, const Ts&... xs){ cout << x; ((cout << ' ' << xs), ...); cout << '\n'; }
template<class T> void print(const vector<T>& a, char separator = ' '){ for (int i = 0; i < sz(a); ++i) cout << a[i] << (i + 1 == sz(a) ? '\n' : separator); if (a.empty()) cout << '\n'; }

inline vector<vector<int>> read_graph(int n, int m, bool directed = false, int index_base = 1){
    vector<vector<int>> g(n); while (m--){ int u,v; scan(u,v); u -= index_base; v -= index_base; g[u].push_back(v); if (!directed) g[v].push_back(u); } return g;
}
inline vector<vector<int>> read_tree(int n, int index_base = 1){ return read_graph(n,n-1,false,index_base); }
template<class T> vector<vector<pair<int,T>>> read_weighted_graph(int n, int m, bool directed = false, int index_base = 1){
    vector<vector<pair<int,T>>> g(n); while (m--){ int u,v; T w; scan(u,v,w); u -= index_base; v -= index_base; g[u].push_back({v,w}); if (!directed) g[v].push_back({u,w}); } return g;
}
template<class T> vector<vector<pair<int,T>>> read_weighted_tree(int n, int index_base = 1){ return read_weighted_graph<T>(n,n-1,false,index_base); }

template<class T> void sort_unique(vector<T>& a){ sort(all(a)); a.erase(unique(all(a)), a.end()); }
template<class C> void st(C& a){ sort(all(a)); }
template<class C> void rst(C& a){ sort(rall(a)); }
template<class C> void rev(C& a){ reverse(all(a)); }
template<class T> void unq(vector<T>& a){ a.erase(unique(all(a)), a.end()); }
template<class T> vector<T> sorted(vector<T> a){ sort(all(a)); return a; }
template<class T> vector<T> sorted_unique(vector<T> a){ sort_unique(a); return a; }
template<class T> vector<T> reversed(vector<T> a){ reverse(all(a)); return a; }
template<class T = int> vector<T> indices(int n, T first = T{}){ vector<T> p(n); iota(all(p),first); return p; }
template<class T> vector<int> argsort(const vector<T>& a){ vector<int> p(a.size()); iota(all(p),0); stable_sort(all(p),[&](int i,int j){ return a[i] < a[j]; }); return p; }
inline vector<int> inverse_permutation(const vector<int>& p){ vector<int> inv(p.size()); for (int i = 0; i < sz(p); ++i) inv[p[i]] = i; return inv; }
template<class T> map<T,int> counter(const vector<T>& a){ map<T,int> res; for (auto& x : a) ++res[x]; return res; }
inline int mex(const vector<int>& a){ vector<char> seen(a.size() + 1); for (int x : a) if (0 <= x && x <= sz(a)) seen[x] = true; return find(all(seen),false) - seen.begin(); }
template<class T> T sum(const vector<T>& a){ return accumulate(all(a),T{}); }
template<class T> T min_value(const vector<T>& a){ assert(!a.empty()); return *min_element(all(a)); }
template<class T> T max_value(const vector<T>& a){ assert(!a.empty()); return *max_element(all(a)); }
inline int bit_count(unsigned long long x){ return __builtin_popcountll(x); }
template<class Graph> vector<int> degrees(const Graph& g){ vector<int> d(g.size()); for (int v = 0; v < sz(g); ++v) d[v] = sz(g[v]); return d; }

template<class T> T floor_div(T a, T b){ assert(b != 0); T q = a / b, r = a % b; return q - (r != 0 && ((r > 0) != (b > 0))); }
template<class T> T mod_floor(T a, T b){ assert(b != 0); T r = a % b; if (r != 0 && ((r > 0) != (b > 0))) r += b; return r; }

template<class T> auto make_vec(size_t n, const T& value){ return vector<T>(n, value); }
template<class... Args, enable_if_t<(sizeof...(Args) > 0),int> = 0> auto make_vec(size_t n, size_t m, Args... args){ return vector(n, make_vec(m, args...)); }

template<class Int, class F> Int first_true(Int l, Int r, F f){ while (l < r){ Int m = l + (r - l) / 2; if (f(m)) r = m; else l = m + 1; } return l; }
template<class Int, class F> Int last_true(Int l, Int r, F f){ static_assert(is_signed<Int>::value); Int x = first_true(l,r,[&](Int v){ return !f(v); }); return x - 1; }
