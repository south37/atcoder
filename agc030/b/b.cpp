// base: https://atcoder.jp/contests/agc030/submissions/7566849#
// cf. https://ferin-tech.hatenablog.com/entry/2019/01/04/052343

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
    int mid = i + (N - i) / 2;  // The last index. e.g. If N = 10 and i = 0, then mid = 5.
    if ((N - i) % 2 == 0) {  // The number of remaining is odd. e.g. 0, 1, ... 9 exist, and i = 0. remaining is 1, 2, ... 9.
      // The result is (X[i]) + (X[i] + revX[N-1]) + (revX[N-1] + X[i+1]) + ... = (X[i]*2 + X[i+1]*2 + ... X[mid-1]*2) + ((L-X[mid+1])*2 + (L-X[mid+2])*2 + ... + (L-X[N-1])*2) + (L - X[mid])

      // [i, mid-1]
      ll val = 2 * (sumx[mid-1] - (i > 0 ? sumx[i-1] : 0));
      // [mid + 1, N-1]
      val += 2 * (N - 1 - mid) * L - 2 * (sumx[N - 1] - sumx[mid]);
      // [mid]
      val += L - x[mid];
      res = max(res, val);
    } else {
      ll val = 2 * (sumx[mid-1] - (i > 0 ? sumx[i-1] : 0)) + x[mid] - 2 * (sumx[N - 1] - sumx[mid]) + (N - 1 - i) * L;
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
