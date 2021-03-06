#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

const int INF = 1e9;

// BIT (Fenwick Tree) with 0-indexed query
// https://youtu.be/lyHk98daDJo?t=7960
template<typename T>
struct BIT {
  int n;
  vector<T> d;
  BIT(int n=0) : n(n), d(n+1) {}
  void add(int i, T x=1) {
    i++; // 0-indexed to 1-indexed
    for (; i <= n; i += i&-i) {
      d[i] += x;
    }
  }
  // The sum of [0, i]
  T sum(int i) {
    i++; // 0-indexed to 1-indexed
    T x = 0;
    for (; i; i -= i&-i) {
      x += d[i];
    }
    return x;
  }
  // The sum of [l, r)
  T sum(int l, int r) {
    assert(l <= r);
    if (r == 0) { return 0; } // Here, l == 0 && r == 0
    if (l == 0) { return sum(r-1); }
    return sum(r-1) - sum(l-1);
  }
};

int main(int argc, char** argv) {
  int N;
  cin >> N;
  vector<int> v(N);
  rep(i, N) {
    cin >> v[i];
  }

  BIT<int> bit(N);
  rep(i, N) {
    bit.add(i, v[i]);
  }

  cout << bit.sum(4) << endl; // sum of [0,4]. 24
  cout << bit.sum(9) << endl; // sum of [0,9]. 55
}
