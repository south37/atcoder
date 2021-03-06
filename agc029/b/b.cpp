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
  ll N;
  cin >> N;
  vector<ll> A(N);
  rep(i, N) {
    cin >> A[i];
  }
  sort(all(A));
  reverse(all(A));

  map<ll, int> m;
  rep(i, N) {
    ++m[A[i]];
  }

  ll ans = 0;
  rep(i, N) {
    if (m[A[i]] == 0) { continue; }  // already erased
    --m[A[i]];

    ll t = 1LL; // The summed value of A[i] + A[j] where j < i and A[i] + A[j] == 2 ** k.
    while (t <= A[i]) { t <<= 1; }

    if (m[t-A[i]] > 0) {
      ++ans;
      --m[t-A[i]];
    }
  }
  cout << ans << endl;
}
