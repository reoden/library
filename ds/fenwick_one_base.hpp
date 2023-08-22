#pragma once

#include <vector>
// @param 1-indexed 
template <typename T>
struct Fenwick {
  const int n;
  std::vector<T> tr;
  Fenwick(int n) : n(n), tr(n + 1) {}

  void add(int x, T v) {for (int i=x;i<=n;i+=i&-i) tr[i] += v;}

  T sum(int x) {
    T ans = 0;
    for (int i = x; i; i-=i&-i) ans += tr[i];
    return ans;
  }
  
  T rangeSum(int l, int r) {return sum(r) - sum(l);}
  
  int query(T s) { // 查询1~pos的和小于等于s
    int pos = 0;
    for (int j = 18; j >= 0; j -- ) 
      if ((pos + (1ll << j) < n) && tr[pos + (1ll << j)] <= s ) 
        pos = (pos + (1 << j)), s -= tr[pos];
    return pos;
	}
};