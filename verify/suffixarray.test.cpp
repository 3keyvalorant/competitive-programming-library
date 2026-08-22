#include "../library/string/suffix_array.hpp"
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);string s;cin>>s;auto sa=suffix_array(s);for(int i=0;i<(int)sa.size();++i)cout<<sa[i]<<" \n"[i+1==(int)sa.size()];}

