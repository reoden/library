// works for at least up to (2**31 &mdash; 1)**2
long long int_sqrt(long long x) {
  long long ans = 0;
  for (long long k = 1LL << 30; k != 0; k /= 2) {
    if ((ans + k) * (ans + k) <= x) { ans += k; }
  }
  return ans;
}