#pragma once
#include "../basic/base.hpp"

struct RollbackUnionFind {
    vector<int> p; vector<pair<int,int>> history; int components = 0;
    RollbackUnionFind(int n = 0){ reset(n); }
    void reset(int n){ p.assign(n, -1); history.clear(); components = n; }
    int leader(int v) const { while (p[v] >= 0) v = p[v]; return v; }
    bool same(int u, int v) const { return leader(u) == leader(v); }
    int size(int v) const { return -p[leader(v)]; }
    bool merge(int u, int v){
        u = leader(u); v = leader(v); if (u == v){ history.push_back({-1,-1}); return false; }
        if (-p[u] < -p[v]) swap(u, v);
        history.push_back({u,p[u]}); history.push_back({v,p[v]}); p[u] += p[v]; p[v] = u; --components; return true;
    }
    int snapshot() const { return history.size(); }
    void undo(){ assert(!history.empty()); if (history.back().first < 0){ history.pop_back(); return; } auto [v,pv] = history.back(); history.pop_back(); auto [u,pu] = history.back(); history.pop_back(); p[u] = pu; p[v] = pv; ++components; }
    void rollback(int state){ assert(0 <= state && state <= (int)history.size()); while ((int)history.size() > state) undo(); }
};
