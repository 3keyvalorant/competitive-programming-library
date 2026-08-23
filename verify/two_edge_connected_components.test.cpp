#include "../library/graph/two_edge_connected_components.hpp"
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);int n,m;cin>>n>>m;TwoEdgeConnectedComponents tecc(n);while(m--){int u,v;cin>>u>>v;tecc.add_edge(u,v);}tecc.build();cout<<tecc.groups.size()<<'\n';for(auto&g:tecc.groups){cout<<g.size();for(int v:g)cout<<' '<<v;cout<<'\n';}}

