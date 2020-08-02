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

const ll INF = 1e18;
const ll MOD = 1000000007;  // 1e9 + 7

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  vector<ll> ans(n+1, INF);
  vector<ll> x(n), y(n), p(n);
  rep(i,n) {
    cin >> x[i] >> y[i] >> p[i];
  }

  // xl[i][j] .. i: bit representation of roads, j: min distance from j to nearest road.
  vector<vector<ll>> xl(1ll<<n, vector<ll>(n)); // vertical
  vector<vector<ll>> yl(1ll<<n, vector<ll>(n)); // horizontal
  rep(i,1ll<<n) {
    rep(j,n) {
      xl[i][j] = abs(x[j]); // main road
      yl[i][j] = abs(y[j]); // main road
      rep(k,n) {
        if (i>>k&1) {
          chmin(xl[i][j], abs(x[j]-x[k]));
          chmin(yl[i][j], abs(y[j]-y[k]));
        }
      }
    }
  }

  rep(i,1ll<<n) {
    ll cnt = __builtin_popcount(i);
    // Loop in all sub sets. In ordinal case, we use
    // `for (ll j = i; j > 0; j=(j-1)&i) { ... }`, but we want to include j=0,
    // so it is slightly different.
    for (ll j = i; j >= 0; --j) {
      j &= i;
      // Here, we use `j` roads as xl.

      ll now = 0;
      rep(k,n) {
        if (!((i>>k)&1)) { // when k is not in i, it means we must calculate cost.
          now += min(xl[j][k], yl[i-j][k]) * p[k];
        }
      }
      chmin(ans[cnt], now);
    }
  }

  rep(i,n+1) {
    cout << ans[i] << endl;
  }
}
