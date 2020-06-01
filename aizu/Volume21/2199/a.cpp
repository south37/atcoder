#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string.h>
#include <set>
#include <stack>

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

const ll INF = 1e15;
const ll MOD = 1000000007;  // 1e9 + 7

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  while (true) {
    ll n,m;
    cin >> n >> m;
    if (n == 0 && m == 0) { break; }
    vector<ll> c(m);
    rep(i,m) {
      cin >> c[i];
    }
    vector<ll> x(n);
    rep(i,n) {
      cin >> x[i];
    }

    // dp[i][j] .. min cost using [0,i), select j as prev. j is in [0,255]
    vector<vector<ll>> dp(n+1,vector<ll>(256, INF));
    dp[0][128] = 0;
    rep(i,n) {
      rep(j,256) { // prev value
        if (dp[i][j] == INF) { continue; }
        // cout << "dp[i][j]: " << dp[i][j] << endl;
        rep(k,m) {
          ll now = j + c[k];
          chmax(now, 0ll);
          chmin(now, 255ll);
          ll cost = (x[i]-now)*(x[i]-now); // when select k, cost is (x[i]-now)^2
          chmin(dp[i+1][now], dp[i][j] + cost);
        }
      }
    }

    ll ans = INF;
    rep(i,256) {
      chmin(ans, dp[n][i]);
    }
    cout << ans << endl;
  }
}
