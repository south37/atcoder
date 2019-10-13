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
  ll N, K;
  cin >> N >> K;
  vector<ll> a(N);
  rep(i, N) {
    cin >> a[i];
  }
  ll ans = 0;
  ll sum = 0;

  int r = 0;
  for (int l = 0; l < N; ++l) {
    while (sum < K) {
      if (r < N) {
        sum += a[r];
        ++r;
      } else {
        break;
      }
    }
    if (sum < K) { break; } // we can not increase sum.
    ans += N-r+1; // (N-1)-(r-1)+1 = N-r+1
    sum -= a[l];
  }
  cout << ans << endl;
}
