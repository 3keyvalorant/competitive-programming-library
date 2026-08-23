#pragma once
#include "../basic/base.hpp"

template<class Cap, class Cost> struct MinCostFlow {
    struct Edge { int to, rev; Cap cap; Cost cost; };
    int n; vector<vector<Edge>> g;
    MinCostFlow(int m = 0) : n(m), g(m) {}
    void add_edge(int u, int v, Cap cap, Cost cost){ int a = g[u].size(), b = g[v].size(); g[u].push_back({v,b,cap,cost}); g[v].push_back({u,a,Cap{},-cost}); }
    pair<Cap,Cost> flow(int s, int t, Cap limit = numeric_limits<Cap>::max()){
        const Cost infinity = numeric_limits<Cost>::max() / 4; vector<Cost> h(n, infinity); h[s] = 0;
        for (int it = 0; it < n; ++it){ bool changed = false; for (int v = 0; v < n; ++v) if (h[v] != infinity) for (auto& e : g[v]) if (e.cap > 0 && h[e.to] > h[v] + e.cost) h[e.to] = h[v] + e.cost, changed = true; if (!changed) break; }
        for (Cost& x : h) if (x == infinity) x = 0;
        Cap sent{}; Cost total{}; vector<Cost> dist(n); vector<int> pv(n), pe(n);
        while (sent < limit){
            fill(all(dist), infinity); dist[s] = 0; minpq<pair<Cost,int>> q; q.push({0,s});
            while (!q.empty()){
                auto [d,v] = q.top(); q.pop(); if (d != dist[v]) continue;
                for (int i = 0; i < (int)g[v].size(); ++i){ auto& e = g[v][i]; Cost nd = d + e.cost + h[v] - h[e.to]; if (e.cap > 0 && chmin(dist[e.to], nd)) pv[e.to] = v, pe[e.to] = i, q.push({nd,e.to}); }
            }
            if (dist[t] == infinity) break;
            for (int v = 0; v < n; ++v) if (dist[v] != infinity) h[v] += dist[v];
            Cap add = limit - sent; for (int v = t; v != s; v = pv[v]) chmin(add, g[pv[v]][pe[v]].cap);
            sent += add; total += (Cost)add * h[t];
            for (int v = t; v != s; v = pv[v]){ Edge& e = g[pv[v]][pe[v]]; e.cap -= add; g[v][e.rev].cap += add; }
        }
        return {sent,total};
    }
};
