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
  void addedge(ll a, ll b, T c) {
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
//     g.addedge(a, b, d);
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

  ll n;
  cin >> n;

  ll lead;
  lca<ll> g(n);
  rep(i,n) {
    ll p;
    cin >> p;
    --p;
    if (p >= 0) {
      g.addedge(p,i,0); // edge p->i
    } else {
      lead = i;
    }
  }
  g.init(lead);

  ll q;
  cin >> q;
  rep(iter,q) {
    ll a, b;
    cin >> a >> b;
    --a; --b;
    ll c = g(a, b); // c is the lowest common ancestor of a and b.
    if (c == b) {
      cout << "Yes" << endl;
    } else {
      cout << "No" << endl;
    }
  }
}
