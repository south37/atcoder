// base: https://atcoder.jp/contests/agc037/submissions/7895840
// hint: https://www.youtube.com/watch?v=68Z88ttiuUg

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
const ll MOD = 998244353;

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

ll cnts[3]; // 0: r, 1: g, 2: b

int main(int argc, char** argv) {
  int N;
  cin >> N;
  string S;
  cin >> S;

  ll ans = 1;
  ll tmp = 0; // the count of mid color. e.g. The count of G in (BBB)(GG)
  rep(i, 3 * N) {
    int c;
    if (S[i] == 'R') {
      c = 0;
    } else if (S[i] == 'G') {
      c = 1;
    } else {
      c = 2;
    }

    int a = (c + 1) % 3;
    int b = (c + 2) % 3;

    if ((cnts[a] > 0) && (cnts[b] > 0)) { // we can make triple
      ans *= tmp;
      ans %= MOD;
      --cnts[a];
      --cnts[b];
      --tmp;
    } else if ((cnts[a] > 0) || (cnts[b] > 0)) {
      if (cnts[a] == 0) { swap(a, b); }
      // Now, cnts[a] > 0 and cnts[b] == 0
      if (cnts[a] > tmp) { // cnts[a] is the largest. e.g. a is B in (BBB)(GG)
        ans *= cnts[a] - tmp;
        ans %= MOD;
        ++tmp;
      }
      ++cnts[c];
    } else { // both are 0
      ++cnts[c];
    }
  }

  // ans *= N!
  rep(i, N) {
    ans *= (i + 1);
    ans %= MOD;
  }

  cout << ans << endl;
}
