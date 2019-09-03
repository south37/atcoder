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

int dx[] = { 1, -1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };

typedef pair<int, int> P;
typedef tuple<int, int, int> triple;

int gcd(int a, int b) {
  if (a < b) { swap(a, b); }
  if (b == 0) { return a; }
  return gcd(b, a % b);
}

bool prime(int n) {
  for (int i = 2; i <= sqrt(n); i++) {
    if (n % i == 0) { return false; }
  }
  return n != 1;
}

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }

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

  cout << sum(5) << endl;;
  cout << sum(10) << endl;;
}
