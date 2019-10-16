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
// prohibited: ?AGC, ?GAC, ?ACG, A?GC, AG?C
// prohibited: ?021, ?201, ?012, 0?21, 02?1

// dp[i][j][k][l] .. the count in position i with suffix j,k,l.
// dp[i+1][j][k][l] = sum dp[i][x][j][k] where (S[x,j,k,l] is not in [?AGC, ?GAC, ?ACG, A?GC, AG?C])
ll dp[105][4][4][4];

int main(int argc, char** argv) {
  int N;
  cin >> N;
  rep(j, 4) {
    rep(k, 4) {
      rep(l, 4) {
        if ((j == 0) && (k == 2) && (l == 1)) { continue; }
        if ((j == 2) && (k == 0) && (l == 1)) { continue; }
        if ((j == 0) && (k == 1) && (l == 2)) { continue; }
        dp[2][j][k][l] = 1;
      }
    }
  }

  for (int i = 2; i < N-1; ++i) {
    rep(j, 4) rep(k, 4) rep(l, 4) {
      rep(x, 4) {
        if ((j == 0) && (k == 2) && (l == 1)) { continue; }
        if ((j == 2) && (k == 0) && (l == 1)) { continue; }
        if ((j == 0) && (k == 1) && (l == 2)) { continue; }
        if ((x == 0) && (k == 2) && (l == 1)) { continue; }
        if ((x == 0) && (j == 2) && (l == 1)) { continue; }
        dp[i+1][j][k][l] += dp[i][x][j][k];
        dp[i+1][j][k][l] %= MOD;
      }
    }
  }

  ll ans = 0;
  rep(j, 4) {
    rep(k, 4) {
      rep(l, 4) {
        ans += dp[N-1][j][k][l];
        ans %= MOD;
      }
    }
  }
  cout << ans << endl;
}
