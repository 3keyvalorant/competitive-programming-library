#pragma once
#include "../basic/base.hpp"

struct FunctionalGraph {
    int n=0,log=61;vector<int>to,dist_cycle,cid,entry,component;vector<vector<int>>up,cycles;
    FunctionalGraph()=default;FunctionalGraph(const vector<int>&next){build(next);}
    void build(const vector<int>&next){
        to=next;n=to.size();up.assign(log,vector<int>(n));up[0]=to;for(int k=1;k<log;++k)for(int v=0;v<n;++v)up[k][v]=up[k-1][up[k-1][v]];
        vector<int>deg(n);vector<vector<int>>rev(n);for(int v=0;v<n;++v)++deg[to[v]],rev[to[v]].push_back(v);queue<int>q;vector<char>removed(n);for(int v=0;v<n;++v)if(!deg[v])q.push(v);while(!q.empty()){int v=q.front();q.pop();removed[v]=1;if(!--deg[to[v]])q.push(to[v]);}
        cid.assign(n,-1);entry.assign(n,-1);component.assign(n,-1);dist_cycle.assign(n,-1);cycles.clear();
        for(int s=0;s<n;++s)if(!removed[s]&&cid[s]<0){int id=cycles.size();vector<int>c;for(int v=s;;v=to[v]){cid[v]=component[v]=id;entry[v]=v;dist_cycle[v]=0;c.push_back(v);if(to[v]==s)break;}cycles.push_back(c);}
        queue<int>b;for(auto&c:cycles)for(int v:c)b.push(v);while(!b.empty()){int v=b.front();b.pop();for(int x:rev[v])if(dist_cycle[x]<0)dist_cycle[x]=dist_cycle[v]+1,cid[x]=component[x]=cid[v],entry[x]=entry[v],b.push(x);}
    }
    int jump(int v,unsigned long long k)const{for(int i=0;i<log;++i)if(k>>i&1ULL)v=up[i][v];return v;}
    int dist_to_cycle(int v)const{return dist_cycle[v];}int cycle_id(int v)const{return cid[v];}int entry_vertex(int v)const{return entry[v];}int cycle_size(int v)const{return cycles[cid[v]].size();}
};

