#pragma once
#include <array>
#include <vector>

using namespace std;

// @return tree and root
template <class T, class Compare = less<T>>
pair<vector<array<int, 2>>, int> cartesian_tree(const vector<T> &a) {
  const int n = a.size();
  vector<array<int, 2>> g(n, {-1, -1});
  vector<int> st;
  constexpr Compare cmp;
  for (int i = 0; i < n; i++) {
    int last_popped = -1;
    while (!st.empty() && cmp(a[i], a[st.back()])) {
      last_popped = st.back();
      st.pop_back();
    }
    g[i][0] = last_popped;
    if (!st.empty()) g[st.back()][1] = i;
    st.emplace_back(i);
  }
  return pair(std::move(g), st.empty() ? -1 : st[0]);
}
