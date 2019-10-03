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

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

ll powmod(ll x, ll n) { // like pow(x, n)
  ll r = 1;
  while (n) {
    if (n & 1) {
      r = r * x % MOD;
    }
    x = x * x % MOD;
    n >>= 1;
  }
  return r;
}

// LCA
template<typename T>
struct lca {
  int n, root, l;
  vector< vector<int> > to;
  vector< vector<T> > co; // co[i][j] .. costs between i - to[i][j]
  vector<int> dep; // depth from root.
  vector<T> costs; // cumulative cost from root.
  vector< vector<int> > par; // par[i][j] .. i's anccestor. The distance from i is 2**j.

  lca(int n) : n(n), to(n), co(n), dep(n), costs(n) {
    l = 0;
    while ((1<<l) < n) { ++l; }
    par = vector< vector<int> >(n+1, vector<int>(l, n));
  }
  void addedge(int a, int b, T c) {
    to[a].push_back(b);
    co[a].push_back(c);
    to[b].push_back(a);
    co[b].push_back(c);
  }
  void init(int _root) {
    root = _root;
    dfs(root);
    rep(i, l-1) {
      rep(v, n) {
        par[v][i+1] = par[par[v][i]][i];
      }
    }
  }
  void dfs(int v, int d = 0, T c = 0, int p = -1) {
    if (p != -1) { par[v][0] = p; }
    dep[v] = d;
    costs[v] = c;
    rep(i, to[v].size()) {
      int u = to[v][i];
      if (u == p) { continue; }
      dfs(u, d + 1, c + co[v][i], v)
    }
  }
  int operator()(int a, int b) { // lca between a and b
    if (dep[a] > dep[b]) { swap(a, b); }
    int gap = dep[b] - dep[a];
    for (int i = l-1; i >= 0; --i) {
      int len = 1<<i;
      if (gap >= len) {
        gap -= len;
        b = par[b][i];
      }
    }
    if (a == b) { return a; }
    for (int i = l-1; i>=0; --i) {
      int na = par[a][i];
      int nb = par[b][i];
      if (na != nb) {
        a = na;
        b = nb;
      }
    }
    return par[a][0];
  }
  int length(int a, int b) {
    int c = lca(a, b);
    return dep[a] + dep[b] - dep[c]*2;
  }
  int cost(int a, int b) {
    int c = lca(a, b);
    return costs[a] + costs[b] - costs[c]*2;
  }
}

struct Edge {
  int to, co, col;
  Edge(int to, int co, int col) : to(to), co(co), col(col) {}
}

vector< vector<Edge> > e;
vector<ll> ans;

struct Query {
  int col, qid, coeff;
  Query(int col, int qid, int coeff) : col(col), qid(qid), coeff(coeff) {}
}
vector< vector<Query> > qs;

int main(int argc, char** argv) {
  int N, Q;
  cin >> N >> Q;

  e.resize(N);
  ans.resize(Q);
  qs.resize(N);
  struct lca g(N);

  rep(i, N-1) {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    --a; --b;
    e[a].emblace_back(b, d, c);
    e[b].emblace_back(a, d, c);

    g.addedge(a, b, d);
  }
  g.init(0);

  rep(i, Q) {
    int x, y, a, b;
    cin >> x >> y >> a >> b;
    --a; --b;
    int c = g.lca(a, b);
    ans[i] = g.costs[a]+g.costs[b]-g.costs[c]*2;
    qs[a].push_back(x, i, 1);
    qs[b].push_back(x, i, 1);
    qs[c].push_back(x, i, -2);
  }
}
