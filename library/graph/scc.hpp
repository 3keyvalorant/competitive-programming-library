#pragma once
#include "../basic/base.hpp"

struct SCC {
    int n=0,scc_count=0; vector<vector<int>> g,rg,groups,dag; vector<int> comp,indeg,outdeg;
    SCC(int m=0){reset(m);} void reset(int m){n=m;g.assign(n,{});rg.assign(n,{});}
    void add_edge(int u,int v){g[u].push_back(v);rg[v].push_back(u);}
    int do_scc(){
        vector<char> used(n); vector<int> order;
        for(int s=0;s<n;++s)if(!used[s]){ vector<pair<int,int>> st{{s,0}};used[s]=1; while(!st.empty()){auto&[v,i]=st.back();if(i<(int)g[v].size()){int to=g[v][i++];if(!used[to])used[to]=1,st.push_back({to,0});}else order.push_back(v),st.pop_back();}}
        comp.assign(n,-1);scc_count=0;reverse(all(order)); for(int s:order)if(comp[s]<0){stack<int>st;st.push(s);comp[s]=scc_count;while(!st.empty()){int v=st.top();st.pop();for(int to:rg[v])if(comp[to]<0)comp[to]=scc_count,st.push(to);}++scc_count;}
        groups.assign(scc_count,{});for(int v=0;v<n;++v)groups[comp[v]].push_back(v);dag.assign(scc_count,{});indeg.assign(scc_count,0);outdeg.assign(scc_count,0);
        vector<pair<int,int>> es;for(int v=0;v<n;++v)for(int to:g[v])if(comp[v]!=comp[to])es.push_back({comp[v],comp[to]});sort(all(es));es.erase(unique(all(es)),es.end());for(auto[a,b]:es)dag[a].push_back(b),++outdeg[a],++indeg[b];
        return scc_count;
    }
};
