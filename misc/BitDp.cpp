#include <bits/stdc++.h>
using namespace std;

int a[20], k;
int dp[20][100][20][20];

/*
 * @prama md:val mod k
 *        odd: num of odd num
 *        even: num of even num
 *        lead: leader zero
 * */
int dfs(int pos, int md, int odd, int even, int lead, int limit) {
  if (!pos) { return !md && odd == even; }
  if (!limit && !lead && ~dp[pos][md][odd][even]) { return dp[pos][md][odd][even]; }

  int res = 0, up = limit ? a[pos] : 9;
  for (int i = 0; i <= up; i++) {
    if (lead && !i) {
      res += dfs(pos - 1, md, odd, even, lead && !i, limit && i == up);
      continue;
    }
    res += dfs(pos - 1, (md * 10 + i) % k, odd + (i & 1), even + (~i & 1), lead && !i,
               limit && i == up);
  }

  return limit ? res : dp[pos][md][odd][even] = res;
}

int calc(int x) {
  int len = 0;
  memset(dp, -1, sizeof dp);
  while (x) a[++len] = x % 10, x /= 10;
  return dfs(len, 0, 0, 0, 1, 1);
}
