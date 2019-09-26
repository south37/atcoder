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

  dp[60][0][0][0] = 1;
  for (ll i = 59; i >= 0; --i) {
    ll lb = (L >> i) & 1;
    ll rb = (R >> i) & 1;
    rep(flagX, 2) rep(flagY, 2) rep(flagZ, 2) { // previous state
      ll pre = dp[i+1][flagX][flagY][flagZ];
      rep(x, 2) rep(y, 2) {
        if (x && !y) { continue; } // x 1, y 0

        int nx = flagX, ny = flagY, nz = flagZ; // next state.

        // Calculate the next state.
        if (!flagZ && x != y) { continue; }
        if (x && y) { nz = 1; } // x = 1, y = 1, bit appeared
        // flagX: L <= x
        if (!flagX && !x && lb) { continue; } // x = 0, lb = 1, invalid
        if (x && !lb) { nx = 1; } // x = 1, lb = 0, L <= x is satisfied
        // flagY: y <= R
        if (!flagY && y && !rb) { continue; } // y = 1, rb = 0, invalid
        if (!y && rb) { ny = 1; } // y = 0, rb = 1, y <= R is satisfied
        dp[i][nx][ny][nz] += pre;
        dp[i][nx][ny][nz] %= MOD;
      }
    }
  }
  ll ans = 0;
  rep(flagX, 2) rep(flagY, 2) rep(flagZ, 2) {
    ans += dp[0][flagX][flagY][flagZ];
    ans %= MOD;
  }
  cout << ans << endl;
}
