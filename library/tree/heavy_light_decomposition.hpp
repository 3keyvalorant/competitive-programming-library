#pragma once
#include "../basic/base.hpp"

struct HeavyLightDecomposition {
    int n = 0, timer = 0;
    vector<vector<int>> g;
    vector<int> parent, depth, sub, heavy, head, in, rev;

    HeavyLightDecomposition(int m = 0) : n(m), g(m) {}
    void add_edge(int u, int v){ g[u].push_back(v); g[v].push_back(u); }

    void build(int root = 0){
        parent.assign(n, -1); depth.assign(n, 0); sub.assign(n, 1); heavy.assign(n, -1);
        vector<int> order{root}; parent[root] = root;
        for (int i = 0; i < (int)order.size(); ++i){
            int v = order[i];
            for (int to : g[v]) if (to != parent[v]) parent[to] = v, depth[to] = depth[v] + 1, order.push_back(to);
        }
        assert((int)order.size() == n);
        for (int i = n - 1; i > 0; --i){
            int v = order[i], p = parent[v]; sub[p] += sub[v];
            if (heavy[p] < 0 || sub[heavy[p]] < sub[v]) heavy[p] = v;
        }
        timer = 0; head.assign(n, 0); in.assign(n, 0); rev.assign(n, 0);
        vector<pair<int,int>> chains{{root, root}};
        while (!chains.empty()){
            auto [v, h] = chains.back(); chains.pop_back();
            for (; v != -1; v = heavy[v]){
                head[v] = h; in[v] = timer; rev[timer++] = v;
                for (int to : g[v]) if (to != parent[v] && to != heavy[v]) chains.push_back({to, to});
            }
        }
    }
    int lca(int u, int v) const {
        while (head[u] != head[v]){ if (depth[head[u]] < depth[head[v]]) swap(u, v); u = parent[head[u]]; }
        return depth[u] < depth[v] ? u : v;
    }
    int dist(int u, int v) const { int w = lca(u, v); return depth[u] + depth[v] - 2 * depth[w]; }
    pair<int,int> subtree(int v, bool edge = false) const { return {in[v] + edge, in[v] + sub[v]}; }
    template<class F> void for_each_path(int u, int v, F f, bool edge = false) const {
        while (head[u] != head[v]){
            if (depth[head[u]] < depth[head[v]]) swap(u, v);
            f(in[head[u]], in[u] + 1); u = parent[head[u]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        if (in[u] + edge < in[v] + 1) f(in[u] + edge, in[v] + 1);
    }
};
