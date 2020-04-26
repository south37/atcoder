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

const ll INF = 1e15;
const ll MOD = 1000000007;  // 1e9 + 7

const ll MAX_A = 55;
const ll MAX_N = 55;

vector<vector<ll>> g;
vector<vector<ll>> dp;
vector<vector<ll>> cost;
vector<vector<ll>> t;
ll n, m;

ll rec(ll v, ll j) {
  cout << "v: " << v << endl;
  cout << "j: " << j << endl;
  if (j < 0 || j > dp[v].size()) { return INF; }
  if (dp[v][j] != INF) { return dp[v][j]; } // already calculated

  cout << "v: " << v << endl;
  cout << "j: " << j << endl;
  for (ll nv : g[v]) {
    // j = precost - cost[nv][v]
    ll precost = j - cost[nv][v];
    // cout << "dp[MAX_N * MAX_A]: " << dp[MAX_N * MAX_A] << endl;

    if (precost >= 0 && precost <= MAX_N) { // Here, consume a[u][v]
      cout << "nv: " << nv << endl;
      cout << "precost: " << precost << endl;
      cout << "MAX_N * MAX_A: " << MAX_N * MAX_A << endl;
      cout << "t[nv][v]: " << t[nv][v] << endl;
      cout << "rec(nv, precost): " << rec(nv, precost) << endl;
      ll now =
      chmin(dp[v][j], rec(nv, precost) + t[nv][v]);
      cout << "chmin success" << endl;
    }
  }
  return dp[v][j];
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll s;
  cin >> n >> m >> s;
  g.resize(n);
  cost.assign(n, vector<ll>(n, INF));
  t.assign(n, vector<ll>(n, INF));

  rep(i, m) {
    ll u, v, a, b;
    cin >> u >> v >> a >> b;
    --u; --v;
    g[u].push_back(v);
    g[v].push_back(u);
    cost[u][v] = a;
    cost[v][u] = a;
    t[u][v] = b;
    t[v][u] = b;
  }
  rep(i, n) {
    g[i].push_back(i); // add self
  }

  rep(i, n) {
    ll a, b;
    cin >> a >> b;
    cost[i][i] = -a;
    cost[i][i] = -a;
    t[i][i] = b;
    t[i][i] = b;
  }

  // For Debug
  cout << "g: " << endl;
  printtree(g);
  cout << "cost: " << endl;
  printtree(cost);
  cout << "t: " << endl;
  printtree(t);

  for (ll t = 1; t < n; ++t) {
    dp.assign(n, vector<ll>(MAX_A * MAX_N + 5, INF));
    dp[0][2] = 0; // start from 0

    ll ans = INF;
    rep(j, MAX_A * MAX_N) {
      chmin(ans, rec(t, j));
    }
    cout << ans << endl;
  }
}
