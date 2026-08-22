#pragma once
#include "../basic/base.hpp"

inline vector<int> suffix_array(const string& s){
    int n = s.size(); vector<int> sa(n), rank(n), next_rank(n); iota(all(sa), 0); for (int i = 0; i < n; ++i) rank[i] = (unsigned char)s[i];
    for (int k = 1; k < n; k <<= 1){
        sort(all(sa), [&](int i, int j){ if (rank[i] != rank[j]) return rank[i] < rank[j]; int ri = i + k < n ? rank[i + k] : -1, rj = j + k < n ? rank[j + k] : -1; return ri < rj; });
        next_rank[sa[0]] = 0; for (int i = 1; i < n; ++i){ int a = sa[i-1], b = sa[i]; next_rank[b] = next_rank[a] + (rank[a] != rank[b] || (a+k<n?rank[a+k]:-1) != (b+k<n?rank[b+k]:-1)); } rank.swap(next_rank);
        if (rank[sa.back()] == n - 1) break;
    }
    return sa;
}
inline vector<int> lcp_array(const string& s, const vector<int>& sa){
    int n = s.size(); if (!n) return {}; vector<int> rank(n), lcp(max(0,n-1)); for (int i = 0; i < n; ++i) rank[sa[i]] = i;
    for (int i = 0, h = 0; i < n; ++i){ int r = rank[i]; if (!r) continue; int j = sa[r-1]; while (i+h<n && j+h<n && s[i+h]==s[j+h]) ++h; lcp[r-1]=h; if(h)--h; }
    return lcp;
}
inline pair<int,int> suffix_array_equal_range(const string& s, const vector<int>& sa, const string& pattern){
    auto cmp = [&](int pos, const string& p){ return s.compare(pos, p.size(), p); };
    int l = lower_bound(all(sa), pattern, [&](int pos, const string& p){ return cmp(pos,p) < 0; }) - sa.begin();
    int r = upper_bound(all(sa), pattern, [&](const string& p, int pos){ return cmp(pos,p) > 0; }) - sa.begin();
    return {l,r};
}

