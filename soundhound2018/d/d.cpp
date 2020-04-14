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

const ll INF = 1e16;
const ll MOD = 1000000007;  // 1e9 + 7

struct edge {
  int from;
  int to;
  int cost;
  edge(int from, int to, int cost) : from(from), to(to), cost(cost) {}
};

vector<vector<edge>> g;
vector<vector<edge>> revG;

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n, m, s, t;
  cin >> n >> m >> s >> t;
  --s; --t; // 0-indexed

  g.resize(n);
  revG.resize(n);

  rep(i, m) {
    ll u, v, a, b;
    cin >> u >> v >> a >> b;
    --u; --v; // 0-indexed
    g[u].push_back(edge(u, v, a));
    g[v].push_back(edge(v, u, a));
    revG[u].push_back(edge(u, v, b));
    revG[v].push_back(edge(v, u, b));
  }

  // Start dijkstra from s
  vector<ll> start(2);
  start[0] = s;
  start[1] = t;
  vector<vector<ll>> ds(2, vector<ll>(n, INF));
  vector<vector<vector<edge>>> graphs;
  graphs.push_back(g);
  graphs.push_back(revG);

  rep(k, 2) {
    ll st = start[k];
    vector<ll>& d = ds[k];
    auto& g = graphs[k];

    d[st] = 0;
    priority_queue<P, vector<P>, greater<P> > q;
    q.push(P(0, st));
    while (!q.empty()) {
      P p = q.top(); q.pop();
      int v = p.second;
      if (d[v] < p.first) { continue; }  // Already updated.
      for (auto e : g[v]) {
        if (d[e.to] > d[v] + e.cost) {
          d[e.to] = d[v] + e.cost;
          q.push(P(d[e.to], e.to));
        }
      }
    }
  }
  // cout << "ds[0]: "; printvec(ds[0]);
  // cout << "ds[1]: "; printvec(ds[1]);

  // Here, ans is min of ds[0][i] + ds[1][i]
  vector<ll> dp(n); // min cost at year i. At i, we can use [i, n) as trade
  dp[n-1] = ds[0][n-1] + ds[1][n-1];
  for (int i = n-2; i >= 0; --i) {
    dp[i] = min(dp[i+1], ds[0][i] + ds[1][i]);
  }

  ll initial = (ll)1e15;
  rep(i, n) {
    cout << initial - dp[i] << endl;
  }
}
