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

  ll ans = 0;
  for (int i = N-1; i >= 0; --i) {
    int cur = S[i] - 'a';

    ll c = 1; // count from S[i..-1]
    rep(j, 26) {
      if (j == cur) { continue; } // current char must not be multiplied.

      c *= (cnts[j] + 1); // Each chars or nothing.
      c %= MOD;
    }
    ans += c;
    ans %= MOD;

    ++cnts[cur];
  }

  cout << ans << endl;
}
