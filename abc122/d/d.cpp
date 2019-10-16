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

// A -> 0
// C -> 1
// G -> 2
// T -> 3
// prohibited: AGC, GAC, ACG
// prohibited: 021, 201, 012

// dp[i][j][k] .. the count in position i with suffix j,k.
// dp[i+1][j][k] = sum dp[i][x][j] where (S[x,j,k] is not in [AGC, GAC, ACG])
ll dp[105][4][4];

int main(int argc, char** argv) {
  int N;
  cin >> N;
  rep(j, 4) {
    rep(k, 4) {
      dp[1][j][k] = 1;
    }
  }

  for (int i = 1; i < N-1; ++i) {
    rep(j, 4) {
      rep(k, 4) {
        rep(x, 4) {
          if ((x == 0) && (j == 2) && (k == 1)) {
            continue;
          }
          if ((x == 2) && (j == 0) && (k == 1)) {
            continue;
          }
          if ((x == 0) && (j == 1) && (k == 2)) {
            continue;
          }
          // Now, x,j,k is OK.
          dp[i+1][j][k] += dp[i][x][j];
          dp[i+1][j][k] %= MOD;
        }
      }
    }
  }

  ll ans = 0;
  rep(j, 4) {
    rep(k, 4) {
      ans += dp[N-1][j][k];
      ans %= MOD;
    }
  }
  cout << ans << endl;
}
