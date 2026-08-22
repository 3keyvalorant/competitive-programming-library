#pragma once
#include "../basic/base.hpp"

template<class UInt = unsigned long long, int B = numeric_limits<UInt>::digits> struct BinaryTrie {
    static_assert(is_unsigned<UInt>::value, "BinaryTrie requires an unsigned integer type");
    struct Node { int next[2] = {-1,-1}; int count = 0; };
    vector<Node> nodes{Node{}};
    int size() const { return nodes[0].count; }
    int count(UInt x) const { int v = 0; for (int b = B - 1; b >= 0; --b){ v = nodes[v].next[x >> b & 1]; if (v < 0) return 0; } return nodes[v].count; }
    void insert(UInt x, int delta = 1){
        assert(delta > 0); int v = 0; nodes[v].count += delta;
        for (int b = B - 1; b >= 0; --b){ int c = x >> b & 1; if (nodes[v].next[c] < 0) nodes[v].next[c] = nodes.size(), nodes.push_back(Node{}); v = nodes[v].next[c]; nodes[v].count += delta; }
    }
    void erase(UInt x, int delta = 1){ assert(count(x) >= delta); int v = 0; nodes[v].count -= delta; for (int b = B - 1; b >= 0; --b){ v = nodes[v].next[x >> b & 1]; nodes[v].count -= delta; } }
    UInt kth_element(int k, UInt xor_mask = 0) const {
        assert(0 <= k && k < size()); int v = 0; UInt value = 0;
        for (int b = B - 1; b >= 0; --b){ int preferred = xor_mask >> b & 1, left = nodes[v].next[preferred], cnt = left < 0 ? 0 : nodes[left].count; int c = preferred; if (k >= cnt) k -= cnt, c ^= 1; v = nodes[v].next[c]; value |= UInt(c) << b; }
        return value;
    }
    UInt min_xor(UInt x) const { assert(size()); return kth_element(0, x) ^ x; }
    UInt max_xor(UInt x) const { assert(size()); return kth_element(size() - 1, x) ^ x; }
    int count_less(UInt x, UInt xor_mask = 0) const {
        int v = 0, res = 0;
        for (int b = B - 1; b >= 0 && v >= 0; --b){ int mb = xor_mask >> b & 1, xb = x >> b & 1; if (xb){ int z = nodes[v].next[mb]; if (z >= 0) res += nodes[z].count; } v = nodes[v].next[mb ^ xb]; }
        return res;
    }
};

