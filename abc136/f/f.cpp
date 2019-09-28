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

ll BIT_MAX_N = 200010;
ll bit[200020]; // bit[0] is dummy.
void add(ll a, ll w) {
  for (ll x = a; x <= BIT_MAX_N; x += x & -x) {
    bit[x] += w;
  }
}
ll sum(ll a) {
  ll ret = 0;
  for (ll x = a; x > 0; x -= x & -x) {
    ret += bit[x];
  }
  return ret;
}

// target point is not included
// + o|x + x|o - o|o
//   x|o   o|x   o|o
// target point is included
// + x|x
//   x|x
ll f(ll left_upper, ll left_lower, ll right_upper, ll right_lower) {
  vector<ll> num = { left_upper, left_lower, right_upper, right_lower };
  vector<ll> o(4), ox(4);
  rep(i, 4) {
    ox[i] = powmod(2, num[i]);
    o[i] = ox[i] - 1;
  }
  ll res = 0;
  res += ((o[0]*ox[1] % MOD)*ox[2] % MOD)*o[3] % MOD;
  res %= MOD;
  res += ((ox[0]*o[1] % MOD)*o[2] % MOD)*ox[3] % MOD;
  res %= MOD;
  res -= ((o[0]*o[1] % MOD)*o[2] % MOD)*o[3] % MOD;
  res %= MOD;
  res += ((ox[0]*ox[1] % MOD)*ox[2] % MOD)*ox[3] % MOD;
  res %= MOD;

  return res;
}

int main(int argc, char** argv) {
  int N;
  cin >> N;
  vector<P> p;
  rep(i, N) {
    ll x, y;
    cin >> x >> y;
    p.emplace_back(x, y);
  }
  sort(all(p)); // increasing order by x

  // Compress y
  map<ll, ll> mp;
  vector<ll> ys(N);
  rep(i, N) { ys[i] = p[i].second; }
  sort(all(ys));
  rep(i, N) { mp[ys[i]] = i + 1; } // y must be larger than 0
  rep(i, N) { p[i].second = mp[p[i].second]; }

  // For Debug
  // rep(i, N) {
  //   cout << "(" << p[i].first << ", " << p[i].second << ")" << endl;
  // }

  vector<ll> left_uppers(N); // Stores the count in upper left.
  vector<ll> left_lowers(N); // Stores the count in lower left.
  rep(i, N) { // i is also the number of points already appeared
    ll y = p[i].second;
    ll lower_cnt = sum(y);
    add(y, 1);

    left_lowers[i] = lower_cnt;
    left_uppers[i] = i - lower_cnt;
  }

  // Clear
  rep(i, N) {
    ll y = p[i].second;
    add(y, -1);
  }

  reverse(all(p)); // decreasing order by x
  vector<ll> right_uppers(N); // Stores the count in upper right.
  vector<ll> right_lowers(N); // Stores the count in lower left.
  rep(i, N) { // i is also the number of points already appeared
    ll y = p[i].second;
    ll lower_cnt = sum(y);
    add(y, 1);

    right_lowers[i] = lower_cnt;
    right_uppers[i] = i - lower_cnt;
  }
  reverse(all(right_uppers));
  reverse(all(right_lowers));

  // For Debug
  reverse(all(p));
  rep(i, N) {
    cout << "(" << p[i].first << ", " << p[i].second << ")" << endl;
    cout << "left upper: " << left_uppers[i] << endl;
    cout << "left lower: " << left_lowers[i] << endl;
    cout << "right upper: " << right_uppers[i] << endl;
    cout << "right lower: " << right_lowers[i] << endl;
  }

  ll ans = 0;
  rep(i, N) {
    ans += f(left_uppers[i], left_lowers[i], right_uppers[i], right_lowers[i]);
  }
  cout << ans << endl;
}
