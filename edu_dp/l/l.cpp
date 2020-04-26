// ref. https://juppy.hatenablog.com/entry/2019/03/18/Educational_DP_Contest%28EDPC%29_G~K_Python_%E7%AB%B6%E6%8A%80%E3%83%97%E3%83%AD%E3%82%B0%E3%83%A9%E3%83%9F%E3%83%B3%E3%82%B0_Atcoder#EDPC--L

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

const ll N = 3005;
// dp[i][j] .. X value when start from [i,j].
ll dp[N][N];
ll a[N];
ll n;

// [i, j]
ll rec(ll i, ll j) {
  if (i > j) { return 0; } // no elements are left.
  if (dp[i][j] >= 0) { return dp[i][j]; }
  if ((j-i+1)%2 == n%2) { // first one
    ll left  = rec(i+1, j) + a[i];
    ll right = rec(i, j-1) + a[j];
    return dp[i][j] = max(left, right);
  } else {
    ll left  = rec(i+1, j);
    ll right = rec(i, j-1);
    return dp[i][j] = min(left, right);
  }
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  cin >> n;
  ll s = 0;
  rep(i, n) {
    cin >> a[i];
    s += a[i];
  }
  memset(dp, -1, sizeof(dp));
  ll X = rec(0, n-1);
  ll ans = 2*X - s;
  cout << ans << endl;
}
