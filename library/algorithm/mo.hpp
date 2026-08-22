#pragma once
#include "../basic/base.hpp"

struct Mo {
    struct Query { int l, r, id; };
    int n; vector<Query> queries;
    Mo(int m = 0) : n(m) {}
    int add_query(int l, int r){ assert(0 <= l && l <= r && r <= n); int id = queries.size(); queries.push_back({l,r,id}); return id; }
    vector<int> order() const {
        int q = queries.size(), block = max(1, (int)(n / max(1.0, sqrt((double)max(1,q))))); vector<Query> sorted = queries;
        sort(all(sorted), [&](const Query& a, const Query& b){ int x = a.l / block, y = b.l / block; if (x != y) return x < y; return x & 1 ? a.r > b.r : a.r < b.r; });
        vector<int> res; res.reserve(q); for (auto query : sorted) res.push_back(query.id); return res;
    }
};
