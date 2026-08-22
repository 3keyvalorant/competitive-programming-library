#pragma once
#include "scc.hpp"

struct TwoSAT {
    int n; SCC scc; vector<bool> ans;
    TwoSAT(int m=0):n(m),scc(2*m),ans(m){}
    int id(int i,bool f)const{return 2*i+(f?0:1);}
    void add_clause(int i,bool f,int j,bool g){scc.add_edge(id(i,!f),id(j,g));scc.add_edge(id(j,!g),id(i,f));}
    bool satisfiable(){scc.do_scc();for(int i=0;i<n;++i){if(scc.comp[id(i,0)]==scc.comp[id(i,1)])return false;ans[i]=scc.comp[id(i,1)]>scc.comp[id(i,0)];}return true;}
    vector<bool> answer()const{return ans;}
};
