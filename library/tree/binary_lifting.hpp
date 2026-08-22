#pragma once
#include "../basic/base.hpp"

template<class T=long long> struct BinaryLifting {
    int n=0,log=1;vector<vector<pair<int,T>>>g;vector<vector<int>>up;vector<int>depth;vector<T>root_dist;
    BinaryLifting(int m=0){reset(m);}void reset(int m){n=m;log=1;g.assign(n,{});while((1LL<<log)<=max(1,n))++log;}
    void add_edge(int u,int v,T w=1){g[u].push_back({v,w});g[v].push_back({u,w});}
    void build(int root=0){up.assign(log,vector<int>(n,root));depth.assign(n,-1);root_dist.assign(n,T{});queue<int>q;q.push(root);depth[root]=0;up[0][root]=root;while(!q.empty()){int v=q.front();q.pop();for(auto[to,w]:g[v])if(depth[to]<0)depth[to]=depth[v]+1,root_dist[to]=root_dist[v]+w,up[0][to]=v,q.push(to);}for(int k=1;k<log;++k)for(int v=0;v<n;++v)up[k][v]=up[k-1][up[k-1][v]];}
    int jump(int v,long long k)const{for(int i=0;i<log&&k;++i,k>>=1)if(k&1)v=up[i][v];return v;}
    int lca(int a,int b)const{if(depth[a]<depth[b])swap(a,b);a=jump(a,depth[a]-depth[b]);if(a==b)return a;for(int k=log-1;k>=0;--k)if(up[k][a]!=up[k][b])a=up[k][a],b=up[k][b];return up[0][a];}
    T dist(int a,int b)const{int c=lca(a,b);return root_dist[a]+root_dist[b]-root_dist[c]-root_dist[c];}
};
