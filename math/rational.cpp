#include <bits/stdc++.h>
using namespace std;
// reduc : 約分するか (約分は非常に遅い)
template <typename T, bool reduc = false> struct Rational {
  T a, b;

  Rational() : a(0), b(1) {}
  Rational(const T &a) : a(a), b(1) {}
  Rational(const T &a, const T &b) : a(a), b(b) { normalize(); }
  void normalize() {
    if (b < 0) a = -a, b = -b;
    if (reduc) {
      T g = gcd(abs(a), b);
      a /= g, b /= g;
    }
  }

  Rational &operator+=(const Rational &x) {
    a = a * x.b + b * x.a;
    b *= x.b;
    normalize();
    return *this;
  }
  Rational &operator-=(const Rational &x) {
    a = a * x.b - b * x.a;
    b *= x.b;
    normalize();
    return *this;
  }
  Rational &operator*=(const Rational &x) {
    a *= x.a;
    b *= x.b;
    normalize();
    return *this;
  }

  Rational &operator/=(const Rational &x) {
    a *= x.b;
    b *= x.a;
    normalize();
    return *this;
  }

  Rational operator-() const { return Rational(-a, b); }
  Rational operator+(const Rational &x) const { return Rational(*this) += x; }
  Rational operator-(const Rational &x) const { return Rational(*this) -= x; }
  Rational operator*(const Rational &x) const { return Rational(*this) *= x; }
  Rational operator/(const Rational &x) const { return Rational(*this) /= x; }

  bool operator<(const Rational &x) const { return a * x.b < b * x.a; }
  bool operator<=(const Rational &x) const { return a * x.b <= b * x.a; }
  bool operator>(const Rational &x) const { return a * x.b > b * x.a; }
  bool operator>=(const Rational &x) const { return a * x.b > b * x.a; }
  bool operator==(const Rational &x) const { return a * x.b == b * x.a; }
  bool operator!=(const Rational &x) const { return a * x.b != b * x.a; }
  friend ostream &operator<<(ostream &os, const Rational &x) {
    return os << x.a << '/' << x.b;
  }
};
