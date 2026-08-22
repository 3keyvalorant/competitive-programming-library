#pragma once
#include "../basic/base.hpp"

template<class DP, class Cost, DP (*merge_dp)(DP,DP), DP (*identity_dp)(), DP (*add_edge_dp)(DP,Cost), DP (*add_vertex_dp)(DP,int)>
struct Rerooting {
    struct Edge { int to; Cost cost; };
    int n; vector<vector<Edge>> g; vector<DP> answer;
    Rerooting(int m = 0) : n(m), g(m) {}
    void add_edge(int u, int v, Cost cost = Cost{}){ g[u].push_back({v,cost}); g[v].push_back({u,cost}); }
    const vector<DP>& build(int root = 0){
        vector<int> parent(n, -1), order{root}; vector<Cost> parent_cost(n);
        parent[root] = root;
        for (int i = 0; i < (int)order.size(); ++i) for (auto [to,c] : g[order[i]]) if (parent[to] < 0)
            parent[to] = order[i], parent_cost[to] = c, order.push_back(to);
        vector<DP> down(n, identity_dp()), from_parent(n, identity_dp());
        for (int i = n - 1; i >= 0; --i){ int v = order[i]; DP x = identity_dp(); for (auto [to,c] : g[v]) if (parent[to] == v) x = merge_dp(x, add_edge_dp(down[to], c)); down[v] = add_vertex_dp(x, v); }
        answer.assign(n, identity_dp());
        for (int v : order){
            int m = g[v].size(); vector<DP> pref(m + 1, identity_dp()), suff(m + 1, identity_dp());
            for (int i = 0; i < m; ++i){ auto [to,c] = g[v][i]; DP x = to == parent[v] ? from_parent[v] : add_edge_dp(down[to], c); pref[i + 1] = merge_dp(pref[i], x); }
            for (int i = m - 1; i >= 0; --i){ auto [to,c] = g[v][i]; DP x = to == parent[v] ? from_parent[v] : add_edge_dp(down[to], c); suff[i] = merge_dp(x, suff[i + 1]); }
            answer[v] = add_vertex_dp(pref[m], v);
            for (int i = 0; i < m; ++i){ auto [to,c] = g[v][i]; if (parent[to] == v) from_parent[to] = add_edge_dp(add_vertex_dp(merge_dp(pref[i], suff[i + 1]), v), c); }
        }
        return answer;
    }
};
