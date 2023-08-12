#pragma once

#include "../misc/random.hpp"
#include <algorithm>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::min;

template <typename T = string>
struct Rolling_Hash {
    const int n;
    const ull base; // 基数
    vector<ull> hashed, pw;
 
    Rolling_Hash(const T &s, ull base) : n(s.size()), base(base) {
        hashed.assign(n + 1, 0), pw.assign(n + 1, 1);
        for (int i = 0; i < n; i++) {
            pw[i + 1] = hash_mul(pw[i], base);
            hashed[i + 1] = hash_mul(hashed[i], base) + s[i];
            if (hashed[i + 1] >= mod) hashed[i + 1] -= mod;
        }
    }
 
    // 文字列の [l,r) の部分のハッシュ値
    ull get_hash(int l, int r) const {
        ull ret = hashed[r] + mod - hash_mul(hashed[l], pw[r - l]);
        return ret - (ret >= mod ? mod : 0);
    }
 
    ull get_all_hash() const { return hashed[n]; }
 
    // s[l1:r1) と s[l2:r2) の辞書順大小比較 (-1 : <, 0 : =, 1 : >)
    int comp(int l1, int r1, int l2, int r2) {
        int l = 0, r = min(r1 - l1, r2 - l2) + 1;
        while (r - l > 1) {
            int m = (l + r) / 2;
            (get_hash(l1, l1 + m) == get_hash(l2, l2 + m) ? l : r) = m;
        }
        if (r1 == l1 + l && r2 == l2 + l) return 0;
        if (r1 == l1 + l) return -1;
        if (r2 == l2 + l) return 1;
        return get_hash(l1 + l, l1 + l + 1) < get_hash(l2 + l, l2 + l + 1) ? -1 : 1;
    }
};