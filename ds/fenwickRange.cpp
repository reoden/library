#include <bits/stdc++.h>
using namespace std;

// [l...r]
template <typename T> class fenwick {
private:
  vector<T> f1, f2;
  int n;

  void modify(int x, T v) {
    for (int i = x; i < n; i |= i + 1) f1[i] += v, f2[i] += v * x;
  }

public:
  explicit fenwick(int _n) : n(_n), f1(_n), f2(_n) {}

  void modify(int l, int r, T v) { modify(l, v), modify(r + 1, -v); }

  T get(int x) {
    T v{};
    for (int i = x; i >= 0; i = (i & (i + 1)) - 1) v += f1[i] * (x + 1) - f2[i];
    return v;
  }

  T get(int l, int r) { return get(r) - get(l - 1); }
};
