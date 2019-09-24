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
vector< vector<int> > to; // Adjacency matrix
int id[MAXN][MAXN];
int toId(int i, int j) {
  if (i > j) { swap(i, j); }
  return id[i][j];
}

int dp[MAXV]; // Max length of path from v.
bool calculated[MAXV];
int dfs(int v) {
  if (dp[v] >= 0) {
    if (!calculated[v]) { return -1; } // If calculated[v] is false, loop exists.
    return dp[v];
  }
  dp[v] = 0;
  for (auto u : to[v]) {
    int res = dfs(u);
    if (res == -1) { return -1; } // Loop exists
    dp[v] = max(dp[v], res + 1);
  }
  calculated[v] = true;
  return dp[v];
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
  for (int i = 0; i < N-1; ++i) {
    for (int j = i + 1; j < N; ++j) {
      id[i][j] = V++;
    }
  }

  to.resize(V);
  rep(i, N) {
    for (int j = 0; j < N - 2; ++j) {
      int p = toId(i, A[i][j]);
      int n = toId(i, A[i][j+1]);
      to[p].push_back(n);
    }
  }

  int ans = 0;
  rep(i, V) {
    memset(dp, -1, sizeof(dp));
    memset(calculated, 0, sizeof(calculated));
    int res = dfs(i);
    if (res == -1) {
      cout << -1 << endl;
      return 0;
    }
    ans = max(ans, res);
  }

  cout << ans + 1 << endl;
}
