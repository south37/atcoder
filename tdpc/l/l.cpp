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

const ll N = 1005;

// dp[i][j] .. using [0,i), max value when left boundary is j-1 (including only [j,i)).
ll dp[N][N];

ll f[N][N];

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  rep(i,n) {
    rep(j,n) {
      cin >> f[i][j];
    }
  }

  rep(i,n+1)rep(j,n+1) { dp[i][j] = -INF; }
  dp[0][0] = 0;
  rep(i,n) {
    vector<ll> s(n+1); // s[j] .. sum of f in [0,j) with i.
    rep(j,n) {
      s[j+1] = s[j] + f[i][j];
    }
    // s[i]-s[j] .. sum of [j,i)
    ll now = -INF;
    rep(j,i+1) {
      // Here, use [j,i) as friend.
      chmax(now, dp[i][j] + (s[i]-s[j]));
      dp[i+1][j] = now;
    }
    dp[i+1][i+1] = now; // set max value for next use.
  }
  cout << dp[n][n]*2 << endl;
}
