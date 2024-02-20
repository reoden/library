#include <bits/stdc++.h>
using namespace std;

namespace Kude {
// Kude return [primes, Minimum prime factor]
pair<vector<int>, vector<int>> primes_lpf(const int n) {
  vector<int> primes;
  primes.reserve(n / 10);
  vector<int> lpf(n + 1);
  for (int i = 2; i <= n; i += 2) lpf[i] = 2;
  for (int i = 3; i <= n; i += 6) lpf[i] = 3;
  if (2 <= n) primes.push_back(2);
  if (3 <= n) primes.push_back(3);
  // 5 * x <= n, x <= floor(n / 5)
  const int n5 = n / 5;
  int x = 5;
  char add_next = 2;
  for (; x <= n5; x += add_next, add_next ^= 2 ^ 4) {
    int px = lpf[x];
    if (px == 0) {
      lpf[x] = px = x;
      primes.push_back(x);
    }
    for (int i = 2;; ++i) {
      int q = primes[i];
      int y = q * x;
      if (y > n) break;
      lpf[y] = q;
      if (q == px) break;
    }
  }
  for (; x <= n; x += add_next, add_next ^= 2 ^ 4) {
    if (lpf[x] == 0) {
      lpf[x] = x;
      primes.push_back(x);
    }
  }
  return {std::move(primes), std::move(lpf)};
}

constexpr int PSIZE = 1000000;
auto [primes, lpf] = primes_lpf(PSIZE);
} // namespace Kude
