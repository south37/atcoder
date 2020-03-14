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

template<class T> void printvec(const vector<T>& v) {
  for (auto x : v) { cout << x << " "; }
  cout << endl;
}
template<class T> void printtree(const vector< vector<T> >& tree) {
  for (long long i = 0; i < tree.size(); ++i) {
    cout << i + 1 << ": "; printvec(tree[i]);
  }
}
template<class T, class U> void printmap(const map<T, U>& mp) {
  for (auto x : mp) { cout << x.first << "=>" << x.second << endl; }
}

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }

#define rep(i, n) for(ll i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()
#define fr first
#define sc second
#define mp make_pair
#define pb push_back

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

ll n;
vector<ll> a;
vector<ll> s; // s[i] .. the sum of a in [0, i)

// return the pair of <sum, count>
pair<ll, ll> calc(ll x) {
  ll sum = 0, cnt = 0;
  rep(i, n) {
    // x-a[i] is the pair of a[i]. we want to find the boundary.
    ll j = lower_bound(all(a), x-a[i]) - a.begin();;
    cnt += n-j; // the count of [j, n)
    sum += s[n] - s[j];
    sum += a[i] * (n-j);
  }
  return mp(sum, cnt);
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll m;
  cin >> n >> m;
  a.resize(n);
  s.resize(n+1);

  rep(i, n) {
    cin >> a[i];
  }
  sort(all(a));
  // printvec(a);

  rep(i, n) {
    s[i+1] = s[i] + a[i];
  }
  // printvec(s);

  ll l = 0;
  ll r = 2e5 + 5;
  // find the boundary in [l, r).
  // The count is equal or larger than m, [t, ..., t, f, ..., f]
  while (r - l > 1) {
    ll mid = (l+r)/2;
    if (calc(mid).second >= m) { // ok
      l = mid;
    } else {
      r = mid;
    }
  }
  // Here, l is the largest true value.

  auto p = calc(l);
  ll ans = p.first;
  ans -= (p.second - m)*l; // We want to know the sum of exact m values.
  cout << ans << endl;
}
