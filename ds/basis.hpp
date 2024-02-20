#pragma once

#include <array>
#include <cassert>

using std::array;

template <typename Int = int, int MAX = 30> struct Basis {
  array<Int, MAX> v;
  Basis() { fill(begin(v), end(v), Int{0}); }

  const Int operator[](int i) const { return v[i]; }

  void add(Int x) {
    int t = _msb(x);
    assert(t < MAX);
    for (int i = t; i >= 0; i--) x = min(x, x ^ v[i]);
    if (x) v[_msb(x)] = x;
  }

  void merge(const Basis &rhs) {
    for (int t = MAX - 1; t >= 0; t--) {
      if (rhs[t] == Int{0}) continue;
      Int x = rhs[t];
      for (int i = t; i >= 0; i--) x = min(x, x ^ v[i]);
      if (x) v[_msb(x)] = x;
    }
  }

  Int get_max() const {
    Int res = 0;
    for (int t = MAX - 1; t >= 0; t--) res = max(res, res ^ v[t]);
    return res;
  }

private:
  int _msb(Int x) { return x ? 63 - __builtin_clzll(x) : -1; }
};