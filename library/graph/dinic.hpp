#pragma once
#include "../basic/base.hpp"

template<class T> struct Dinic {
    struct Edge{int to,rev;T cap;}; int n;vector<vector<Edge>>g;vector<int>level,it;
    Dinic(int m=0):n(m),g(m),level(m),it(m){}
    void add_edge(int u,int v,T cap){int a=g[u].size(),b=g[v].size();g[u].push_back({v,b,cap});g[v].push_back({u,a,T{}});}
    bool bfs_level(int s,int t){fill(all(level),-1);queue<int>q;q.push(s);level[s]=0;while(!q.empty()){int v=q.front();q.pop();for(auto&e:g[v])if(e.cap>0&&level[e.to]<0)level[e.to]=level[v]+1,q.push(e.to);}return level[t]>=0;}
    T dfs(int v,int t,T f){if(v==t)return f;for(int&i=it[v];i<(int)g[v].size();++i){Edge&e=g[v][i];if(e.cap>0&&level[v]<level[e.to]){T d=dfs(e.to,t,min(f,e.cap));if(d>0){e.cap-=d;g[e.to][e.rev].cap+=d;return d;}}}return T{};}
    T flow(int s,int t,T limit=numeric_limits<T>::max()){T res{};while(res<limit&&bfs_level(s,t)){fill(all(it),0);while(T f=dfs(s,t,limit-res))res+=f;}return res;}
};
