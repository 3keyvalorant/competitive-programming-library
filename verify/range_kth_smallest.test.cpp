#include "../library/data_structure/wavelet_matrix.hpp"
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);int n,q;cin>>n>>q;vector<unsigned>a(n);for(auto&x:a)cin>>x;WaveletMatrix<unsigned,30>wm(a);while(q--){int l,r,k;cin>>l>>r>>k;cout<<wm.kth_smallest(l,r,k)<<'\n';}}
