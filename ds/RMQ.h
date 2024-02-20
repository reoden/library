#include <bits/stdc++.h>
using namespace std;

template <class T> struct RMQ {
  vector<vector<T>> jmp;

  T f(T a, T b) { return min(a, b); }

  RMQ(const vector<T> &V) : jmp(1, V) {
    for (int pw = 1, k = 1; pw * 2 <= V.size(); pw *= 2, ++k) {
      jmp.emplace_back(V.size() - pw * 2 + 1);
      for (int j = 0; j < jmp[k].size(); j++) {
        jmp[k][j] = f(jmp[k - 1][j], jmp[k - 1][j + pw]);
      }
    }
  }

  T query(int a, int b) {
    assert(a < b);
    int dep = 31 - __builtin_clz(b - a);
    return f(jmp[dep][a], jmp[dep][b - (1U << dep)]);
  }
};
