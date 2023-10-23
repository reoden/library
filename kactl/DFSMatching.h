#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
typedef vector<int> vi;
#define sz(a) (int)(a.size())
#define all(a) a.begin(), a.end()

bool find(int j, vector<vi> &g, vi &btoa, vi &vis) {
  if (btoa[j] == -1)
    return 1;
  vis[j] = 1;
  int di = btoa[j];
  for (int e : g[di]) {
    if (!vis[e] && find(e, g, btoa, vis)) {
      btoa[e] = di;
      return 1;
    }
  }
  return 0;
}

int dfsMatching(vector<vi> &g, vi &btoa) {
  vi vis;
  rep(i, 0, sz(g)) {
    vis.assign(sz(btoa), 0);
    for (int j : g[i]) {
      if (find(j, g, btoa, vis)) {
        btoa[j] = i;
        break;
      }
    }
  }

  return sz(btoa) - (int)count(all(btoa), -1);
}
