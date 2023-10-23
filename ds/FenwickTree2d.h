#include "./FenwickTree.h"
#include <algorithm>
#include <vector>

struct FT2 {
  std::vector<std::vector<int>> ys;
  std::vector<FT> ft;
  FT2(int limx) : ys(limx) {}

  void fakeUpdate(int x, int y) {
    for (; x < ys.size(); x |= x + 1) {
      ys[x].push_back(y);
    }
  }

  void init() {
    for (std::vector<int> &v : ys) {
      std::sort(v.begin(), v.end());
      ft.emplace_back(v.size());
    }
  }

  int ind(int x, int y) {
    return (int)(std::lower_bound(ys[x].begin(), ys[x].end(), y) -
                 ys[x].begin());
  }

  void update(int x, int y, long long dif) {
    for (; x < ys.size(); x |= x + 1) {
      ft[x].update(ind(x, y), dif);
    }
  }

  long long query(int x, int y) {
    long long sum = 0;
    for (; x; x &= x - 1) {
      sum += ft[x - 1].query(ind(x - 1, y));
    }

    return sum;
  }
};
