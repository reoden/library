#pragma once

#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using std::cin;
using std::queue;
using std::vector;

template <typename T> struct edge {
  int src, to;
  T cost;

  edge(int _to, T _cost) : src(-1), to(_to), cost(_cost) {}
  edge(int _src, int _to, T _cost) : src(_src), to(_to), cost(_cost) {}

  edge &operator=(const int &x) {
    to = x;
    return *this;
  }

  operator int() const { return to; }
};
template <typename T> using Edges = vector<edge<T>>;
template <typename T> using WeightedGraph = vector<Edges<T>>;
using UnweightedGraph = vector<vector<int>>;

// Input of (Unweighted) Graph
UnweightedGraph graph(int N, int M = -1, bool is_directed = false,
                      bool is_1origin = true) {
  UnweightedGraph g(N);
  if (M == -1) M = N - 1;
  for (int _ = 0; _ < M; _++) {
    int x, y;
    cin >> x >> y;
    if (is_1origin) x--, y--;
    g[x].push_back(y);
    if (!is_directed) g[y].push_back(x);
  }
  return g;
}

// Input of Weighted Graph
template <typename T>
WeightedGraph<T> wgraph(int N, int M = -1, bool is_directed = false,
                        bool is_1origin = true) {
  WeightedGraph<T> g(N);
  if (M == -1) M = N - 1;
  for (int _ = 0; _ < M; _++) {
    int x, y;
    cin >> x >> y;
    T c;
    cin >> c;
    if (is_1origin) x--, y--;
    g[x].emplace_back(x, y, c);
    if (!is_directed) g[y].emplace_back(y, x, c);
  }
  return g;
}

// Input of Edges
template <typename T>
Edges<T> esgraph(int N, int M, int is_weighted = true, bool is_1origin = true) {
  Edges<T> es;
  for (int _ = 0; _ < M; _++) {
    int x, y;
    cin >> x >> y;
    T c;
    if (is_weighted)
      cin >> c;
    else
      c = 1;
    if (is_1origin) x--, y--;
    es.emplace_back(x, y, c);
  }
  return es;
}

// Input of Adjacency Matrix
template <typename T>
vector<vector<T>> adjgraph(int N, int M, T INF, int is_weighted = true,
                           bool is_directed = false, bool is_1origin = true) {
  vector<vector<T>> d(N, vector<T>(N, INF));
  for (int _ = 0; _ < M; _++) {
    int x, y;
    cin >> x >> y;
    T c;
    if (is_weighted)
      cin >> c;
    else
      c = 1;
    if (is_1origin) x--, y--;
    d[x][y] = c;
    if (!is_directed) d[y][x] = c;
  }
  return d;
}

/**
 * @brief グラフテンプレート
 * @docs docs/graph/graph-template.md
 */
// 一般のグラフのstからの距離！！！！
// unvisited nodes : d = -1
vector<int> Depth(const UnweightedGraph &g, int start = 0) {
  int n = g.size();
  vector<int> ds(n, -1);
  ds[start] = 0;
  queue<int> q;
  q.push(start);
  while (!q.empty()) {
    int c = q.front();
    q.pop();
    int dc = ds[c];
    for (auto &d : g[c]) {
      if (ds[d] == -1) {
        ds[d] = dc + 1;
        q.push(d);
      }
    }
  }
  return ds;
}

// Depth of Rooted Weighted Tree
// unvisited nodes : d = -1
template <typename T> vector<T> Depth(const WeightedGraph<T> &g, int start = 0) {
  vector<T> d(g.size(), -1);
  auto dfs = [&](auto rec, int cur, T val, int par = -1) -> void {
    d[cur] = val;
    for (auto &dst : g[cur]) {
      if (dst == par) continue;
      rec(rec, dst, val + dst.cost, cur);
    }
  };
  dfs(dfs, start, 0);
  return d;
}

using std::make_pair;
using std::max_element;
using std::pair;

// Diameter of Tree
// return value : { {u, v}, length }
pair<pair<int, int>, int> Diameter(const UnweightedGraph &g) {
  auto d = Depth(g, 0);
  int u = max_element(begin(d), end(d)) - begin(d);
  d = Depth(g, u);
  int v = max_element(begin(d), end(d)) - begin(d);
  return make_pair(make_pair(u, v), d[v]);
}

// Diameter of Weighted Tree
// return value : { {u, v}, length }
template <typename T> pair<pair<int, int>, T> Diameter(const WeightedGraph<T> &g) {
  auto d = Depth(g, 0);
  int u = max_element(begin(d), end(d)) - begin(d);
  d = Depth(g, u);
  int v = max_element(begin(d), end(d)) - begin(d);
  return make_pair(make_pair(u, v), d[v]);
}

// nodes on the path u-v ( O(N) )
template <typename G> vector<int> Path(G &g, int u, int v) {
  vector<int> ret;
  int end = 0;
  auto dfs = [&](auto rec, int cur, int par = -1) -> void {
    ret.push_back(cur);
    if (cur == v) {
      end = 1;
      return;
    }
    for (int dst : g[cur]) {
      if (dst == par) continue;
      rec(rec, dst, cur);
      if (end) return;
    }
    if (end) return;
    ret.pop_back();
  };
  dfs(dfs, u);
  return ret;
}

/**
 * @brief グラフユーティリティ
 * @docs docs/graph/graph-utility.md
 */