// ref. https://suikaba.hatenablog.com/entry/2017/08/26/172626

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

// StronglyConnectedComponents.
typedef vector<vector<ll>> UnWeightedGraph;

template<typename G>
struct StronglyConnectedComponents {
  const G &g;
  UnWeightedGraph gg, rg;
  vector<ll> comp, order, used;

  StronglyConnectedComponents(const G& g) : g(g), gg(g.size()), rg(g.size()), comp(g.size(), -1ll), used(g.size()) {
    rep(i,g.size()) {
      for(auto e : g[i]) {
        gg[i].emplace_back((ll) e);
        rg[(ll)e].emplace_back(i);
      }
    }
  }

  ll operator[](ll k) {
    return comp[k];
  }

  void dfs(ll idx) {
    if (used[idx]) return;
    used[idx] = true;
    for (ll to : gg[idx]) dfs(to);
    order.push_back(idx);
  }

  void rdfs(ll idx, ll cnt) {
    if (comp[idx] != -1) return;
    comp[idx] = cnt;
    for (ll to : rg[idx]) rdfs(to, cnt);
  }

  void build(UnWeightedGraph& t) {
    rep(i,gg.size()) { dfs(i); }
    reverse(all(order));
    ll ptr = 0;
    for(ll i : order) {
      if (comp[i] == -1) { rdfs(i, ptr), ptr++; }
    }

    t.resize(ptr);
    rep(i,g.size()) {
      for(auto &to : g[i]) {
        ll x = comp[i], y = comp[to];
        if(x == y) continue; // skip edge to self
        t[x].push_back(y);
      }
    }
  }
};

// int main(int argc, char** argv) {
//   cin.tie(NULL);
//   cout.tie(NULL);
//   ios_base::sync_with_stdio(false);
//   //cout << setprecision(10) << fixed;
//
//   ll n,m;
//   cin >> n >> m;
//   g.resize(n);
//   rep(i,m) {
//     ll s,t;
//     cin >> s >> t;
//     g[s].push_back(t);
//   }
//
//   UnWeightedGraph buff; // result graph. unused in this problem.
//   StronglyConnectedComponents<UnWeightedGraph> scc(g);
//   scc.build(buff);
//
//   ll q;
//   cin >> q;
//   rep(iter,q) {
//     ll u,v;
//     cin >> u >> v;
//     if (scc[u] == scc[v]) {
//       cout << 1 << endl;
//     } else {
//       cout << 0 << endl;
//     }
//   }
// }

vector<vector<ll>> g; // matrix
UnWeightedGraph g_list; // adjacency list

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  g.assign(n,vector<ll>(n));
  g_list.resize(n);
  rep(i,n)rep(j,n) {
    cin >> g[i][j];
    if (g[i][j] == 1) {
      g_list[i].push_back(j);
    }
  }

  UnWeightedGraph t; // result graph.
  StronglyConnectedComponents<UnWeightedGraph> scc(g_list);
  scc.build(t);

  int const K = t.size(); // count of scc result graph.
  rep(i,K) {
    // Remove duplicated edges
    sort(all(t[i]));
    t[i].erase(unique(all(t[i])), t[i].end());
  }

  // st[i] .. vertices in each vertice in t.
  vector<ll> sz(K+1);
  rep(i,n) {
    ++sz[scc[i]];
  }

  // todo .. vertices in topologicaly sorted order. K is dummy. return idx of t.
  vector<int> todo(K+1);
  todo[0] = K;
  rep(i,K) { todo[i+1] = i; }

  // can[i][j] .. reachable from i to j.
  vector<vector<bool>> can(K+1,vector<bool>(K+1));
  rep(i,K) {
    can[K][i] = true; // start vertex to all vertices
    for (ll u : t[i]) { // u is reachable from i
      can[i][u] = true;
    }
  }

  // Calculate by the way similar to warshal-froid.
  rep(k,K+1)rep(i,K+1)rep(j,K+1) {
    can[i][j] = can[i][j] || (can[i][k]&&can[k][j]);
  }

  // dp[i][j] .. maximum count of using [0,i] and [0,j]. i>j.
  vector<vector<ll>> dp(K+1, vector<ll>(K+1));
  rep(i,K+1) {
    rep(j,i) {
      int u = todo[i], v = todo[j];
      chmax(dp[u][v], sz[u]+sz[v]); // start from (u,v)
      for (int k = i+1; k <= K; ++k) {
        int w = todo[k];
        if (can[u][w]) {
          chmax(dp[w][v], dp[u][v] + sz[w]);
        }
        if(can[v][w]) {
          chmax(dp[w][u], dp[u][v] + sz[w]);
        }
      }
    }
  }

  ll ans = 0;
  rep(i,K+1)rep(j,K+1) {
    chmax(ans, dp[i][j]);
  }
  cout << ans << endl;
}
