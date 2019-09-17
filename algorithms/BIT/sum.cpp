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
void add(int a, int w) {
  for (int x = a; x <= N; x += x & -x) {
    bit[x] += w;
  }
}
int sum(int a) {
  int ret = 0;
  for (int x = a; x > 0; x -= x & -x) {
    ret += bit[x];
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
    add(i + 1, v[i]);
  }
  // We can also use this for initialization. O(N).
  // for (int x = 1; x < N+1; ++x) { bit[x] = v[x-1]; }
  // for (int x = 1; x < N; ++x) { bit[x + (x & -x)] += bit[x]; }

  cout << sum(5) << endl;  // 24
  cout << sum(10) << endl; // 55
}
