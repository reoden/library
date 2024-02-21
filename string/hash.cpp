#include "../misc/random.cpp"
#include <bits/stdc++.h>
using namespace std;

template <typename T = string> struct Rolling_Hash {
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

  // s[l1:r1] と s[l2:r2] の最長共通接頭辞
  int lcp(int l1, int r1, int l2, int r2) {
    int ok = 0, ng = min(r1 - l1, r2 - l2) + 1;
    while (ng - ok > 1) {
      int mid = (ok + ng) / 2;
      (get_hash(l1, l1 + mid) == get_hash(l2, l2 + mid) ? ok : ng) = mid;
    }
    return ok;
  }

  // s[l1:r1) と s[l2:r2) の辞書順大小比較 (-1 : <, 0 : =, 1 : >)
  int comp(int l1, int r1, int l2, int r2) {
    int d = lcp(l1, r1, l2, r2);
    if (r1 == l1 + d && r2 == l2 + d) return 0;
    if (r1 == l1 + d) return -1;
    if (r2 == l2 + d) return 1;
    return get_hash(l1 + d, l1 + d + 1) < get_hash(l2 + d, l2 + d + 1) ? -1 : 1;
  }
};

template <typename T> struct Fixed_Size_Hash {
  const int n;
  const ull base;
  vector<T> v;
  ull hashed;
  vector<ull> pw;

  Fixed_Size_Hash(const vector<T> &v, ull base) : n(v.size()), base(base), v(v) {
    hashed = 0;
    pw.assign(n + 1, 1);
    for (int i = 0; i < n; i++) {
      pw[i + 1] = hash_mul(pw[i], base);
      hashed = hash_mul(hashed, base) + v[i];
      if (hashed >= mod) hashed -= mod;
    }
  }
  Fixed_Size_Hash(int m, const T &x, ull base) : Fixed_Size_Hash(vector<T>(m, x), base) {}
  ull add(int i, const T &x) {
    hashed += hash_mul(pw[n - 1 - i], mod + x);
    if (hashed >= mod) hashed -= mod;
    v[i] += x;
    return hashed;
  }
  ull change(int i, const T &x) { return add(i, x - v[i]); }
  ull get_hash() const { return hashed; }
};
