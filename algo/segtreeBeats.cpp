#include <bits/stdc++.h>
using namespace std;

int ceil_pow2(int n) {
  int x = 0;
  while ((1U << x) < (unsigned int)(n)) x++;
  return x;
}

template <class S, S (*op)(S, S), S (*e)(), class F, S (*mapping)(F, S),
          F (*composition)(F, F), F (*id)()>
struct segtree_beats {
public:
  segtree_beats() : segtree_beats(0) {}
  explicit segtree_beats(int n) : segtree_beats(std::vector<S>(n, e())) {}
  explicit segtree_beats(const std::vector<S> &v) : _n(int(v.size())) {
    log = ceil_pow2(_n);
    size = 1 << log;
    d = std::vector<S>(2 * size, e());
    lz = std::vector<F>(size, id());
    for (int i = 0; i < _n; i++) d[size + i] = v[i];
    for (int i = size - 1; i >= 1; i--) { update(i); }
  }

  void set(int p, S x) {
    assert(0 <= p && p < _n);
    p += size;
    for (int i = log; i >= 1; i--) push(p >> i);
    d[p] = x;
    for (int i = 1; i <= log; i++) update(p >> i);
  }

  S get(int p) {
    assert(0 <= p && p < _n);
    p += size;
    for (int i = log; i >= 1; i--) push(p >> i);
    return d[p];
  }

  S prod(int l, int r) {
    assert(0 <= l && l <= r && r <= _n);
    if (l == r) return e();

    l += size;
    r += size;

    for (int i = log; i >= 1; i--) {
      if (((l >> i) << i) != l) push(l >> i);
      if (((r >> i) << i) != r) push(r >> i);
    }

    S sml = e(), smr = e();
    while (l < r) {
      if (l & 1) sml = op(sml, d[l++]);
      if (r & 1) smr = op(d[--r], smr);
      l >>= 1;
      r >>= 1;
    }

    return op(sml, smr);
  }

  S all_prod() { return d[1]; }

  void apply(int p, F f) {
    assert(0 <= p && p < _n);
    p += size;
    for (int i = log; i >= 1; i--) push(p >> i);
    d[p] = mapping(f, d[p]);
    for (int i = 1; i <= log; i++) update(p >> i);
  }
  void apply(int l, int r, F f) {
    assert(0 <= l && l <= r && r <= _n);
    if (l == r) return;

    l += size;
    r += size;

    for (int i = log; i >= 1; i--) {
      if (((l >> i) << i) != l) push(l >> i);
      if (((r >> i) << i) != r) push((r - 1) >> i);
    }

    {
      int l2 = l, r2 = r;
      while (l < r) {
        if (l & 1) all_apply(l++, f);
        if (r & 1) all_apply(--r, f);
        l >>= 1;
        r >>= 1;
      }
      l = l2;
      r = r2;
    }

    for (int i = 1; i <= log; i++) {
      if (((l >> i) << i) != l) update(l >> i);
      if (((r >> i) << i) != r) update((r - 1) >> i);
    }
  }

  template <bool (*g)(S)> int max_right(int l) {
    return max_right(l, [](S x) { return g(x); });
  }
  template <class G> int max_right(int l, G g) {
    assert(0 <= l && l <= _n);
    assert(g(e()));
    if (l == _n) return _n;
    l += size;
    for (int i = log; i >= 1; i--) push(l >> i);
    S sm = e();
    do {
      while (l % 2 == 0) l >>= 1;
      if (!g(op(sm, d[l]))) {
        while (l < size) {
          push(l);
          l = (2 * l);
          if (g(op(sm, d[l]))) {
            sm = op(sm, d[l]);
            l++;
          }
        }
        return l - size;
      }
      sm = op(sm, d[l]);
      l++;
    } while ((l & -l) != l);
    return _n;
  }

  template <bool (*g)(S)> int min_left(int r) {
    return min_left(r, [](S x) { return g(x); });
  }
  template <class G> int min_left(int r, G g) {
    assert(0 <= r && r <= _n);
    assert(g(e()));
    if (r == 0) return 0;
    r += size;
    for (int i = log; i >= 1; i--) push((r - 1) >> i);
    S sm = e();
    do {
      r--;
      while (r > 1 && (r % 2)) r >>= 1;
      if (!g(op(d[r], sm))) {
        while (r < size) {
          push(r);
          r = (2 * r + 1);
          if (g(op(d[r], sm))) {
            sm = op(d[r], sm);
            r--;
          }
        }
        return r + 1 - size;
      }
      sm = op(d[r], sm);
    } while ((r & -r) != r);
    return 0;
  }

private:
  int _n, size, log;
  std::vector<S> d;
  std::vector<F> lz;

  void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
  void all_apply(int k, F f) {
    d[k] = mapping(f, d[k]);
    if (k < size) {
      lz[k] = composition(f, lz[k]);
      if (d[k].fail) push(k), update(k);
    }
  }
  void push(int k) {
    all_apply(2 * k, lz[k]);
    all_apply(2 * k + 1, lz[k]);
    lz[k] = id();
  }
};

// ---- END : SEGMENT TREE BEATS ----
// range-update-gcd-range-max-sum
using ll = int64_t;
constexpr ll inf = 2e9;
struct S {
  int max_val;
  int lcm;
  int len;
  ll sum;
  bool fail;
};

S e() { return {0, 1, 0, 0, false}; }
S apply_reset(S original, int x) {
  return {x, x, original.len, (ll)original.len * x, false};
}
S op(S l, S r) {
  if (r.len == 0) return l;
  if (l.len == 0) return r;
  S ret = e();
  ret.max_val = max(l.max_val, r.max_val);
  ret.lcm = min(inf, (ll)l.lcm * r.lcm / __gcd(l.lcm, r.lcm));
  ret.len = l.len + r.len;
  ret.sum = l.sum + r.sum;
  return ret;
}

struct F {
  int dogcd;
  int reset;
};
F id() { return {0, 0}; }
S mapping(F f, S x) {
  if (x.fail) return x;
  assert(!((f.reset > 0) && (f.dogcd > 0)));
  if (f.reset > 0) { return apply_reset(x, f.reset); }
  if (f.dogcd > 0) {
    if ((ll)x.len * x.max_val == x.sum) {
      // always success if the values are all same
      return apply_reset(x, __gcd(f.dogcd, x.max_val));
    }
    // if there is some i (0 <= i < n) such that
    // __gcd(g, x[i]) < x[i], then g % x[i] > 0 so g % lcm(x) > 0
    // conversely if g % lcm(x) > 0 => exists i s.t. __gcd(g, x[i]) < x[i]
    // follows.
    if (x.lcm == inf || f.dogcd % x.lcm > 0) {
      x.fail = 1;
      return x;
    }
  }
  // no change
  return x;
}
F composition(F g, F f) {
  if (g.reset) { return {0, g.reset}; }
  if (f.reset) { return {0, __gcd(g.dogcd, f.reset)}; }
  return {__gcd(g.dogcd, f.dogcd), 0};
}
// usage :
/*
vector<int> a(n);
vector<S> inits(n);
for (int i=0; i<n; i++){
  cin >> a[i];
  inits[i] = apply_reset({0, 1, 1, 0}, a[i]);
}
segtree_beats<S,op,e,F,mapping,composition,id> seg(inits);
*/
