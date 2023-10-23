#pragma once
#include "./Polynomial.h"
#include <algorithm>
#include <vector>

std::vector<double> polyRoots(Poly p, double xmin, double xmax) {
  if (p.a.size() == 2) {
    return {-p.a[0] / p.a[1]};
  }
  std::vector<double> ret;
  Poly der = p;
  der.diff();

  auto dr = polyRoots(der, xmin, xmax);
  dr.push_back(xmin - 1);
  dr.push_back(xmax + 1);
  std::sort(dr.begin(), dr.end());

  for (int i = 0; i < dr.size() - 1; i++) {
    double l = dr[i];
    double h = dr[i + 1];
    bool sign = p(l) > 0;
    if (sign ^ (p(h) > 0)) {
      for (int it = 0; it < 60; it++) {
        double m = (l + h) / 2;
        double f = p(m);
        if ((f <= 0) ^ sign)
          l = m;
        else
          h = m;
      }
      ret.push_back((l + h) / 2);
    }
  }

  return ret;
}
