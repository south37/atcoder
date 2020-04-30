// ref. https://www.ioi-jp.org/joi/2014/2015-ho/2015-ho-t2-review.pdf

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

ll n;
vector<ll> a;
// dp[i][j] = max(dp[i+1][j]+a[i], dp[i][j-1]+a[j]) when (j-i+1)%2==n%2,
//            dp[i+1][j](a[i]>a[j]) or dp[i][j-1](a[i]<a[j]) when (j-i+1)%2!=n%2.
// dp[i][i] = 0.
vector<vector<ll>> dp;

ll rec(ll i, ll j) {
  if (i == j) { // last one
    if (n%2 == 1) {
      return a[i];
    } else {
      return 0;
    }
  }
  assert(i < j);
  if (dp[i][j] >= 0) { return dp[i][j]; }

  if ((j-i+1)%2 == n%2) { // first
    dp[i][j] = max(rec(i+1, j)+a[i], rec(i, j-1)+a[j]);
  } else {
    if (a[i] > a[j]) {
      dp[i][j] = rec(i+1, j);
    } else {
      dp[i][j] = rec(i, j-1);
    }
  }
  return dp[i][j];
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  cin >> n;
  a.resize(2*n);
  dp.assign(2*n, vector<ll>(2*n, -1));

  rep(i,n) {
    cin >> a[i];
  }
  rep(i,n) {
    a[i+n] = a[i];
  }

  ll ans = 0;
  rep(i,n) {
    ll now = a[i];
    now += rec(i+1, i+n-1); // rec(1,n-1) when i == 0.
    chmax(ans, now);
  }
  cout << ans << endl;
}
