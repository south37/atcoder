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

ll BIT_MAX_N = 2000100100;
ll bit[2000100105]; // bit[0] is dummy.
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

const ll offset = 1e9 + 1;

int main(int argc, char** argv) {
  int N;
  cin >> N;
  vector<P> p;
  rep(i, N) {
    ll x, y;
    cin >> x >> y;
    x += offset;
    y += offset;
    p.emplace_back(x, y);
  }
  sort(all(p)); // increasing order by x

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
  rep(i, N) {
    cout << "(" << p[N - 1 - i].first - offset << ", " << p[N - 1 - i].second - offset << ")" << endl;
    cout << "left upper: " << left_uppers[i] << endl;
    cout << "left lower: " << left_lowers[i] << endl;
    cout << "right upper: " << right_uppers[i] << endl;
    cout << "right lower: " << right_lowers[i] << endl;
  }

  ll ans = 0;
  rep(i, N) {
    // ans += (left_uppers[i] + 1) * (left_lowers[i] + 1) * (right_uppers[i] + 1) * (right_lowers[i] + 1);
    ll cnt = 1;
    cnt *= left_uppers[i] + 1;
    cnt %= MOD;
    cnt *= left_lowers[i] + 1;
    cnt %= MOD;
    cnt *= right_uppers[i] + 1;
    cnt %= MOD;
    cnt *= right_lowers[i] + 1;
    cnt %= MOD;

    ans += cnt;
    ans %= MOD;
  }

  cout << ans << endl;
}
