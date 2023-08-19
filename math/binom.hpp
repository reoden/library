#pragma once

#include <vector>

template <class T> struct Combina {
  int n;
  std::vector<T> fact, invfact;
 
  Combina() {}
  Combina(int _n) : n(_n), fact(_n + 1), invfact(_n + 1) {
    fact[0] = 1;
    for (int i = 1; i <= n; i++)
      fact[i] = fact[i - 1] * i;
    invfact[n] = 1 / fact[n];
    for (int i = n; i >= 1; i--)
      invfact[i - 1] = invfact[i] * i;
  }
 
  T binom(int a, int b) {
    if (a < b || b < 0)
      return 0;
    return fact[a] * invfact[b] * invfact[a - b];
  }
 
  long long lucas(long long n, long long m, long long p) {
    if (n > 0 || m > 0)
      return lucas(n / p, m / p, p) * lucas(n % p, m % p, p) % p;
    else
      return 1ll;
  }
};