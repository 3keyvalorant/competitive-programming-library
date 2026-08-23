#include "../library/math/convolution.hpp"
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);int n,m;cin>>n>>m;vector<mint>a(n),b(m);for(auto&x:a)cin>>x;for(auto&x:b)cin>>x;auto c=convolution(a,b);for(int i=0;i<(int)c.size();++i)cout<<c[i]<<" \n"[i+1==(int)c.size()];}

