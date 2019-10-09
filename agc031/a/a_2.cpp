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
  string S;
  cin >> S;

  // Check the count of chars from last.
  int cnts[26]; // The count of each chars. The index is chr - 'a'.
  memset(cnts, 0, sizeof(cnts));

  rep(i, N) {
    int cur = S[i] - 'a';
    ++cnts[cur];
  }

  ll ans = 1;
  rep(j, 26) {
    ans *= (cnts[j] + 1); // Each chars or nothing.
    ans %= MOD;
  }
  ans -= 1;
  (ans += MOD) %= MOD;

  cout << ans << endl;
}
