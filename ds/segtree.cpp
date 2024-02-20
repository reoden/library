#include <bits/stdc++.h>
using namespace std;

template <typename K> class SegmentTree {
  vector<K> nodes;
  int n;

public:
  SegmentTree(int n) : n(n), nodes(n * 2) {}

  template <typename Gen> void build(Gen gen) {
    function<void(int, int, int)> _build = [&](int L, int R, int p) {
      if (L == R) {
        nodes[p] = gen(L);
        return;
      }
      int mid = (L + R) / 2, lp = p + 1, rp = p + (mid - L + 1) * 2;
      _build(L, mid, lp), _build(mid + 1, R, rp);
      nodes[p] = nodes[lp] + nodes[rp];
    };
    _build(0, n - 1, 1);
  }

  void modify(int id, K v, bool is_add = false) {
    function<void(int, int, int)> _modify = [&](int L, int R, int p) {
      if (L == R) {
        if (is_add)
          nodes[p] += v;
        else
          nodes[p] = v;
        return;
      }
      int mid = (L + R) / 2, lp = p + 1, rp = p + (mid - L + 1) * 2;
      if (id <= mid)
        _modify(L, mid, lp);
      else
        _modify(mid + 1, R, rp);
      nodes[p] = nodes[lp] + nodes[rp];
    };
    _modify(0, n - 1, 1);
  }

  K query(int l, int r) {
    function<K(int, int, int)> _query = [&](int L, int R, int p) -> K {
      if (l <= L && R <= r) { return nodes[p]; }
      int mid = (L + R) / 2, lp = p + 1, rp = p + (mid - L + 1) * 2;
      if (mid >= l && mid < r)
        return _query(L, mid, lp) + _query(mid + 1, R, rp);
      else if (mid >= l)
        return _query(L, mid, lp);
      else
        return _query(mid + 1, R, rp);
    };
    return _query(0, n - 1, 1);
  }

  template <typename V, typename Fn, typename Fn2>
  V query(int l, int r, V init_value, Fn merge, Fn2 parse) {
    function<V(int, int, int)> _query = [&](int L, int R, int p) -> V {
      if (l <= L && R <= r) {
        V ret = parse(nodes[p]);
        return ret;
      }
      int mid = (L + R) / 2, lp = p + 1, rp = p + (mid - L + 1) * 2;
      V ret = init_value;
      if (mid >= l) ret = merge(ret, _query(L, mid, lp));
      if (mid < r) ret = merge(ret, _query(mid + 1, R, rp));
      return ret;
    };
    return _query(0, n - 1, 1);
  }
};

struct node {
  int s;
  node &operator+=(const node &rhs) {
    int a = s + rhs.s;
    s = a;
    return *this;
  }
};

node operator+(const node &lhs, const node &rhs) {
  node ret = lhs;
  ret += rhs;
  return std::move(ret);
}
