// Problem: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A&lang=jp
// https://qiita.com/drken/items/2f56925972c1d34e05d8
// https://qiita.com/drken/items/e805e3f514acceb87602

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string.h>

using namespace std;

#define COUT(x) cout << #x << " = " << (x) << " (L" << __LINE__ << ")" << endl

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

int dx[] = { 1, -1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

int gcd(int a, int b) {
  if (a < b) { swap(a, b); }
  if (b == 0) { return a; }
  return gcd(b, a % b);
}

bool prime(int n) {
  for (int i = 2; i <= sqrt(n); ++i) {
    if (n % i == 0) { return false; }
  }
  return n != 1;
}

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }

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

const int COM_MAX = 500010;
ll fac[COM_MAX], facinv[COM_MAX], inv[COM_MAX];
void COMinit() {
  fac[0] = fac[1] = 1;
  facinv[0] = facinv[1] = 1;
  inv[1] = 1;
  for(int i = 2; i < COM_MAX; ++i) {
    fac[i] = fac[i-1] * i % MOD;
    inv[i] = MOD - inv[MOD%i] * (MOD / i) % MOD;
    facinv[i] = facinv[i-1] * inv[i] % MOD;
  }
}

ll COM(ll n, ll k) {
  return (fac[n] * facinv[k] % MOD) * facinv[n-k] % MOD;
}

ll PERM(ll n, ll k) {
  return (fac[n] * facinv[k] % MOD);
}

// Dinic's algorithm.
// from https://qiita.com/drken/items/e805e3f514acceb87602

typedef int FLOW;       // Type of flow. int here.
const int MAX_V = 100;  // Maximum number of nodes in a graph.
const FLOW INF = 1e9;

struct Edge {
  int rev, from, to;
  FLOW cap, icap; // icap: initial cap

  Edge(int r, int f, int t, FLOW c) : rev(r), from(f), to(t), cap(c), icap(c) {}

  friend ostream& operator << (ostream& s, const Edge& E) {
    if (E.cap > 0) {
      return s << E.from << "->" << E.to << '(' << E.cap << ')';
    } else {
      return s;
    }
  }
};

class Graph {
public:
  Graph(int n = 0) : V(n) {
    rep(i, MAX_V) { list[i].clear(); }
  }

  void init(int n = 0) {
    V = n;
    rep(i, MAX_V) { list[i].clear(); }
  }

  void resize(int n = 0) { V = n; }

  void reset() {
    rep(i, V) {
      rep(j, list[i].size()) {
        list[i][j].cap = list[i][j].icap;
      }
    }
  }

  inline vector<Edge>& operator [] (int i) {
    return list[i];
  }

  Edge &redge(Edge e) {
    if (e.from != e.to) {
      return list[e.to][e.rev];
    } else {
      return list[e.to][e.rev + 1];
    }
  }

  void addedge(int from, int to, FLOW cap) {
    list[from].push_back(Edge((int)list[to].size(), from, to, cap));
    list[to].push_back(Edge((int)list[from].size() - 1, to, from, 0));
  }

private:
  int V;
  vector<Edge> list[MAX_V];
};

static int level[MAX_V];
static int iter[MAX_V];

void dibfs(Graph &G, int s) {
  rep(i, MAX_V) { level[i] = -1; }
  level[s] = 0;
  queue<int> que;
  que.push(s);
  while (!que.empty()) {
    int v = que.front();
    que.pop();
    rep(i, G[v].size()) {
      Edge &e = G[v][i];
      if (level[e.to] < 0 && e.cap > 0) {
        level[e.to] = level[v] + 1;
        que.push(e.to);
      }
    }
  }
}

FLOW didfs(Graph &G, int v, int t, FLOW f) {
  if (v == t) { return f; }

  for (int &i = iter[v]; i < G[v].size(); ++i) {
    Edge &e = G[v][i], &re = G.redge(e);
    if (level[v] < level[e.to] && e.cap > 0) {
      FLOW d = didfs(G, e.to, t, min(f, e.cap));
      if (d > 0) {
        e.cap -= d;
        re.cap += d;
        return d;
      }
    }
  }
  return 0;
}

// Main function for calculatig maximum flow
FLOW Dinic(Graph &G, int s, int t) {
  FLOW res = 0;
  while (true) {
    dibfs(G, s);
    if (level[t] < 0) { return res; }
    memset(iter, 0, sizeof(iter));
    FLOW flow;
    while ((flow = didfs(G, s, t, INF)) > 0) {
      res += flow;
    }
  }
}

int main(int argc, char** argv) {
  int V, E;
  cin >> V >> E;
  Graph g(V);
  rep(i, E) {
    int u, v, c;
    cin >> u >> v >> c;
    g.addedge(u, v, c);
  }

  int r = Dinic(g, 0, V - 1);
  cout << r << endl;
}
