/**
 * Author: Ludo Pulles, chilli, Simon Lindholm
 * Date: 2019-01-09
 * License: CC0
 * Source: http://neerc.ifmo.ru/trains/toulouse/2017/fft2.pdf (do read, it's
 excellent) Accuracy bound from http://www.daemonology.net/papers/fft.pdf
 * Description: fft(a) computes $\hat f(k) = \sum_x a[x] \exp(2\pi i \cdot k x /
 N)$ for all $k$. N must be a power of 2. Useful for convolution:
   \texttt{conv(a, b) = c}, where $c[x] = \sum a[i]b[x-i]$.
   For convolution of complex numbers or more than two vectors: FFT, multiply
   pointwise, divide by n, reverse(start+1, end), FFT back.
   Rounding is safe if $(\sum a_i^2 + \sum b_i^2)\log_2{N} < 9\cdot10^{14}$
   (in practice $10^{16}$; higher for random inputs).
   Otherwise, use NTT/FFTMod.
 * Time: O(N \log N) with $N = |A|+|B|$ ($\tilde 1s$ for $N=2^{22}$)
 * Status: somewhat tested
 * Details: An in-depth examination of precision for both FFT and FFTMod can be
 found
 * here
 (https://github.com/simonlindholm/fft-precision/blob/master/fft-precision.md)
 */
#include <algorithm>
#include <cmath>
#include <complex>
#include <vector>

typedef double db;
typedef std::complex<db> C;
typedef std::vector<db> vd;

void fft(std::vector<C> &a) {
  int n = a.size(), L = 31 - __builtin_clz(n);
  static std::vector<std::complex<long double>> R(2, 1);
  static std::vector<C> rt(2, 1);
  for (static int k = 2; k < n; k *= 2) {
    R.resize(n);
    rt.resize(n);
    auto x = std::polar(1.0L, std::acos(-1.0L) / k);
    for (int i = k; i < 2 * k; i++) {
      rt[i] = R[i] = i & 1 ? R[i / 2] * x : R[i / 2];
    }
  }

  std::vector<int> rev(n);
  for (int i = 0; i < n; i++) {
    rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
  }

  for (int i = 0; i < n; i++) {
    if (i < rev[i]) {
      std::swap(a[i], a[rev[i]]);
    }
  }

  for (int k = 1; k < n; k *= 2) {
    for (int i = 0; i < n; i += 2 * k) {
      for (int j = 0; j < k; j++) {
        C z = rt[j + k] * a[i + j + k];
        a[i + j + k] = a[i + j] - z;
        a[i + j] += z;
      }
    }
  }
}

vd conv(const vd &a, const vd &b) {
  if (a.empty() || b.empty())
    return {};

  vd res(a.size() + b.size() - 1);
  int L = 32 - __builtin_clz(res.size());
  int n = 1U << L;
  std::vector<C> in(n), out(n);
  std::copy(a.begin(), a.end(), begin(in));

  for (int i = 0; i < b.size(); i++) {
    in[i].imag(b[i]);
  }

  fft(in);
  for (C &x : in)
    x *= x;
  for (int i = 0; i < n; i++) {
    out[i] = in[-i & (n - 1)] - conj(in[i]);
  }

  fft(out);
  for (int i = 0; i < res.size(); i++) {
    res[i] = imag(out[i]) / (4 * n);
  }

  return res;
}
