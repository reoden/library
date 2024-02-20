#include <bits/stdc++.h>
using namespace std;

template <typename T> struct FT {
  vector<T> s;
  FT(int n) : s(n) {}
  void update(int pos, T diff) {
    for (; pos < int(s.size()); pos |= pos + 1) s[pos] += diff;
  }
  T query(int pos) {
    T res = 0;
    for (; pos; pos &= pos - 1) res += s[pos - 1];
    return res;
  }
  int lower_bound(T sum) {
    if (sum <= 0) return -1;
    int pos = 0;
    for (int pw = 1 << 30; pw; pw >>= 1) {
      if (pos + pw <= int(s.size()) && s[pos + pw - 1] < sum)
        pos += pw, sum -= s[pos - 1];
    }
  }
};

struct FT2 {
  vector<vector<int>> ys;
  vector<FT<long long>> ft;
  FT2(int limx) : ys(limx) {}
  void fakeUpdate(int x, int y) {
    for (; x < int(ys.size()); x |= x + 1) ys[x].push_back(y);
  }
  void init() {
    for (auto &v : ys) sort(v.begin(), v.end()), ft.emplace_back(v.size());
  }
  int ind(int x, int y) {
    return (int)(lower_bound(ys[x].begin(), ys[x].end(), y) - ys[x].begin());
  }
  void update(int x, int y, long long dif) {
    for (; x < int(ys.size()); x |= x + 1) ft[x].update(ind(x, y), dif);
  }
  long long query(int x, int y) {
    long long sum = 0;
    for (; x; x &= x - 1) { sum += ft[x - 1].query(ind(x - 1, y)); }
    return sum;
  }
};
