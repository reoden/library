#include <bits/stdc++.h>
using namespace std;

template <typename T> long long inversions(vector<T> nums) {
  if (nums.empty()) return 0;
  auto merge = [](auto &&merge, vector<T> &a, int l, int r, vector<T> &tmp) -> long long {
    if (l == r) return 0;
    int mid = (l + r) / 2;
    long long ret = merge(merge, a, l, mid, tmp) + merge(merge, a, mid + 1, r, tmp);
    int i = l, j = mid + 1, k = l;
    while (i <= mid) {
      while (j <= r && a[j] < a[i]) tmp[k++] = a[j++];
      ret += j - mid - 1;
      tmp[k++] = a[i++];
    }
    while (j <= r) tmp[k++] = a[j++];
    copy(begin(tmp) + l, begin(tmp) + r + 1, begin(a) + l);
    return ret;
  };
  auto tmp = nums;
  return merge(merge, nums, 0, nums.size() - 1, tmp);
}
