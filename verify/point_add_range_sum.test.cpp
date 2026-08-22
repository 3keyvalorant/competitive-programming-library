#include "../library/data_structure/fenwick_tree.hpp"
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);int n,q;cin>>n>>q;vector<long long>a(n);for(auto&x:a)cin>>x;FenwickTree<long long>fw(a);while(q--){int t,l,r;cin>>t>>l>>r;if(t)cout<<fw.sum(l,r)<<'\n';else fw.add(l,r);}}

