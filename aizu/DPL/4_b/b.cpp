// ref. https://ferin-tech.hatenablog.com/entry/2017/03/29/155630

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
#define sz(x) (ll)(x).size()
#define fr first
#define sc second
#define mp make_pair
#define pb push_back
#define eb emplace_back

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;
typedef vector<ll> vl;
typedef vector<P> vp;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

// BIT (Fenwick Tree) with 0-indexed query
// https://youtu.be/lyHk98daDJo?t=7960
template<typename T>
struct BIT {
  int n;
  vector<T> d;
  BIT(int n=0) : n(n), d(n+1) {}
  void add(int i, T x=1) {
    i++; // 0-indexed to 1-indexed
    for (; i <= n; i += i&-i) {
      d[i] += x;
    }
  }
  // The sum of [0, i]
  T sum(int i) {
    i++; // 0-indexed to 1-indexed
    T x = 0;
    for (; i; i -= i&-i) {
      x += d[i];
    }
    return x;
  }
  // The sum of [l, r)
  T sum(int l, int r) {
    return sum(r-1) - sum(l-1);
  }
};

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n, k, l, r;
  cin >> n >> k >> l >> r;
  vector<ll> a(n);
  rep(i,n) {
    cin >> a[i];
  }

  ll n2 = n/2;
  ll remain = n-n2;
  vector<vector<vector<ll>>> dp(2);
  dp[0].resize(n2+1); // prev
  dp[1].resize(remain+1); // latter

  rep(k,2) {
    ll m = dp[k].size()-1;

    rep(i,1ll<<m) {
      ll v = 0; // sum of value
      ll cnt = 0; // count
      rep(j,m) {
        if (i&(1ll<<j)) {
          v += a[j];
          ++cnt;
        }
      }
      dp[k][cnt].push_back(v);
    }
    reverse(all(a));
  }
  rep(i,n2) {
    sort(all(dp[0][i]));
  }

  vector<vector<ll>>& dp1 = dp[0];
  vector<vector<ll>>& dp2 = dp[1];
  // printtree(dp1);
  // printtree(dp2);

  ll ans = 0;
  // Try all i in latter
  rep(i, k+1) { // loop in [0,k]
    if (i+n2 < k) { continue; } // too small
    if (i > remain) { continue; } // too large
    // Here, consider i and k-i.
    for (ll v : dp2[i]) {
      // Here, l <= lv+rv <= r
      // <=> l-rv <= lv <= r-rv
      ll rdx = upper_bound(all(dp1[k-i]), r-v) - dp1[k-i].begin();
      ll ldx = lower_bound(all(dp1[k-i]), l-v) - dp1[k-i].begin();
      // result is count of [lit, rit)
      ans += rdx-ldx;
    }
  }
  cout << ans << endl;
}
