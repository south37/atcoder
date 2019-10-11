// base: https://atcoder.jp/contests/agc030/submissions/7566849#

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

ll N, L;

ll solve(const vector<ll>& x) {
  vector<ll> sumx(x);
  for (int i = 1; i < N; i++) {
    sumx[i] += sumx[i - 1];
  }

  ll res = 0;
  rep(i, N) {  // i: starting point of turn.
    int mid = i + (N - i) / 2;  // The last index
    if ((N - i) % 2 == 0) {  // The number of remaining is even.
      ll val = 2 * (sumx[mid] - sumx[i] - x[mid] + x[i]) - x[mid] - 2 * (sumx[N - 1] - sumx[mid]) + (N - 1 - i) * L;
      res = max(res, val);
    } else {
      ll val = 2 * (sumx[mid] - sumx[i] - x[mid] + x[i]) + x[mid] - 2 * (sumx[N - 1] - sumx[mid]) + (N - 1 - i) * L;
      res = max(res, val);
    }
  }
  return res;
}

int main(int argc, char** argv) {
  cin >> L >> N;
  vector<ll> X(N);
  rep(i, N) {
    cin >> X[i];
  }
  // Try anti-clock order at first.
  ll ans = 0;
  ans = max(ans, solve(X));

  // Calculate reversed.
  reverse(all(X));
  rep(i, N) {
    X[i] = L - X[i];
  }
  ans = max(ans, solve(X));

  cout << ans << endl;
}
