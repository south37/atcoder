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

vector<ll> ans;
vector<vector<ll>> g;
vector<ll> a;
vector<ll> dp;

void dfs(ll v, ll p=-1) {
  // Update dp
  ll pre;
  ll len = dp.size();
  ll idx = lower_bound(all(dp), a[v]) - dp.begin();
  if (idx == len) { // idx is end(), should be added.
    dp.push_back(a[v]);
  } else { // idx < len. should replace.
    pre = dp[idx];
    dp[idx] = a[v];
  }

  ans[v] = dp.size();

  for (ll u : g[v]) {
    if (u == p) { continue; }
    dfs(u, v);
  }

  // Revert dp
  if (idx == len) {
    dp.pop_back();
  } else {
    dp[idx] = pre;
  }
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  ans.resize(n);
  g.resize(n);
  a.resize(n);

  rep(i,n) {
    cin >> a[i];
  }
  rep(iter,n-1) {
    ll u, v;
    cin >> u >> v;
    --u; --v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  dfs(0);

  rep(i,n) {
    cout << ans[i] << endl;
  }
}
