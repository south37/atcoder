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

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n, x, d;
  cin >> n >> x >> d;

  // Check the case when d = 0
  if (d == 0) {
    if (x == 0) {
      cout << 0 << endl;
      return 0;
    } else {
      cout << n+1 << endl;
      return 0;
    }
  }

  map<int, vector<P>> mp;
  rep(i, n+1) {
    // Here, we consider the case in which we use i.
    ll s = x*i;
    ll l = (ll)i*(i-1)/2; // the sum of [0, i)
    ll r = l + (ll)i*(n-i); // slide to [n-i, n)
    s += l*d;
    r -= l; // [l, r] is closed range. the distance is r+1.
    mp[((s%d)+d)%d].emplace_back(s, r);
  }

  ll ans = 0;
  for (auto& p : mp) {
    auto& a = p.second;
    int m = a.size();
    // subtract remainder and divide by d.
    rep(i, m) {
      a[i].first = (a[i].first - p.first)/d;
    }
    vector<P> ev;
    rep(i, m) {
      ev.emplace_back(a[i].first, 1);
      ev.emplace_back(a[i].first + a[i].second + 1, -1);
    }
    sort(all(ev));
    ll cnt = 0, pre = -INF;
    for (auto& e : ev) {
      ll len = e.first - pre;
      if (cnt) { ans += len; }
      cnt += e.second;
      pre = e.first;
    }
  }
  cout << ans << endl;
}
