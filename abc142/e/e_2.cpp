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

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

ll powmod(ll x, ll n) { // like pow(x, n)
  ll r = 1;
  while (n) {
    if (n & 1) {
      r = r * x % MOD;
    }
    x = x * x % MOD;
    n >>= 1;
  }
  return r;
}

// dp[i+1][j] .. minimum const of state j by using a[0]..a[i]. j is the bit representation of state.
// dp[i+1][j | c[i]] = min(dp[i][j | c[i]], dp[i][j] + a[i])
ll dp[1005][5000]; // dp[i][j] ..

int main(int argc, char** argv) {
  int N, M;
  cin >> N >> M;

  vector<int> a(M);
  vector<int> b(M); // the number of boxes
  vector<ll> c(M);
  rep(i, M) {
    cin >> a[i] >> b[i];
    rep(j, b[i]) {
      int t;
      cin >> t;
      --t; // 0-indexed
      c[i] += 1LL << t;
    }
  }

  rep(i, M + 1) {
    rep(j, 1LL << N) {
      dp[i][j] = INF;
    }
  }

  dp[0][0] = 0;
  rep(i, M) {
    rep(j, 1LL << N) {
      dp[i+1][j] = min(dp[i+1][j], dp[i][j]);

      int nj = j | c[i];
      dp[i+1][nj] = min(dp[i+1][nj], dp[i][j] + a[i]);
    }
  }

  if (dp[M][(1LL << N) - 1] == INF) {
    cout << -1 << endl;
  } else {
    cout << dp[M][(1LL << N) - 1] << endl;
  }
}
