// Ari-hon 3-4. p173

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

const int INF = 1e5;

#define MAX_N 15
int n;
int d[MAX_N][MAX_N];
int dp[1 << MAX_N][MAX_N]; // Memo

int rec(int S, int v) {
  if (dp[S][v] >= 0) {
    return dp[S][v];
  }

  if (S == (1<<n)-1 && v == 0) {
    // Returned to 0 after visited all cities.
    return dp[S][v] = 0;
  }

  int res = INF;
  rep(u, n) {
    if (!(S >> u & 1)) { // u is not visited
      res = min(res, rec(S | (1 << u), u) + d[v][u]);
    }
  }
  return dp[S][v] = res;
}

int main(int argc, char** argv) {
  // Initialization
  fill(&(d[0][0]), &(d[0][0]) + MAX_N * MAX_N, INF);
  memset(dp, -1, sizeof(dp));

  int m;
  cin >> n >> m;
  rep(i, m) {
    int a, b, w;
    cin >> a >> b >> w;
    d[a][b] = w;
  }

  int res = rec(0, 0);
  cout << res << endl;
}
