#pragma once
#include "../basic/base.hpp"

inline vector<int> bfs(const vector<vector<int>>& g, const vector<int>& starts){
    vector<int> d(g.size(), -1); queue<int> q; for (int s : starts) if (d[s] < 0) d[s] = 0, q.push(s);
    while (!q.empty()){ int v = q.front(); q.pop(); for (int to : g[v]) if (d[to] < 0) d[to] = d[v] + 1, q.push(to); }
    return d;
}
inline vector<int> bfs(const vector<vector<int>>& g, int s){ return bfs(g, vector<int>{s}); }

template<class T> vector<T> bfs01(const vector<vector<pair<int,T>>>& g, int s){
    const T infinity = numeric_limits<T>::max() / 4; vector<T> d(g.size(), infinity); deque<int> q; d[s] = 0; q.push_back(s);
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
        start = s; T infinity = numeric_limits<T>::max() / 4; dist.assign(n, infinity); prev.assign(n, -1); minpq<pair<T,int>> q; dist[s] = 0; q.push({0,s});
        while (!q.empty()){ auto [d,v] = q.top(); q.pop(); if (d != dist[v]) continue; for (auto [to,w] : g[v]) if (chmin(dist[to], d+w)) prev[to] = v, q.push({dist[to],to}); }
        return dist;
    }
    T output(int v) const { return dist[v]; }
    vector<int> path(int v) const { if (dist.empty() || dist[v] == numeric_limits<T>::max()/4) return {}; vector<int> p; for (; v != -1; v = prev[v]) p.push_back(v); reverse(all(p)); return p; }
};

template<class T> struct BellmanFordResult { vector<T> dist; vector<char> negative; bool has_negative_cycle; };
template<class T> BellmanFordResult<T> bellman_ford(int n, const vector<tuple<int,int,T>>& edges, int s){
    T infinity = numeric_limits<T>::max()/4; vector<T> d(n,infinity); vector<char> neg(n); d[s]=0;
    for (int i=0;i<n;++i) for (auto [u,v,w]:edges) if (d[u]!=infinity && d[v]>max(-infinity,d[u]+w)){ d[v]=max(-infinity,d[u]+w); if(i==n-1) neg[v]=1; }
    for(int i=0;i<n;++i) for(auto [u,v,w]:edges) if(neg[u]) neg[v]=1;
    return {d,neg,any_of(all(neg),[](char x){return x;})};
}

template<class T> void floyd_warshall(vector<vector<T>>& d){
    int n=d.size(); T infinity=numeric_limits<T>::max()/4;
    for(int k=0;k<n;++k)for(int i=0;i<n;++i)if(d[i][k]!=infinity)for(int j=0;j<n;++j)if(d[k][j]!=infinity)chmin(d[i][j],d[i][k]+d[k][j]);
}

inline optional<vector<int>> topological_sort(const vector<vector<int>>& g){
    int n=g.size(); vector<int> deg(n),res; for(auto& es:g)for(int v:es)++deg[v]; queue<int>q; for(int i=0;i<n;++i)if(!deg[i])q.push(i);
    while(!q.empty()){int v=q.front();q.pop();res.push_back(v);for(int to:g[v])if(!--deg[to])q.push(to);} if((int)res.size()!=n)return nullopt; return res;
}
