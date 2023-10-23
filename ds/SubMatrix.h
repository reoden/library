#include <vector>
template <class T> struct SubMatrix {
  std::vector<std::vector<T>> p;

  SubMatrix(std::vector<std::vector<T>> &v) {
    int R = v.size(), C = v[0].size();
    p.assign(R + 1, std::vector<T>(C + 1));
    for (int r = 0; r < R; r++) {
      for (int c = 0; c < C; c++) {
        p[r + 1][c + 1] = v[r][c] + p[r][c + 1] + p[r + 1][c] - p[r][c];
      }
    }
  }

  T sum(int u, int l, int d, int r) {
    return p[d][r] - p[d][l] - p[u][r] + p[u][l];
  }
};
