#pragma once
#include "base.hpp"

template<class T> vector<T> prefix_sum(const vector<T>& a){
    vector<T> s(a.size() + 1);
    for (int i = 0; i < (int)a.size(); ++i) s[i + 1] = s[i] + a[i];
    return s;
}
template<class T> vector<T> prefix_1Dsum(const vector<T>& a){ return prefix_sum(a); }
template<class T> T range_sum(const vector<T>& s, int l, int r){ assert(0 <= l && l <= r && r < (int)s.size()); return s[r] - s[l]; }
template<class T> vector<vector<T>> prefix_sum_2d(const vector<vector<T>>& a){
    int h = a.size(), w = h ? a[0].size() : 0;
    vector s(h + 1, vector<T>(w + 1));
    for (int i = 0; i < h; ++i) for (int j = 0; j < w; ++j)
        s[i + 1][j + 1] = a[i][j] + s[i][j + 1] + s[i + 1][j] - s[i][j];
    return s;
}
template<class T> T range_sum_2d(const vector<vector<T>>& s, int x1, int y1, int x2, int y2){
    return s[x2][y2] - s[x1][y2] - s[x2][y1] + s[x1][y1];
}
template<class T> void rotate_grid(vector<vector<T>>& a, bool counterclockwise = false){
    if (a.empty() || a[0].empty()) return;
    int h = a.size(), w = a[0].size();
    vector b(w, vector<T>(h));
    for (int i = 0; i < h; ++i) for (int j = 0; j < w; ++j)
        if (counterclockwise) b[w - 1 - j][i] = a[i][j]; else b[j][h - 1 - i] = a[i][j];
    a = move(b);
}
