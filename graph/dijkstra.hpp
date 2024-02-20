#include <bits/stdc++.h>
using namespace std;

namespace Kude {
template <class T>
vector<long long> dijkstra(vector<vector<pair<int, T>>> &to, int s = 0) {
  struct QueElem {
    int v;
    long long c;
    bool operator<(const QueElem a) const { return c > a.c; }
    QueElem(int v, long long c) : v(v), c(c) {}
  };
  priority_queue<QueElem> q;
  vector<long long> dist(to.size(), numeric_limits<T>::max());
  dist[s] = 0;
  q.emplace(s, 0);
  while (!q.empty()) {
    QueElem qe = q.top();
    q.pop();
    int u = qe.v;
    long long c = qe.c;
    if (c > dist[u]) continue;
    for (auto vc : to[u]) {
      int v = vc.first;
      long long nc = c + vc.second;
      if (nc < dist[v]) {
        dist[v] = nc;
        q.emplace(v, nc);
      }
    }
  }
  return dist;
}
} // namespace Kude
