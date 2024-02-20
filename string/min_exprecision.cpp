#include <string>

inline int string_min_exprecission(const std::string &s) {
  int N = s.size();
  int i = 0, j = 1, k = 0;
  while (k < N && i < N && j < N) {
    if (s[(i + k) % N] == s[(j + k) % N]) {
      k++;
    } else {
      s[(i + k) % N] > s[(j + k) % N] ? i = i + k + 1 : j = j + k + 1;
      if (i == j) { i++; }
      k = 0;
    }
  }

  return i <= j ? i : j;
}
