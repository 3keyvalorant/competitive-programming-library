#include "../library/data_structure/union_find.hpp"
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);int n,q;cin>>n>>q;UnionFind uf(n);while(q--){int t,u,v;cin>>t>>u>>v;if(t)cout<<uf.same(u,v)<<'\n';else uf.merge(u,v);}}

