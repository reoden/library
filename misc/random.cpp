#include <bits/stdc++.h>
using namespace std;

struct Random_Number_Generator {
  mt19937_64 mt;

  Random_Number_Generator()
      : mt(std::chrono::steady_clock::now().time_since_epoch().count()) {}

  int64_t operator()(int64_t l, int64_t r) { // 区間 [l,r) の整数で乱数発生
    uniform_int_distribution<int64_t> dist(l, r - 1);
    return dist(mt);
  }

  int64_t operator()(int64_t r) { // 区間 [0,r) の整数で乱数発生
    return (*this)(0, r);
  }
} rng;

using ull = unsigned long long;
const ull mod = (1ULL << 61) - 1;

ull hash_mod(ull x) {
  ull ret = (x >> 61) + (x & mod);
  return ret - (ret >= mod ? mod : 0);
}

ull hash_mul(ull x, ull y) {
  x = hash_mod(x), y = hash_mod(y);
  ull x1 = x >> 31, x2 = x & ((1ULL << 31) - 1), y1 = y >> 31,
      y2 = y & ((1ULL << 31) - 1);
  ull z = x1 * y2 + x2 * y1, z1 = z >> 30, z2 = z & ((1ULL << 30) - 1);
  return hash_mod(x1 * y1 * 2 + x2 * y2 + z1 + (z2 << 31));
}

ull hash_pow(ull x, ull n) {
  ull ret = 1;
  for (; n > 0; n >>= 1, x = hash_mul(x, x)) {
    if (n & 1) ret = hash_mul(ret, x);
  }
  return ret;
}

// m 以上の base を乱択で生成する
ull generate_base(ull m = (1ULL << 50)) {
  while (true) {
    ull k = rng(mod);
    if (std::gcd(mod - 1, k) != 1) continue;
    ull base = hash_pow(3, k);
    if (base >= m) return base;
  }
  return 0;
}
