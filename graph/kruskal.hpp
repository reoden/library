#pragma once

#include "../ds/dsu.hpp"
#include "./graph_template.hpp"

template <typename T> T kruskal(int N, Edges<T> &es) {
  sort(begin(es), end(es), [&](Edge<T> a, Edge<T> b) { return a.cost < b.cost; });
  dsu uf(N);
  T ret = 0;
  for (Edge<T> &e : es) {
    if (uf.same(e.from, e.to)) continue;
    ret += e.cost;
    uf.merge(e.from, e.to);
  }
  return ret;
}
