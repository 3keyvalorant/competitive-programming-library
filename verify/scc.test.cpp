#include "../library/graph/scc.hpp"
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);int n,m;cin>>n>>m;SCC s(n);while(m--){int u,v;cin>>u>>v;s.add_edge(u,v);}s.do_scc();cout<<s.groups.size()<<'\n';for(auto&g:s.groups){cout<<g.size();for(int v:g)cout<<' '<<v;cout<<'\n';}}

