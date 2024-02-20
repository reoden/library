#include <bits/stdc++.h>
using namespace std;

struct BinaryTrie {
  struct BTNode {
    int size;
    int next[2];
    BTNode() {
      size = 0;
      next[0] = next[1] = -1;
    }
  };

  int B;
  vector<BTNode> trie;
  BinaryTrie() {}
  BinaryTrie(int l) {
    B = l;
    trie.push_back(BTNode());
  }
  void clear() {
    trie.clear();
    trie.push_back(BTNode());
  }
  int size() { return trie[0].size; }

  void insert(int x, int num = 1) {
    int p = 0;
    for (int i = B - 1; i >= 0; i--) {
      trie[p].size += num;
      int e = (x >> i) & 1;
      if (trie[p].next[e] == -1) {
        trie.push_back(BTNode());
        trie[p].next[e] = trie.size() - 1;
      }
      p = trie[p].next[e];
    }
    trie[p].size += num;
  }

  int count(int x) {
    int p = 0;
    for (int i = B - 1; i >= 0; i--) {
      int e = (x >> i) & 1;
      if (trie[p].next[e] == -1) return 0;
      p = trie[p].next[e];
    }
    return trie[p].size;
  }

  void erase(int x, int num = 1) {
    num = min(num, count(x));
    int p = 0;
    for (int i = B - 1; i >= 0; i--) {
      trie[p].size -= num;
      int e = (x >> i) & 1;
      if (trie[p].next[e] == -1) {
        trie.push_back(BTNode());
        trie[p].next[e] = trie.size() - 1;
      }
      p = trie[p].next[e];
    }
    trie[p].size -= num;
  }

  int lower_bound(int x) {
    int p = 0, ret = 0;
    for (int i = B - 1; i >= 0; i--) {
      int e = (x >> i) & 1;
      if (e == 1 && trie[p].next[0] != -1) ret += trie[trie[p].next[0]].size;
      if (trie[p].next[e] == -1 || trie[trie[p].next[e]].size == 0) break;
      p = trie[p].next[e];
    }
    return ret;
  }

  int getMin(int k = 0, int x = 0) {
    if (trie[0].size <= k) return -1;
    int p = 0, ret = 0, sum = 0;
    for (int i = B - 1; i >= 0; i--) {
      int e = (x >> i) & 1;
      if (trie[p].next[e] == -1 || sum + trie[trie[p].next[e]].size <= k) {
        if (trie[p].next[e] != -1) sum += trie[trie[p].next[e]].size;
        e = 1 - e;
      }
      p = trie[p].next[e];
      ret |= ((int)e) << i;
    }
    return ret;
  }
};
