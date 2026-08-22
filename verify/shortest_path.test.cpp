#include "../library/graph/shortest_path.hpp"
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);int n,m,s,t;cin>>n>>m>>s>>t;Dijkstra<long long>d(n);while(m--){int u,v;long long w;cin>>u>>v>>w;d.make_directedgraph(u,v,w);}d.do_dijkstra(s);auto p=d.path(t);if(p.empty()){cout<<-1<<'\n';return 0;}cout<<d.output(t)<<' '<<p.size()-1<<'\n';for(int i=1;i<(int)p.size();++i)cout<<p[i-1]<<' '<<p[i]<<'\n';}

