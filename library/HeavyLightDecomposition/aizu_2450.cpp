// ref. https://ei1333.github.io/luzhiled/snippets/tree/heavy-light-decomposition.html

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

// HeavyLightDecomposition
template<typename G>
struct HeavyLightDecomposition {
  G &g;
  vector<int> sz, in, out, head, rev, par;

  HeavyLightDecomposition(G &g) : g(g), sz(g.size()), in(g.size()), out(g.size()), head(g.size()), rev(g.size()), par(g.size()) {}

  void dfs_sz(int idx, int p) {
    par[idx] = p;
    sz[idx] = 1;
    if(g[idx].size() && g[idx][0] == p) swap(g[idx][0], g[idx].back());
    for(auto &to : g[idx]) {
      if(to == p) continue;
      dfs_sz(to, idx);
      sz[idx] += sz[to];
      if(sz[g[idx][0]] < sz[to]) swap(g[idx][0], to);
    }
  }

  void dfs_hld(int idx, int par, int &times) {
    in[idx] = times++;
    rev[in[idx]] = idx;
    for(auto &to : g[idx]) {
      if(to == par) continue;
      head[to] = (g[idx][0] == to ? head[idx] : to);
      dfs_hld(to, idx, times);
    }
    out[idx] = times;
  }

  void build() {
    dfs_sz(0, -1);
    int t = 0;
    dfs_hld(0, -1, t);
  }

  int la(int v, int k) {
    while(1) {
      int u = head[v];
      if(in[v] - k >= in[u]) return rev[in[v] - k];
      k -= in[v] - in[u] + 1;
      v = par[u];
    }
  }

  int lca(int u, int v) {
    for(;; v = par[head[v]]) {
      if(in[u] > in[v]) swap(u, v);
      if(head[u] == head[v]) return u;
    }
  }

  // q .. query for path vector.
  // f .. merge operation for two results of q.
  template<typename T, typename Q, typename F>
  // T query(int u, int v, const T &ti, const Q &q, const F &f, bool edge = false) {
  pair<T,T> query(int u, int v, const T &ti, const Q &q, const F &f, bool edge = false) {
    T l = ti, r = ti;
    for(;; v = par[head[v]]) {
      if(in[u] > in[v]) swap(u, v), swap(l, r);
      if(head[u] == head[v]) break;
      l = f(q(in[head[v]], in[v] + 1), l);
    }
    // return f(f(q(in[u] + edge, in[v] + 1), l), r);
    return { f(q(in[u] + edge, in[v] + 1), l), r };
  }

  template< typename Q >
  void add(int u, int v, const Q &q, bool edge = false) {
    for(;; v = par[head[v]]) {
      if(in[u] > in[v]) swap(u, v);
      if(head[u] == head[v]) break;
      q(in[head[v]], in[v] + 1);
    }
    q(in[u] + edge, in[v] + 1);
  }
};

// SegmentTree with State.
// State .. muximum containuous sum.
struct State {
  ll ans, whole, left, right;

  State() : ans(-INF), whole(0), left(-INF), right(-INF) {}

  State(ll val, int length) {
    whole = val * length;
    ans = left = right = (val > 0 ? whole : val);
  }

  State operator+(const State &s) const {
    State ret;
    ret.ans = max({ans, s.ans, right + s.left});
    ret.whole = whole + s.whole;
    ret.left = max(left, whole + s.left);
    ret.right = max(s.right, right + s.whole);
    return (ret);
  }
};

struct SegmentTree {
  vector<State> seg;
  vector<ll> lazy;
  int sz;

  SegmentTree(int n) {
    sz = 1;
    while(sz < n) sz <<= 1;
    seg.assign(2 * sz - 1, State());
    lazy.assign(2 * sz - 1, INF);
  }

  void push(int k, int l, int r) {
    if(lazy[k] == INF) return;
    seg[k] = State(lazy[k], r - l);
    if(k < sz - 1) {
      lazy[2 * k + 1] = lazy[k];
      lazy[2 * k + 2] = lazy[k];
    }
    lazy[k] = INF;
  }

  void update(int a, int b, int x, int k, int l, int r) {
    push(k, l, r);
    if(a >= r || b <= l) {
      return;
    }
    if(a <= l && r <= b) {
      lazy[k] = x;
      push(k, l, r);
      return;
    }
    update(a, b, x, 2 * k + 1, l, (l + r) >> 1);
    update(a, b, x, 2 * k + 2, (l + r) >> 1, r);
    seg[k] = seg[2 * k + 1] + seg[2 * k + 2];
  }

  State query(int a, int b, int k, int l, int r) {
    push(k, l, r);
    if(a >= r || b <= l) return (State());
    if(a <= l && r <= b) return (seg[k]);
    return (query(a, b, 2 * k + 1, l, (l + r) >> 1) +
            query(a, b, 2 * k + 2, (l + r) >> 1, r));
  }

  void update(int a, int b, int x) {
    update(a, b, x, 0, 0, sz);
  }

  State query(int a, int b) {
    return (query(a, b, 0, 0, sz));
  }

  void set(int k, int v) {
    seg[k + sz - 1] = State(v, 1);
  }

  void build() {
    for(int k = sz - 2; k >= 0; k--) {
      seg[k] = seg[2 * k + 1] + seg[2 * k + 2];
    }
  }
};

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n,q;
  cin >> n >> q;
  vector<ll> w(n);
  rep(i,n) {
    cin >> w[i];
  }
  vector<vector<ll>> g(n);
  rep(i,n-1) {
    ll u,v;
    cin >> u >> v;
    --u; --v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  // printvec(w);
  // printtree(g);

  HeavyLightDecomposition<vector<vector<ll>>> tree(g);
  tree.build();

  SegmentTree seg(n);
  rep(i,n) {
    seg.set(i, w[tree.rev[i]]);
  }
  seg.build();

  while(q--) {
    int t,a,b,c;
    cin >> t >> a >> b >> c;
    --a; --b;
    if (t == 1) { // modify
      tree.add(a, b,
        [&](int a, int b) { seg.update(a,b,c); }
      );
    } else { // t == 2. query
      pair<State,State> p = tree.query(a, b, State(),
        [&](int a, int b) { return seg.query(a,b); },
        [](const State& a, const State& b) { return a + b; }
      );
      State l = p.first;
      State r = p.second;
      swap(l.left, l.right);
      cout << (l+r).ans << endl;
    }
  }
}
