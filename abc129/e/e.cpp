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

ll dp[1000100][2];  // dp[i][s] .. i: position, s: equal or lower

int main(int argc, char** argv) {
  string L;
  cin >> L;
  int N = L.size();
  dp[0][0] = 1;
  rep(i, N) {
    rep(s, 2) { // s = 0: equal, s = 1: lower
      rep(l, 2) rep(r, 2) {
        if (l == 1 && r == 1) { continue; }

        int ns = s || (L[i] == '1' && l == 0 && r == 0);
        if (L[i] == '1') {
          dp[i+1][ns] += dp[i][s];
          dp[i+1][ns] %= MOD;
        } else { // L[i] == '0'
          if (s > 0) {
            dp[i+1][ns] += dp[i][s];
            dp[i+1][ns] %= MOD;
          } else {
            if (l == 0 && r == 0) { // if s == 0,
              dp[i+1][ns] += dp[i][s];
              dp[i+1][ns] %= MOD;
            }
          }
        }
      }
    }
  }

  cout << dp[N][0] + dp[N][1] << endl;
}
