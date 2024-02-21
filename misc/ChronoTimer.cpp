#include <bits/stdc++.h>
using namespace std;

struct ChronoTimer {
  std::chrono::high_resolution_clock::time_point st;

  ChronoTimer() { reset(); }

  void reset() { st = std::chrono::high_resolution_clock::now(); }

  std::chrono::milliseconds::rep elapsed() {
    auto ed = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(ed - st).count();
  }
};
