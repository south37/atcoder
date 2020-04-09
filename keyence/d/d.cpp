// ref. https://atcoder.jp/contests/keyence2020/submissions/9549557

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

  ll n;
  cin >> n;
  vector<ll> a(n);
  vector<ll> b(n);
  rep(i, n) {
    cin >> a[i];
  }
  rep(i, n) {
    cin >> b[i];
  }

  // dp[mask][k] .. minimum count when mask is selected and k is last.
  vector<vector<ll>> dp(1ll<<n, vector<ll>(n, INF));
  ll m = 1ll << n;
  rep(i, n) {
    dp[1ll<<i][i] = 0;
  }
  rep(i, m) { // i is current state
    ll c = __builtin_popcount(i);
    ll cnt = c; // inversion number
    rep(j, n) { // j is last element
      if ((1ll<<j) & i) {
        --cnt; // e.g. when first element is located at k, then inversion number is k-1 (1-indexed)
        ll pre = i^(1ll<<j); // pre is prev state
        rep(k, n) {
          if ((1ll<<k) & pre) { // k is prev element
            ll prv = (c^k)%2 ? b[k] : a[k]; // c is 1-indexed, k is 0-indexed.
            ll cur = (c^j)%2 ? a[j] : b[j];
            if (prv <= cur) { // valid
              chmin(dp[i][j], dp[pre][k] + cnt);
            }
          }
        }
      }
    }
  }

  ll ans = INF;
  rep(i, n) {
    chmin(ans, dp[m-1][i]);
  }
  if (ans == INF) {
    cout << -1 << endl;
  } else {
    cout << ans << endl;
  }
}
