#include <cassert>
#include <functional>
#include <iterator>
#include <limits>
#include <set>
struct Line {
  mutable long long k, m, p;
  bool operator<(const Line &o) const { return k < o.k; }
  bool operator<(long long x) const { return p < x; }
};

struct LineContainer : std::multiset<Line, std::less<>> {
  // (for double, use inf = 1/.0, div(a, b) = a / b)
  static const long long inf = std::numeric_limits<long long>::max() / 2;
  long long div(long long a, long long b) { // floor division
    return a / b - ((a ^ b) < 0 && a % b);
  }

  bool isect(iterator x, iterator y) {
    if (y == end()) { return x->p == inf, 0; }
    if (x->k == y->k)
      x->p = x->m > y->m ? inf : -inf;
    else
      x->p = div(y->m - x->m, x->k - y->k);

    return x->p >= y->p;
  }

  void add(long long k, long long m) {
    auto z = insert({k, m, 0}), y = z++, x = y;
    while (isect(y, z)) z = erase(z);
    if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
    while ((y = x) != begin() && (--x)->p >= y->p) { isect(x, erase(y)); }
  }

  long long query(long long x) {
    assert(!empty());
    auto l = *lower_bound(x);
    return l.k * x + l.m;
  }
};
