// ref. https://ei1333.github.io/luzhiled/snippets/graph/two-edge-connected-components.html

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

// LowLink
template<typename G>
struct LowLink {
  const G &g;
  vector<int> used, ord, low;
  vector<int> articulation;
  vector<pair<int, int>> bridge;

  LowLink(const G &g) : g(g) {}

  int dfs(int idx, int k, int par) {
    used[idx] = true;
    ord[idx] = k++;
    low[idx] = ord[idx];
    bool is_articulation = false;
    int cnt = 0;
    for(auto &to : g[idx]) {
      if(!used[to]) {
        ++cnt;
        k = dfs(to, k, idx);
        low[idx] = min(low[idx], low[to]);
        is_articulation |= ~par && low[to] >= ord[idx];
        if(ord[idx] < low[to]) bridge.emplace_back(minmax(idx, (int) to));
      } else if(to != par) {
        low[idx] = min(low[idx], ord[to]);
      }
    }
    is_articulation |= par == -1 && cnt > 1;
    if(is_articulation) articulation.push_back(idx);
    return k;
  }

  virtual void build() {
    used.assign(g.size(), 0);
    ord.assign(g.size(), 0);
    low.assign(g.size(), 0);
    int k = 0;
    for(int i = 0; i < g.size(); i++) {
      if(!used[i]) k = dfs(i, k, -1);
    }
  }
};

// BiconectedGraph
template<typename G>
struct BiconectedGraph : LowLink<G> {
  using LL = LowLink<G>;
  vector< int > comp;

  BiconectedGraph(const G& g) : LL(g) {}

  int operator[](const int &k) {
    return comp[k];
  }

  void dfs(int idx, int par, int &k) {
    if(~par && this->ord[par] >= this->low[idx]) comp[idx] = comp[par];
    else comp[idx] = k++;
    for(auto &to : this->g[idx]) {
      if(comp[to] == -1) dfs(to, idx, k);
    }
  }

  void build(G& t) {
    LL::build();
    comp.assign(this->g.size(), -1);
    int k = 0;
    for(int i = 0; i < comp.size(); i++) {
      if(comp[i] == -1) dfs(i, -1, k);
    }
    t.resize(k);
    for(auto &e : this->bridge) {
      int x = comp[e.first], y = comp[e.second];
      t[x].push_back(y);
      t[y].push_back(x);
    }
  }
};

// LCA
template<typename T>
struct lca {
  ll n, root, l;
  vector< vector<ll> > to;
  vector< vector<T> > co; // co[i][j] .. costs between i - to[i][j]
  vector<ll> dep; // depth from root.
  vector<T> costs; // cumulative cost from root.
  vector< vector<ll> > par; // par[i][j] .. i's anccestor. The distance from i is 2**j.

  lca(ll n) : n(n), to(n), co(n), dep(n), costs(n) {
    l = 0;
    while ((1ll<<l) < n) { ++l; }
    par = vector< vector<ll> >(n+1, vector<ll>(l, n));
  }
  void addedge(ll a, ll b, T c = 0) {
    to[a].push_back(b);
    co[a].push_back(c);
    to[b].push_back(a);
    co[b].push_back(c);
  }
  void init(ll _root) {
    root = _root;
    dfs(root);
    rep(i, l-1) {
      rep(v, n) {
        par[v][i+1] = par[par[v][i]][i];
      }
    }
  }
  void dfs(ll v, ll d = 0, T c = 0, ll p = -1) {
    if (p != -1) { par[v][0] = p; }
    dep[v] = d;
    costs[v] = c;
    rep(i, to[v].size()) {
      ll u = to[v][i];
      if (u == p) { continue; }
      dfs(u, d + 1, c + co[v][i], v);
    }
  }
  ll operator()(ll a, ll b) { // lca between a and b
    if (dep[a] > dep[b]) { swap(a, b); }
    ll gap = dep[b] - dep[a];
    for (ll i = l-1; i >= 0; --i) {
      ll len = 1ll<<i;
      if (gap >= len) {
        gap -= len;
        b = par[b][i];
      }
    }
    if (a == b) { return a; }
    for (ll i = l-1; i>=0; --i) {
      ll na = par[a][i];
      ll nb = par[b][i];
      if (na != nb) {
        a = na;
        b = nb;
      }
    }
    return par[a][0];
  }
  ll length(ll a, ll b) {
    ll c = (*this)(a, b);
    return dep[a] + dep[b] - dep[c]*2;
  }
  ll cost(ll a, ll b) {
    ll c = (*this)(a, b);
    return costs[a] + costs[b] - costs[c]*2;
  }
};

// int main(int argc, char** argv) {
//   ll N, Q;
//   cin >> N >> Q;
//
//   lca<ll> g(N);
//
//   rep(i, N-1) {
//     ll a, b, d;
//     cin >> a >> b >> d;
//     --a; --b;
//     g.addedge(a, b, d); // add edge "a->b" and "b->a" with weight d.
//   }
//   g.init(0);
//
//   rep(i, Q) {
//     ll a, b;
//     cin >> a >> b;
//     --a; --b;
//     ll c = g(a, b); // c is the lowest common ancestor of a and b.
//     ll ans = g.costs[a] + g.costs[b] - g.costs[c] * 2; // The distance between a and b.
//     cout << a + 1 << "-" << b + 1 << ": " << ans << endl; // e.g. 1-4: 40
//   }
// }

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n,m;
  cin >> n >> m;
  vector<vector<int>> g(n);
  rep(i,m) {
    int u,v;
    cin >> u >> v;
    --u;--v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  BiconectedGraph<vector<vector<int>>> bcc(g);
  vector<vector<int>> t; // template
  bcc.build(t);

  lca<int> t2(t.size()); // LCA tree
  rep(v,t.size()) {
    for (int u : t[v]) {
      t2.addedge(v,u);
    }
  }
  t2.init(bcc[0]);

  ll q;
  cin >> q;
  rep(iter,q) {
    int a,b,c;
    cin >> a >> b >> c;
    --a;--b;--c;
    int x = bcc[a], y = bcc[b], z = bcc[c];
    if (t2.length(x,z) == t2.length(x,y) + t2.length(y,z)) { // ok
      cout << "OK" << endl;
    } else {
      cout << "NG" << endl;
    }
  }
}
