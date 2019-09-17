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

int N;
int bit[1234567]; // bit[0] is dummy.
void insert(int a, int w) {
  for (int x = a; x <= N; x += x & -x) {
    bit[x] = max(bit[x], w);
  }
}
int query(int a) {
  int ret = 0;
  for (int x = a; x > 0; x -= x & -x) {
    ret = max(ret, bit[x]);
  }
  return ret;
}

int main(int argc, char** argv) {
  cin >> N;
  vector<int> v(N);
  rep(i, N) {
    cin >> v[i];
  }

  rep(i, N) {
    insert(i + 1, v[i]);
  }

  cout << query(5) << endl;  // 7
  cout << query(10) << endl; // 10
}
