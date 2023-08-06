#pragma once

#include <algorithm>
#include <iterator>
#include <limits>
#include <numeric>
#include <vector>

namespace Lazysegmenttree {
const static int N = 200010;
template <class T> constexpr T inf = std::numeric_limits<T>::max() / 2;

// @ range add get range min
struct Info {
  int64_t minv;

  Info() : minv(inf<int64_t>) {}
  Info(int64_t _minv) : minv(_minv) {}
};

Info operator+(const Info &a, const Info &b) {
  Info c;
  c.minv = std::min(a.minv, b.minv);
  return c;
}

struct Tag {
  int64_t add;

  Tag() : add(0) {}
  Tag(int _add) : add(_add) {}
};

void apply(Info &a, Tag &b, const Tag &c) {
  a.minv = a.minv + c.add;
  b.add = b.add + c.add;
}

Info info[N << 2];
Tag tag[N << 2];

void pull(int p) { info[p] = info[p * 2] + info[p * 2 + 1]; }

void build(int p, int l, int r) {
  if (l == r) {
    info[p].minv = inf<int64_t>;
    return;
  }

  int mid = (l + r) >> 1;
  build(p * 2, l, mid), build(p * 2 + 1, mid + 1, r);
  pull(p);
}

void apply(int p, const Tag &v) { apply(info[p], tag[p], v); }

void push(int p) {
  apply(p * 2, tag[p]);
  apply(p * 2 + 1, tag[p]);
  tag[p] = Tag();
}

void change(int p, int l, int r, int x, const Info &v) {
  if (l == r) {
    info[p] = v;
    return;
  }
  int mid = (l + r) >> 1;
  push(p);
  if (mid >= x) change(p * 2, l, mid, x, v);
  else change(p * 2 + 1, mid + 1, r, x, v);
  pull(p);
}

void modify(int p, int l, int r, int ln, int rn, const Tag &v) {
  if (l > rn || r < ln)
    return;
  if (l >= ln && r <= rn) {
    apply(p, v);
    return;
  }

  push(p);
  int mid = (l + r) >> 1;
  modify(p * 2, l, mid, ln, rn, v);
  modify(p * 2 + 1, mid + 1, r, ln, rn, v);
  pull(p);
}

Info query(int p, int l, int r, int ln, int rn) {
  if (l > rn || r < ln)
    return Info();
  if (l >= ln && r <= rn) {
    return info[p];
  }

  push(p);
  int mid = (l + r) >> 1;
  return query(p * 2, l, mid, ln, rn) + query(p * 2 + 1, mid + 1, r, ln, rn);
}

// @ return first index >= v
int lower(int p, int l, int r, int ln, int rn, const Info &v) {
  push(p);
  if (l >= ln && r <= rn) {
    if (info[p].minv < v.minv)
      return -1;
    if (l == r)
      return l;
    int mid = (l + r) / 2;
    if (info[p * 2].minv >= v.minv)
      return lower(p * 2, l, mid, ln, rn, v);
    return lower(p * 2 + 1, mid + 1, r, ln, rn, v);
  }
  int mid = (l + r) / 2;

  if (rn <= mid)
    return lower(p * 2, l, mid, ln, rn, v);
  else if (mid < l)
    return lower(p * 2 + 1, mid + 1, r, ln, rn, v);
  else {
    int pos = lower(p * 2, l, mid, ln, mid, v);
    if (!~pos)
      return lower(p * 2 + 1, mid + 1, r, mid + 1, rn, v);
    return pos;
  }
}
} // namespace Lazysegmenttree
using namespace Lazysegmenttree;