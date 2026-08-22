#pragma once
#include "../basic/base.hpp"

struct LowLink {
    int n, timer = 0; vector<pair<int,int>> edges; vector<vector<pair<int,int>>> g;
    vector<int> ord, low, parent; vector<char> articulation; vector<int> bridges;
    LowLink(int m = 0) : n(m), g(m) {}
    int add_edge(int u, int v){ int id = edges.size(); edges.push_back({u,v}); g[u].push_back({v,id}); g[v].push_back({u,id}); return id; }
    void build(){
        ord.assign(n, -1); low.resize(n); parent.assign(n, -1); articulation.assign(n, false); bridges.clear(); timer = 0;
        vector<int> parent_edge(n, -1), children(n);
        for (int root = 0; root < n; ++root) if (ord[root] < 0){
            ord[root] = low[root] = timer++;
            vector<pair<int,int>> st{{root,0}};
            while (!st.empty()){
                int v = st.back().first; int& i = st.back().second;
                if (i < (int)g[v].size()){
                    auto [to,id] = g[v][i++]; if (id == parent_edge[v]) continue;
                    if (ord[to] < 0){ parent[to] = v; parent_edge[to] = id; ++children[v]; ord[to] = low[to] = timer++; st.push_back({to,0}); }
                    else low[v] = min(low[v], ord[to]);
                } else {
                    st.pop_back();
                    if (parent[v] >= 0){ int p = parent[v]; low[p] = min(low[p], low[v]); if (low[v] > ord[p]) bridges.push_back(parent_edge[v]); if (parent[p] >= 0 && low[v] >= ord[p]) articulation[p] = true; }
                }
            }
            articulation[root] = children[root] >= 2;
        }
        sort(all(bridges));
    }
    vector<int> articulation_points() const { vector<int> res; for (int v = 0; v < n; ++v) if (articulation[v]) res.push_back(v); return res; }
    vector<pair<int,int>> bridge_edges() const { vector<pair<int,int>> res; for (int id : bridges) res.push_back(edges[id]); return res; }
};
