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

#define rep(i, n) for(ll i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

int main(int argc, char** argv) {
  ll N;
  cin >> N;

  vector<ll> factors;
  for (ll k = 2; k <= N; ++k) {
    ll n = k;

    // Calculate prime factors.
    ll i = 2;
    while (i * i <= n) {
      while ((n % i) == 0) {
        factors.push_back(i);
        n /= i;
        // For Debug
      }
      ++i;
    }
    if (n > 1) {
      factors.push_back(n);
    }
  }
  map<ll, ll> mp;
  for (auto x : factors) {
    ++mp[x];
  }

  // For Debug
  // for (auto x : mp) {
  //   cout << x.first << ": " << x.second << endl;
  // }

  // Here, we calculate the count of 74, 24, 14, 4, 2
  // (75) -> 1C1 = 1
  // (25, 3) -> 3C1 * (15-1)C1 = 42
  // (15, 5) -> 4C1 * (9-1)C1 = 32
  // (5, 5, 3) -> 9C2 * (15-2)C1 = 468
  ll c74 = 0;
  ll c24 = 0;
  ll c14 = 0;
  ll c4 = 0;
  ll c2 = 0;
  for (auto x : mp) {
    if (x.second >= 74) { ++c74; }
    if (x.second >= 24) { ++c24; }
    if (x.second >= 14) { ++c14; }
    if (x.second >= 4)  { ++c4; }
    if (x.second >= 2)  { ++c2; }
  }

  ll ans = 0;
  ans += c74;
  ans += c24 * max(0LL, c2-1);
  ans += c14 * max(0LL, c4-1);
  ans += c4 * max(0LL, c4-1) / 2 * max(0LL, c2-2);

  cout << ans << endl;
}
