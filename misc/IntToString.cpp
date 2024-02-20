#include <bits/stdc++.h>
using namespace std;

template <typename T> std::string integer_to_string(T x) {
  if (x == 0) { return "0"; }
  std::string s;
  bool neg = false;
  if (x < 0) x = -x, neg = true;
  while (x > 0) {
    s += static_cast<char>(x % 10 + '0');
    x /= 10;
  }
  if (neg) s += "-";

  std::reverse(s.begin(), s.end());
  return s;
}
