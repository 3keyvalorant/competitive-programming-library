#include "../library/basic/prefix_sum.hpp"
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);int n,q;cin>>n>>q;vector<long long>a(n);for(auto&x:a)cin>>x;auto s=prefix_sum(a);while(q--){int l,r;cin>>l>>r;cout<<range_sum(s,l,r)<<'\n';}}

