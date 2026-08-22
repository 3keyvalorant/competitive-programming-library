#pragma once
#include "../data_structure/union_find.hpp"

template<class T> struct KruskalResult{T cost{};vector<tuple<int,int,T>> edges;bool connected=false;};
template<class T> KruskalResult<T> kruskal(int n,vector<tuple<int,int,T>> edges){
    sort(all(edges),[](auto&a,auto&b){return get<2>(a)<get<2>(b);});UnionFind uf(n);KruskalResult<T>r;
    for(auto[u,v,w]:edges)if(uf.merge(u,v)){r.cost+=w;r.edges.push_back({u,v,w});}
    r.connected=n==0||(int)r.edges.size()==n-1;return r;
}
