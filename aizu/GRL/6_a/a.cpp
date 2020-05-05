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

const ll MOD = 1000000007;  // 1e9 + 7

// Dinic's algorithm.

typedef ll FLOW;       // Type of flow. int here.
const ll MAX_V = 100;  // Maximum number of nodes in a graph.
const FLOW INF = 1e9;

struct Edge {
  ll rev, from, to;
  FLOW cap, icap; // icap: initial cap

  Edge(ll r, ll f, ll t, FLOW c) : rev(r), from(f), to(t), cap(c), icap(c) {}

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
  Graph(ll n = 0) : V(n) {
    rep(i, MAX_V) { list[i].clear(); }
  }

  void init(ll n = 0) {
    V = n;
    rep(i, MAX_V) { list[i].clear(); }
  }

  void resize(ll n = 0) { V = n; }

  void reset() {
    rep(i, V) {
      rep(j, list[i].size()) {
        list[i][j].cap = list[i][j].icap;
      }
    }
  }

  inline vector<Edge>& operator [] (ll i) {
    return list[i];
  }

  Edge &redge(Edge e) {
    if (e.from != e.to) {
      return list[e.to][e.rev];
    } else {
      return list[e.to][e.rev + 1];
    }
  }

  void addedge(ll from, ll to, FLOW cap) {
    list[from].push_back(Edge((ll)list[to].size(), from, to, cap));
    list[to].push_back(Edge((ll)list[from].size() - 1, to, from, 0));
  }

private:
  ll V;
  vector<Edge> list[MAX_V];
};

static ll level[MAX_V];
static ll iter[MAX_V];

void dibfs(Graph &G, ll s) {
  rep(i, MAX_V) { level[i] = -1; }
  level[s] = 0;
  queue<ll> que;
  que.push(s);
  while (!que.empty()) {
    ll v = que.front();
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

FLOW didfs(Graph &G, ll v, ll t, FLOW f) {
  if (v == t) { return f; }

  for (ll &i = iter[v]; i < G[v].size(); ++i) {
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

// int main(int argc, char** argv) {
//   int V, E;
//   cin >> V >> E;
//   Graph g(V);
//   rep(i, E) {
//     ll u, v, c;
//     cin >> u >> v >> c;
//     g.addedge(u, v, c);
//   }
//
//   ll r = Dinic(g, 0, V - 1);
//   cout << r << endl;
// }

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n, m;
  cin >> n >> m;
  Graph g(n);
  rep(i,m) {
    ll u,v,c;
    cin >> u >> v >> c;
    g.addedge(u,v,c);
  }

  ll r = Dinic(g,0,n-1);
  cout << r << endl;
}
