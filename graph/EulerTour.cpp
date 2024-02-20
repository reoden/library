#include <bits/stdc++.h>
using namespace std;
// Preorder Euler Tour
// （行きがけ順，部分木の頂点クエリ等に有用）
struct PreorderEulerTour {
  int V; // # of vertices of tree
  int root;
  vector<std::vector<int>> edges;
  vector<int> subtree_begin, subtree_end;
  vector<int> vis_order;

  void _build_dfs(int now, int prv) {
    subtree_begin[now] = vis_order.size();
    vis_order.push_back(now);
    for (auto nxt : edges[now]) {
      if (nxt != prv) {
        _build_dfs(nxt, now);
        vis_order.push_back(now);
      }
    }
    subtree_end[now] = vis_order.size();
  }
  PreorderEulerTour() = default;
  PreorderEulerTour(const vector<vector<int>> &to, int root)
      : V(to.size()), root(root), edges(to) {
    assert(root >= 0 and root < V);
    subtree_begin.resize(V);
    subtree_end.resize(V);
    _build_dfs(root, -1);
  }
};
