// base: https://atcoder.jp/contests/agc031/submissions/7912574

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

int main(int argc, char** argv) {
  int N;
  cin >> N;
  vector<ll> c(N);
  rep(i, N) {
    cin >> c[i];
  }

  // dp[i] = sum of all dp[j] where c[j] != c[j+1] && c[j+1] == c[i].
  // When c[i], c[i+1], ..., c[k] are same, then we consider dp[i], dp[i+1], ... d[k] as same.
  vector<ll> dp(N);
  ll dpsum[200010]; // dpsum is the summerized count of each colors at each step i.
  memset(dpsum, 0, sizeof(dpsum));
  dpsum[c[0]] = 1; // initial value is 1.
  rep(i, N) {
    dp[i] = dpsum[c[i]];
    if ((i < N-1) && (c[i] != c[i+1])) {
      dpsum[c[i+1]] += dp[i];
      dpsum[c[i+1]] %= MOD;
    }
  }

  cout << dp[N-1] << endl;
}
