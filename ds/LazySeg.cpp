#include <bits/stdc++.h>
using namespace std;

struct node {
  long long v = 0;
  long long sz = 1;
};
struct Tag {
  long long v = 0;
};

/*range add ask maxminum*/
// node pull(const node &a, const node &b) { return {max(a.v, b.v)}; }
// Tag pull(const Tag &a, const Tag &b) { return {a.v + b.v}; }
// node apply_tag(const node &a, const Tag &b) { return {a.v + b.v}; }

/*range/ask add*/
node pull(const node &a, const node &b) { return {a.v + b.v, a.sz + b.sz}; }
Tag pull(const Tag &a, const Tag &b) { return {a.v + b.v}; }
node apply_tag(const node &a, const Tag &b) { return {a.v + b.v * a.sz, a.sz}; }

struct SegTree {
  long long n, h;
  vector<node> t;
  vector<Tag> lazy;

  SegTree(long long _n) : n(_n), h((long long)log2(n)), t(2 * _n), lazy(2 * _n) {}
  void apply(long long x, const Tag &tag) {
    t[x] = apply_tag(t[x], tag);
    lazy[x] = pull(lazy[x], tag);
  }
  void build(long long l) {
    for (l = (l + n) / 2; l > 0; l /= 2) {
      if (!lazy[l].v) t[l] = pull(t[l * 2], t[2 * l + 1]);
    }
  }
  void push(long long l) {
    for (long long s = h; s > 0; s--) {
      long long i = (l + n) >> s;
      if (lazy[i].v) apply(2 * i, lazy[i]), apply(2 * i + 1, lazy[i]);
      lazy[i] = Tag();
    }
  }
  // WARNING: i : [l, r)
  void modify(long long l, long long r, const Tag &v) {
    push(l), push(r - 1);
    long long l0 = l, r0 = r;
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
      if (l & 1) apply(l++, v);
      if (r & 1) apply(--r, v);
    }
    build(l0), build(r0 - 1);
  }
  // WARNING: t[l] + ... + t[r - 1]
  node query(long long l, long long r) {
    push(l), push(r - 1);
    node left, right;
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
      if (l & 1) left = pull(left, t[l++]);
      if (r & 1) right = pull(t[--r], right);
    }
    return pull(left, right);
  }
};
/*
for (auto i : std::views::iota(0, N)) {
  seg.t[i + N] = node{A[i]};
}
for (auto i : std::views::iota(0, N) | std::views::reverse) {
  seg.t[i] = pull(seg.t[i * 2], seg.t[i * 2 + 1]);
}
*/
