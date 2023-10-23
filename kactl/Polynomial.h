#pragma once
#include <vector>
struct Poly {
  std::vector<double> a;

  double operator()(double x) const {
    double val = 0;
    for (int i = a.size(); i--;)
      (val *= x) += a[i];
    return val;
  }

  void diff() {
    for (int i = 1; i < a.size(); i++) {
      a[i - 1] = i * a[i];
    }
    a.pop_back();
  }

  void divroot(double x0) {
    double b = a.back(), c;
    a.back() = 0;
    for (int i = a.size() - 1; i--;) {
      c = a[i], a[i] = a[i + 1] * x0 + b;
      b = c;
    }
    a.pop_back();
  }
};
