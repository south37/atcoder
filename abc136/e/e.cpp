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

int main(int argc, char** argv) {
  int N, K;
  cin >> N >> K;
  vector<ll> A(N);
  rep(i, N) {
    cin >> A[i];
  }

  ll S = 0;
  rep(i, N) {
    S += A[i];
  }
  // For Debug
  // cout << "sum: " << S << endl;

  set<ll> gcds;
  for (ll i = 2; i <= sqrt(S); ++i) { // i is the divisor
    if ((S % i) == 0) {
      gcds.insert(i);
      gcds.insert(S / i);
    }
  }
  gcds.insert(S);
  // For Debug
  // for (auto x : gcds) {
  //   cout << x << " ";
  // }
  // cout << endl;

  ll ans = 0;

  for (auto it = gcds.rbegin(); it != gcds.rend(); ++it) { // Try x in decreasing order.
    ll x = *it;

    // a[i]: (A[i] % x) = d (-d). increasing order.
    // b[i]: x - a[i]   = x-d (+ x-d). decreasing order.
    vector<ll> a(N);
    rep(i, N) {
      a[i] = A[i] % x;
    }
    sort(all(a));
    vector<ll> b(N);
    rep(i, N) {
      b[i] = x - (a[i]);
    }

    // For Debug
    // cout << "a: ";
    // rep(i, N) {
    //   cout << a[i] << " ";
    // }
    // cout << endl;
    // cout << "b: ";
    // rep(i, N) {
    //   cout << b[i] << " ";
    // }
    // cout << endl;

    // sumA[i]: summention of a from 0 to i.
    // sumB[i]: summention of b from i to N-1.
    vector<ll> sumA = a;
    vector<ll> sumB = b;
    for (int i = 0; i < N-1; ++i) {
      sumA[i+1] += sumA[i];
    }
    for (int i = N-1; i > 0; --i) {
      sumB[i-1] += sumB[i];
    }

    // Find the k in which sumA[k] = sumB[k+1]
    int k;
    for (k = 0; k < N-1; ++k) {
      if (sumA[k] == sumB[k+1]) { break; }
    }
    int summed = 0;
    for (int i = 0; i <= k; ++i) {
      summed += a[i];
    }
    if (summed <= K) { // OK.
      ans = x;
      break;
    }
  }

  if (ans > 0) {
    cout << ans << endl;
  } else {
    cout << 1 << endl;
  }
}
