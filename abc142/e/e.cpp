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

// d[i] .. bit representation of boxes opened by a[i].
ll d[1005];

// dp[i+1][j] .. minimum const of state j by using a[0]..a[i]. j is the bit representation of state.
// dp[i+1][j | d[i]] = min(dp[i][j | d[i]], dp[i][j] + a[i])
ll dp[1005][5005]; // 2 ** 12 ~ 4e3

int main(int argc, char** argv) {
  int N, M;
  cin >> N >> M;

  vector<int> a(M);
  vector<int> b(M); // the number of boxes
  vector< vector<int> > c(M);
  rep(i, M) {
    cin >> a[i] >> b[i];
    c[i].resize(b[i]);
    rep(j, b[i]) {
      cin >> c[i][j];
      --c[i][j]; // 0-indexed
    }
  }
  // rep(i, M) {
  //   rep(j, b[i]) {
  //     cout << c[i][j] << " ";
  //   }
  //   cout << endl;
  // }

  rep(i, M) {
    rep(j, b[i]) {
      d[i] |= 1LL << (N - 1 - c[i][j]); // c[i][j] is from 0 to N - 1.
    }
  }
  // For Debug
  // cout << "d: " << endl;
  // rep(i, M) {
  //   cout << d[i] << endl;
  // }

  ll max_s = (1LL << N) - 1; // If N is 3, max_s is 111. The max value of representatable state.

  // Initialize dp.
  rep(i, M + 1) {
    rep(j, max_s + 1) {
      dp[i][j] = INF;
    }
  }
  // cout << dp[M-1][max_s] << endl;

  // Initialize dp.
  dp[0][0] = 0;
  // cout << "dp["<<0<<"]["<< d[0] <<"]: " << dp[0][d[0]] << endl;
  for (int i = 0; i < M; ++i) {
    rep(j, max_s + 1) {
      dp[i+1][j] = dp[i][j];
    }
    rep(j, max_s + 1) {
      // cout << "prev:" << endl;
      // cout << "dp["<<i<<"]["<< (j | d[i]) <<"]: " << dp[i][j | d[i]] << endl;
      // cout << "dp["<<i<<"]["<<j<<"] + a["<<i<<"]: " << dp[i][j] + a[i] << endl;
      dp[i+1][j | d[i]] = min(dp[i+1][j | d[i]], dp[i][j] + a[i]);
      // cout << "post:" << endl;
      // cout << "dp["<<i+1<<"]["<< (j | d[i]) <<"]: " << dp[i+1][j | d[i]] << endl;
    }
  }

  ll ans = dp[M][max_s];
  if (ans == INF) {
    cout << -1 << endl;
  } else {
    cout << ans << endl;
  }
}
