#pragma once

#include <algorithm>
#include <cassert>
#include <vector>

struct SCC {
  std::vector<std::vector<int>> G;
  std::vector<int> comp; // component id vertex v belongs to

  SCC(int n) : G(n), comp(n, -1), n(n), time(0), group_num(0), ord(n, -1), low(n) {}

  void add_edge(int u, int v) {
    assert(0 <= u && u < n);
    assert(0 <= v && v < n);
    G[u].emplace_back(v);
  }

  int add_vertex() {
    G.emplace_back();
    comp.emplace_back(-1);
    ord.emplace_back(-1);
    low.emplace_back();
    return n++;
  }

  std::vector<std::vector<int>> build() {
    for (int i = 0; i < n; i++) {
      if (ord[i] < 0) { dfs(i); }
    }
    for (int &x : comp) { x = group_num - 1 - x; }

    std::vector<std::vector<int>> groups(group_num);
    for (int i = 0; i < n; i++) { groups[comp[i]].emplace_back(i); }
    return groups;
  }

  std::vector<std::vector<int>> make_graph() {
    std::vector<std::vector<int>> dag(group_num);
    for (int v = 0; v < n; v++) {
      for (int &u : G[v]) {
        if (comp[v] != comp[u]) { dag[comp[v]].emplace_back(comp[u]); }
      }
    }
    for (auto &to : dag) {
      std::sort(to.begin(), to.end());
      to.erase(unique(to.begin(), to.end()), to.end());
    }
    return dag;
  }

  int operator[](int v) const { return comp[v]; }

private:
  int n, time, group_num;
  std::vector<int> ord, low, visited;

  void dfs(int v) {
    ord[v] = low[v] = time++;
    visited.emplace_back(v);
    for (int &u : G[v]) {
      if (ord[u] == -1) {
        dfs(u);
        low[v] = std::min(low[v], low[u]);
      } else if (comp[u] < 0) {
        low[v] = std::min(low[v], ord[u]);
      }
    }
    if (ord[v] == low[v]) {
      while (true) {
        int u = visited.back();
        visited.pop_back();
        comp[u] = group_num;
        if (u == v) break;
      }
      group_num++;
    }
  }
};
