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

const ll MOD = 1000000007;  // 1e9 + 7

// Digit DP.

// In each digit, x and y is in one of the three.
// - x=0, y=0
// - x=0, y=1 (In this case, most significant bit must appear in the left bits)
// - x=1, y=1

// (digit)
// (L <= x is already satisfied by the left bits)
// (y <= R is already satisfied by the left bits)
// (most significant bit already appeared)
ll dp[61][2][2][2];

int main(int argc, char** argv) {
  ll L, R;
  cin >> L >> R;

  dp[0][0][0][0] = 1; // dp[i] represents the result of top-i digits. i-0 is initialized.
  for (ll i = 0; i < 60; ++i) {
    ll lb = (L >> (59-i)) & 1;
    ll rb = (R >> (59-i)) & 1;
    rep(j, 2) rep(k, 2) rep(s, 2) { // previous state
      ll pre = dp[i][j][k][s];
      rep(x, 2) rep(y, 2) {
        if (x && !y) { continue; } // x 1, y 0

        int nj = j, nk = k, ns = s; // next state.

        // Calculate the next state.
        if (!s && x != y) { continue; }
        if (x && y) { ns = 1; } // x = 1, y = 1, bit appeared
        // j: L <= x
        if (!j && !x && lb) { continue; } // x = 0, lb = 1, invalid
        if (x && !lb) { nj = 1; } // x = 1, lb = 0, L <= x is satisfied
        // k: y <= R
        if (!k && y && !rb) { continue; } // y = 1, rb = 0, invalid
        if (!y && rb) { nk = 1; } // y = 0, rb = 1, y <= R is satisfied
        dp[i+1][nj][nk][ns] += pre;
        dp[i+1][nj][nk][ns] %= MOD;
      }
    }
  }
  ll ans = 0;
  rep(j, 2) rep(k, 2) rep(s, 2) {
    ans += dp[60][j][k][s];
    ans %= MOD;
  }
  cout << ans << endl;
}
