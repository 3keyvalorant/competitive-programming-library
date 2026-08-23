#pragma once
#include "../basic/base.hpp"

inline vector<int> suffix_array(const string& s){
    int n = s.size(); if (!n) return {}; vector<int> sa(n), rank(n), next_rank(n), count(max(n,256));
    for (unsigned char c : s) ++count[c];
    for (int i = 1; i < 256; ++i) count[i] += count[i-1];
    for (int i = n-1; i >= 0; --i) sa[--count[(unsigned char)s[i]]] = i;
    int classes = 1; rank[sa[0]] = 0; for (int i = 1; i < n; ++i){ if (s[sa[i-1]] != s[sa[i]]) ++classes; rank[sa[i]] = classes - 1; }
    for (int k = 1; k < n; k <<= 1){
        vector<int> second; second.reserve(n); for (int i = n-k; i < n; ++i) second.push_back(i); for (int v : sa) if (v >= k) second.push_back(v-k);
        fill(count.begin(), count.begin()+classes, 0); for (int v : second) ++count[rank[v]]; for (int i = 1; i < classes; ++i) count[i] += count[i-1]; for (int i = n-1; i >= 0; --i) sa[--count[rank[second[i]]]] = second[i];
        next_rank[sa[0]] = 0; int next_classes = 1; for (int i = 1; i < n; ++i){ int a=sa[i-1],b=sa[i]; if (rank[a] != rank[b] || (a+k<n?rank[a+k]:-1) != (b+k<n?rank[b+k]:-1)) ++next_classes; next_rank[b] = next_classes - 1; } rank.swap(next_rank); classes = next_classes; if (classes == n) break;
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
