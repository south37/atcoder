// ref. https://img.atcoder.jp/abc164/editorial.pdf

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

const ll INF = 1e13;
const ll MOD = 1000000007;  // 1e9 + 7

const ll MAX_A = 55;
const ll MAX_N = 55;

vector<ll> g[MAX_N];
ll cost[MAX_N][MAX_N]; // money
ll t[MAX_N][MAX_N]; // time

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n, m, s;
  cin >> n >> m >> s;
  ll maxA = 0;
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
    chmax(maxA, a);
  }
  rep(i, n) {
    g[i].push_back(i); // add self
  }
  rep(i, n) {
    ll a, b;
    cin >> a >> b;
    cost[i][i] = -a;
    t[i][i] = b;
  }

  // Do dijkstra
  ll MAX_COIN = (n-1) * MAX_A + 1;
  vector<ll> dp(n * MAX_COIN, INF);
  // (i,j) .. dp[i*MAX_COIN, j]. position i, coin j.
  priority_queue<P, vector<P>, greater<P>> q;
  chmin(s, MAX_COIN-1); // we don't need to consider large s
  dp[s] = 0; // (0, s)
  q.push({ 0, s });
  while (!q.empty()) {
    auto p = q.top(); q.pop();
    ll nd = p.first;
    ll vv = p.second;
    if (nd > dp[vv]) { continue; } // already updated

    ll v = vv / MAX_COIN; // vertex
    ll j = vv % MAX_COIN; // remaining coin

    for (int nv : g[v]) {
      // Here, we consider v -> nv
      ll nj = j - cost[v][nv];
      if (nj < 0) { continue; } // invalid
      chmin(nj, MAX_COIN-1); // we don't need to consider large s
      // Here, 0 <= nj < MAX_COIN
      if (dp[nv*MAX_COIN + nj] > nd + t[v][nv]) {
        dp[nv*MAX_COIN + nj] = nd + t[v][nv];
        q.push({ dp[nv*MAX_COIN + nj], nv*MAX_COIN + nj });
      }
    }
  }

  for (ll v = 1; v < n; ++v) {
    ll ans = INF;
    rep(i, MAX_COIN) {
      chmin(ans, dp[v*MAX_COIN + i]);
    }
    cout << ans << endl;
  }
}
