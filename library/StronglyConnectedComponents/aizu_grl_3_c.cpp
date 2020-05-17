// ref. https://ei1333.github.io/luzhiled/snippets/graph/strongly-connected-components.html

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
        if(x == y) continue;
        t[x].push_back(y);
      }
    }
  }
};

UnWeightedGraph g;

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n,m;
  cin >> n >> m;
  g.resize(n);
  rep(i,m) {
    ll s,t;
    cin >> s >> t;
    g[s].push_back(t);
  }

  UnWeightedGraph buff; // Result graph. Indices of vertices are topologicaly sorted. This graph contains duplicated edges.
  StronglyConnectedComponents<UnWeightedGraph> scc(g);
  scc.build(buff);

  ll q;
  cin >> q;
  rep(iter,q) {
    ll u,v;
    cin >> u >> v;
    if (scc[u] == scc[v]) {
      cout << 1 << endl;
    } else {
      cout << 0 << endl;
    }
  }
}
