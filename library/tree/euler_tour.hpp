#pragma once
#include "binary_lifting.hpp"
#include "../data_structure/fenwick_tree.hpp"

struct EulerTour {
    int n=0,timer=0;vector<vector<pair<int,long long>>>g;vector<int>in,out,parent;vector<long long>vcost,edge_to_parent;FenwickTree<long long>vsub,vpath,esub,epath;BinaryLifting<long long>bl;
    EulerTour(int m=0):n(m),g(m),vcost(m),edge_to_parent(m),bl(m){}
    void addEdge(int u,int v,long long w=0){g[u].push_back({v,w});g[v].push_back({u,w});bl.add_edge(u,v,w);}
    void addVCost(int v,long long w){vcost[v]=w;}
    void build(int root=0){timer=0;in.assign(n,-1);out.assign(n,-1);parent.assign(n,-1);vector<pair<int,int>>st{{root,0}};parent[root]=root;while(!st.empty()){auto&[v,i]=st.back();if(i==0)in[v]=timer++;if(i==(int)g[v].size()){out[v]=timer;st.pop_back();continue;}auto[to,w]=g[v][i++];if(to==parent[v])continue;parent[to]=v;edge_to_parent[to]=w;st.push_back({to,0});}vector<long long>vs(n),es(n),vp(n+1),ep(n+1);for(int v=0;v<n;++v){vs[in[v]]=vcost[v];es[in[v]]=edge_to_parent[v];vp[in[v]]+=vcost[v];vp[out[v]]-=vcost[v];ep[in[v]]+=edge_to_parent[v];ep[out[v]]-=edge_to_parent[v];}vsub=FenwickTree<long long>(vs);esub=FenwickTree<long long>(es);vpath=FenwickTree<long long>(vp);epath=FenwickTree<long long>(ep);bl.build(root);}
    int lca(int u,int v)const{return bl.lca(u,v);}long long rootE(int v)const{return epath.sum(in[v]+1);}long long rootV(int v)const{return vpath.sum(in[v]+1);}
    long long distE(int u,int v)const{int c=lca(u,v);return rootE(u)+rootE(v)-2*rootE(c);}
    long long partV(int v)const{return vsub.sum(in[v],out[v]);}long long partE(int v)const{return esub.sum(in[v]+1,out[v]);}
    long long distV(int u,int v)const{int c=lca(u,v);return rootV(u)+rootV(v)-2*rootV(c)+vcost[c];}
    void changeECost(int u,int v,long long w){int x=parent[u]==v?u:parent[v]==u?v:-1;assert(x>=0);long long d=w-edge_to_parent[x];edge_to_parent[x]=w;esub.add(in[x],d);epath.add(in[x],d);epath.add(out[x],-d);}
};
