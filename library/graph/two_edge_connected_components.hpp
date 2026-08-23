#pragma once
#include "lowlink.hpp"

struct TwoEdgeConnectedComponents {
    LowLink lowlink; vector<int> comp; vector<vector<int>> groups, forest;
    TwoEdgeConnectedComponents(int n = 0) : lowlink(n) {}
    int add_edge(int u, int v){ return lowlink.add_edge(u, v); }
    int build(){
        lowlink.build(); int n = lowlink.n; vector<char> bridge(lowlink.edges.size()); for (int id : lowlink.bridges) bridge[id] = true;
        comp.assign(n, -1); groups.clear();
        for (int s = 0; s < n; ++s) if (comp[s] < 0){ int id = groups.size(); groups.push_back({}); queue<int> q; q.push(s); comp[s] = id; while (!q.empty()){ int v = q.front(); q.pop(); groups[id].push_back(v); for (auto [to,e] : lowlink.g[v]) if (!bridge[e] && comp[to] < 0) comp[to] = id, q.push(to); } }
        forest.assign(groups.size(), {}); for (int id : lowlink.bridges){ auto [u,v] = lowlink.edges[id]; int a = comp[u], b = comp[v]; forest[a].push_back(b); forest[b].push_back(a); }
        return groups.size();
    }
};

