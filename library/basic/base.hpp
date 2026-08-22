#pragma once
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
template<class T> using minpq = priority_queue<T, vector<T>, greater<T>>;
template<class T> using maxpq = priority_queue<T>;

constexpr int INF = numeric_limits<int>::max() / 2;
constexpr ll LINF = numeric_limits<ll>::max() / 4;

#define rep(i,n) for (long long i = 0; i < (long long)(n); ++i)
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)

template<class T, class U> bool chmin(T& a, const U& b){ if (b < a) return a = b, true; return false; }
template<class T, class U> bool chmax(T& a, const U& b){ if (a < b) return a = b, true; return false; }

inline void Yes(){ cout << "Yes\n"; }
inline void No(){ cout << "No\n"; }
inline void YN(bool ok){ ok ? Yes() : No(); }

template<class T> T ceil_div(T a, T b){
    assert(b != 0);
    T q = a / b, r = a % b;
    return q + (r != 0 && ((r > 0) == (b > 0)));
}
inline bool is_in_grid(int i, int j, int h, int w){ return 0 <= i && i < h && 0 <= j && j < w; }
template<class T> T manhattan_distance(T x1, T y1, T x2, T y2){ return abs(x1 - x2) + abs(y1 - y2); }
template<class T> long double euclidean_distance(T x1, T y1, T x2, T y2){ return hypot((long double)(x1 - x2), (long double)(y1 - y2)); }

template<class T> vector<T> compressed_values(vector<T> xs){ sort(all(xs)); xs.erase(unique(all(xs)), xs.end()); return xs; }
template<class T> vector<int> coordinate_compress(const vector<T>& a){
    auto xs = compressed_values(a);
    vector<int> res(a.size());
    for (int i = 0; i < (int)a.size(); ++i) res[i] = lower_bound(all(xs), a[i]) - xs.begin();
    return res;
}

