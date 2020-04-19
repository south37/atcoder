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
  vector<pair<ll, ll>> a(n); // pair of <value, id>
  rep(i, n) {
    cin >> a[i].first;
    a[i].second = i + 1; // 1-indexed
  }
  sort(all(a));
  reverse(all(a));
  // For Debug
  // rep(i, n) {
  //   cout << a[i].first << " " << a[i].second << endl;
  // }

  vector<vector<ll>> dp(n+1, vector<ll>(n+1)); // dp[x][y] .. max score when selecting x as (i-pi) and y as (pi-i).
  rep(x, n) rep(y, n) {
    ll now = x + y;
    if (now >= n) { continue; }
    ll px = x+1; // 1, 2, ...
    ll py = n-y; // n, n-1, ...
    chmax(dp[x+1][y], dp[x][y] + a[now].first * (a[now].second - px));
    chmax(dp[x][y+1], dp[x][y] + a[now].first * (py - a[now].second));
  }

  ll ans = 0;
  rep(i, n+1) {
    chmax(ans, dp[i][n-i]);
  }
  cout << ans << endl;
}
