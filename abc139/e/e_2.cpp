#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string.h>
#include <set>

using namespace std;

#define COUT(x) cout << #x << " = " << (x) << " (L" << __LINE__ << ")" << endl

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

int dx[] = { 1, -1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

const int MAXN = 1005;
const int MAXV = MAXN * MAXN; // The number of vectices is N*(N-1)/2
vector< vector<int> > to; // edges

int id[MAXN][MAXN];
int getId(int i, int j) {
  if (i > j) { swap(i, j); }
  return id[i][j];
}

int dp[MAXV]; // Represents the distance from leaf or state (initizlied by -1, intermediate is -2).
int dfs(int v) {
  if (dp[v] >= 0) { return dp[v]; }
  if (dp[v] == -2) { return -1; } // v is in intermediate state. Loop exists.

  dp[v] = -2;
  int d = 0;
  for (auto e : to[v]) {
    int res = dfs(e);
    if (res == -1) { return -1; }
    d = max(d, res);
  }

  return dp[v] = d + 1;
}

int main(int argc, char** argv) {
  int N;
  cin >> N;

  vector< vector<int> > A(N, vector<int>(N-1));
  rep(i, N) {
    rep(j, N-1) {
      cin >> A[i][j];
      --A[i][j];
    }
  }

  int V = 0;
  rep(i, N) {
    rep(j, N) {
      if (i < j) {
        id[i][j] = V++;
      }
    }
  }

  to.resize(V);

  rep(i, N) {
    for (int j = 0; j <= N - 3; ++j) { // j is from 0 to N-3 (N-2)
      int v = getId(i, A[i][j]);
      int n = getId(i, A[i][j+1]);
      to[v].push_back(n);
    }
  }

  int ans = 0;
  memset(dp, -1, sizeof(dp));
  rep(i, V) {
    int res = dfs(i); // dfs calculate the maximum distance from i.
    if (res == -1) {
      cout << -1 << endl;
      return 0;
    }
    ans = max(ans, res);
  }
  cout << ans << endl;
}
