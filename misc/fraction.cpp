#include <bits/stdc++.h>
using namespace std;

struct Frac {
  Frac(long long p_ = 0, long long q_ = 1) {
    auto g = __gcd(p_, q_);
    p = p_ / g;
    q = q_ / g;
  }

  Frac add() const { return Frac(p + q, q); }
  long long p, q;
};

Frac operator/(const Frac &a, const Frac &b) { return Frac(a.p * b.q, a.q * b.p); }
bool operator<(const Frac &a, const Frac &b) {
  return a.p != b.p ? a.p < b.p : a.q < b.q;
}
