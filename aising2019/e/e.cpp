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

vector<ll> a;
vector<vector<ll>> g;

// dp1[v][k] .. sum of a[u] in connected component including v where all a[u] > 0. Other connected components are valid.
// dp2[v][k] .. sum of a[u] in connected component including v. Other connected components are valid.
vector<vector<ll>> dp1, dp2;

// flg .. if true, consider only positive value.
vector<ll> tr(const vector<ll>& dp, const vector<ll>& ch1, const vector<ll>& ch2, bool flg) {
  ll n = dp.size();
  ll m = ch1.size();

  vector<ll> ans(n+m-1, INF);
  rep(i, n) {
    if (dp[i] == INF) { continue; } // invalid
    rep(j, m) {
      // Update "i+j-1" as i and j is connected (it means -1). j must not be INF.
      if (i+j-1 >= 0) {
        if (ch1[j] != INF)         { chmin(ans[i+j-1], dp[i]+ch1[j]); }
        if (ch2[j] != INF && !flg) { chmin(ans[i+j-1], dp[i]+ch2[j]); }
      }
      // Update "i+j" as i is separated from j and j is vaid.
      if (ch1[j] != INF) { chmin(ans[i+j], dp[i]); }
      if (ch2[j] < 0)    { chmin(ans[i+j], dp[i]); }
    }
  }
  return ans;
}

void dfs(int v, int p = -1) {
  dp1[v].push_back(INF); // we can not achieve 0.
  dp1[v].push_back(a[v] > 0 ? a[v] : INF); // NOTE: Treat as INF when s[v] is not possitive. It is invalid in this case.
  dp2[v].push_back(INF); // we can not achieve 0.
  dp2[v].push_back(a[v]);
  for (ll u : g[v]) {
    if (u == p) { continue; }
    dfs(u,v);
    dp1[v] = tr(dp1[v], dp1[u], dp2[u], true);
    dp2[v] = tr(dp2[v], dp1[u], dp2[u], false);
  }
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  a.resize(n);
  g.resize(n);
  dp1.resize(n);
  dp2.resize(n);
  rep(i,n) {
    cin >> a[i];
  }
  rep(i,n-1) {
    ll u,v;
    cin >> u >> v;
    --u;--v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  dfs(0);

  ll ans = -1;
  rep(i,n+1) {
    if (dp1[0][i] < INF) { ans = i-1; break;; } // all positive
    if (dp2[0][i] < 0) { ans = i-1; break; } // sum is minus
  }
  cout << ans << endl;
}
