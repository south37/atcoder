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

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n, m, q;
  cin >> n >> m >> q;
  // dp[i][j] .. using[0,i), last value is j.
  vector<vector<ll>> dp(n+1, vector<ll>(m+1));
  vector<tuple<ll,ll,ll,ll>> queries;

  map<ll, vector<tuple<ll,ll,ll>>> mp;
  rep(iter,q) {
    ll a, b, c, d;
    cin >> a >> b >> c >> d;
    --a; --b; // 0-indexed
    // queries.push_back(tuple<ll,ll,ll,ll>(b,a,c,d));
    mp[b].push_back(tuple<ll,ll,ll>(a,c,d));
  }
  // sort(all(queries));
  // Here, queries are sorted by b.

  rep(i,n) {
    if (mp.find(i) != mp.end()) { // query exist
      vector<tuple<ll,ll,ll>>& p = mp[i];
      sort(all(p)); // sort by a.
      for (ll j = 1; j <= m; ++j) {
        for (auto& pp : p) {
          ll a, c, d;
          tie(a, c, d) = pp;
          cout << "a,b,c,d:" << a<<","<<i<<","<<c<<","<<d<<endl;
          // Here, if diff is c, add d
          if (j+c <= m) {
            chmax(dp[i][j+c], dp[a][j] + d);
          }
        }
      }
    }
  }
  printtree(dp);

  // Here, max value in dp[n-1] is result.
  ll ans = 0;
  for (ll i = 1; i <= m; ++i) {
    chmax(ans, dp[n-1][i]);
  }
  cout << ans << endl;
}
