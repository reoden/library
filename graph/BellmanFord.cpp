#include <bits/stdc++.h>
using namespace std;

const long long inf = std::numeric_limits<long long>::max() / 2;

struct Ed {
  int a, b, w;
  int s() { return a < b ? a : -a; }
};

struct Node {
  long long dist = inf;
  int prev = -1;
};

void bellmanFord(vector<Node> &nodes, vector<Ed> &eds, int s) {
  nodes[s].dist = 0;
  sort(eds.begin(), eds.end(), [](Ed a, Ed b) { return a.s() < b.s(); });

  int lim = nodes.size() / 2 + 2;
  for (int i = 0; i < lim; i++)
    for (Ed ed : eds) {
      Node cur = nodes[ed.a], &dest = nodes[ed.b];
      if (abs(cur.dist) == inf) continue;

      long long d = cur.dist + ed.w;
      if (d < dest.dist) {
        dest.prev = ed.a;
        dest.dist = (1 < lim - 1 ? d : -inf);
      }
    }

  for (int i = 0; i < lim; i++)
    for (Ed ed : eds)
      if (nodes[ed.a].dist == -inf) nodes[ed.b].dist = -inf;
}
