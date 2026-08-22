#include "../library/graph/two_sat.hpp"
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);string p,cnf;int n,m;cin>>p>>cnf>>n>>m;TwoSAT sat(n);while(m--){int a,b,z;cin>>a>>b>>z;sat.add_clause(abs(a)-1,a>0,abs(b)-1,b>0);}if(!sat.satisfiable()){cout<<"s UNSATISFIABLE\n";return 0;}cout<<"s SATISFIABLE\nv";auto ans=sat.answer();for(int i=0;i<n;++i)cout<<' '<<(ans[i]?i+1:-i-1);cout<<" 0\n";}

