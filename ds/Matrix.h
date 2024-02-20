#include <array>
#include <cassert>
#include <vector>

template <class T, int N> struct Matrix {
  typedef Matrix M;
  std::array<std::array<T, N>, N> d{};

  M operator*(const M &m) const {
    M a;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        for (int k = 0; k < N; k++) { a.d[i][j] += d[i][k] * m.d[k][j]; }
      }
    }
  }

  std::vector<T> operator*(const std::vector<T> &vec) const {
    std::vector<T> ret(N);
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) { ret[i] += d[i][j] * vec[j]; }
    }

    return ret;
  }

  M operator^(long long p) const {
    assert(p >= 0);
    M a, b(*this);
    for (int i = 0; i < N; i++) { a.d[i][i] = 1; }

    while (p) {
      if (p & 1) a = a * b;
      b = b * b;
      p >>= 1;
    }

    return a;
  }
};
