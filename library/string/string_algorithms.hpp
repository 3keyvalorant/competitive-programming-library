#pragma once
#include "../basic/base.hpp"

template<class Seq> vector<int> z_algorithm(const Seq&s){int n=s.size();vector<int>z(n);if(!n)return z;z[0]=n;for(int i=1,j=0;i<n;){while(i+j<n&&s[j]==s[i+j])++j;z[i]=j;if(!j){++i;continue;}int k=1;while(i+k<n&&k+z[k]<j)z[i+k]=z[k],++k;i+=k;j-=k;}return z;}
template<class Seq> vector<int> prefix_function(const Seq&s){int n=s.size();vector<int>p(n);for(int i=1;i<n;++i){int j=p[i-1];while(j&&s[i]!=s[j])j=p[j-1];if(s[i]==s[j])++j;p[i]=j;}return p;}
template<class Seq> vector<int> kmp_search(const Seq&text,const Seq&pattern){vector<int>res;if(pattern.empty()){for(int i=0;i<=(int)text.size();++i)res.push_back(i);return res;}auto p=prefix_function(pattern);for(int i=0,j=0;i<(int)text.size();++i){while(j&&text[i]!=pattern[j])j=p[j-1];if(text[i]==pattern[j])++j;if(j==(int)pattern.size())res.push_back(i-j+1),j=p[j-1];}return res;}
template<class Seq> vector<int> manacher_odd(const Seq&s){int n=s.size();vector<int>d(n);for(int i=0,l=0,r=-1;i<n;++i){int k=i>r?1:min(d[l+r-i],r-i+1);while(i-k>=0&&i+k<n&&s[i-k]==s[i+k])++k;d[i]=k--;if(i+k>r)l=i-k,r=i+k;}return d;}

