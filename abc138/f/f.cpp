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
int dp[60][2][2][2];

char l[61];
char r[61];

ll f(int pos, int flagX, int flagY, int flagZ) {
  if (pos == -1) {
    return 1;
  }
  if (dp[pos][flagX][flagY][flagZ] != -1) {
    return dp[pos][flagX][flagY][flagZ];
  }
  ll ret = 0;
  // x 0, y 0
  if (flagX || l[pos] == '0') {
    ret += f(pos - 1, flagX, (r[pos] == '1') ? 1 : flagY, flagZ);
  }
  // x 0, y 1
  if ((flagX || l[pos] == '0') && (flagY || r[pos] == '1') && flagZ) {
    ret += f(pos - 1, flagX, flagY, flagZ);
  }
  // x 1, y 1
  if (flagY || r[pos] == '1') {
    ret += f(pos - 1, (l[pos] == '0') ? 1 : flagX, flagY, 1);
  }
  ret %= MOD;
  dp[pos][flagX][flagY][flagZ] = ret;
  return ret;
}

int main(int argc, char** argv) {
  ll L, R;
  cin >> L >> R;
  for (ll i = 59; i >= 0; --i) {
    l[59 - i] = ((L >> i) & 1) ? '1' : '0';
    r[59 - i] = ((R >> i) & 1) ? '1' : '0';
  }
  // For Debug
  cout << l << endl;
  cout << r << endl;

  memset(dp, -1, sizeof(dp));
  ll ans = f(59, 0, 0, 0);
  cout << ans << endl;
}
