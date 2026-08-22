#pragma once
#include "../basic/base.hpp"

struct RollingHash {
    using ull=uint64_t;static constexpr ull mod=(1ULL<<61)-1,base=1000003;
    vector<ull>h,p;static ull add(ull a,ull b){a+=b;return a>=mod?a-mod:a;}static ull mul(ull a,ull b){__uint128_t t=(__uint128_t)a*b;t=(t>>61)+(t&mod);ull r=(ull)t;return r>=mod?r-mod:r;}
    RollingHash()=default;template<class Seq>RollingHash(const Seq&s){int n=s.size();h.assign(n+1,0);p.assign(n+1,1);for(int i=0;i<n;++i)h[i+1]=add(mul(h[i],base),(unsigned long long)s[i]+1),p[i+1]=mul(p[i],base);}
    ull get(int l,int r)const{ull x=add(h[r],mod-mul(h[l],p[r-l]));return x;}static ull concat(ull left,ull right,int right_len,const RollingHash&rh){return add(mul(left,rh.p[right_len]),right);}
};

