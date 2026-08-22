#pragma once
#include "../basic/base.hpp"

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

