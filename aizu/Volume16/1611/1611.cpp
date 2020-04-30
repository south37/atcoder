// ref. https://ferin-tech.hatenablog.com/entry/2017/05/17/123005

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

void solve() {
  // dp[l][r] = dp[l+1][r-1] + 2 if dp[l+1][r-1] == d-2 && abs(a[l]-a[r]) <= 1
  vector<vector<ll>> dp(n, vector<ll>(n));

  for (ll d = 2; d <= n; ++d) { // dist
    rep(l,n) {
      ll r = l+d-1; // we consider [l,r]
      if (r >= n) { continue; }
      if (dp[l+1][r-1] == d-2 && abs(a[l]-a[r]) <= 1) {
        chmax(dp[l][r], d);
      }
      for (ll k = l; k < r; ++k) {
        chmax(dp[l][r], dp[l][k] + dp[k+1][r]);
      }
    }
  }
  cout << dp[0][n-1] << endl;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  while (true) {
    cin >> n;
    if (n == 0) { break; } // exit
    a.resize(n);
    rep(i,n) {
      cin >> a[i];
    }
    solve();
  }
}
