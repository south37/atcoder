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

const ll MOD = 1000000007;  // 1e9 + 7

// Dinic's algorithm.
// from https://qiita.com/drken/items/e805e3f514acceb87602

typedef int FLOW;       // Type of flow. int here.
const int MAX_V = 100010;  // Maximum number of nodes in a graph.
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

// Set cycle numbers to each nodes. Return the "total number of cycles" and
// "indices of cycles".
// e.g. If res[i] = j, then i is included in cycle j.
pair< int, vector<int> > cmp(vector<int> p){
  int n = p.size(), s = 0;
  vector<int> res(n, -1);

  rep(i, n) {
    if (res[i] == -1) {
      int x = i;
      do {
        res[x] = s;
        x = p[x];
      } while (x != i);
      ++s;
    }
  }

  return make_pair(s, res);
}

int main(int argc, char** argv) {
  int N;
  cin >> N;
  vector<int> P(N);
  vector<int> Q(N);
  rep(i, N) {
    cin >> P[i];
  }
  rep(i, N) {
    cin >> Q[i];
  }

  int l = 0, r = 0;
  vector<int> a, b;
  tie(l, a) = cmp(P);
  tie(r, b) = cmp(Q);

  int ans = N;
  int V = 1 + l + r + 1;
  Graph g(V);
  rep(i, N) {
    if (i == P[i] && i == Q[i]) {
      --ans;
    } else if (i == P[i]) {
      g.addedge(1 + l + b[i], 1 + l + r, 1);
    } else if (i == Q[i]) {
      g.addedge(0, 1 + a[i], 1);
    } else {
      g.addedge(1 + l + b[i], 1 + a[i], 1);
      if (P[i] == Q[i]) {
        g.addedge(1 + a[i], 1 + l + b[i], 1);
      }
    }
  }
  int f = Dinic(g, 0, V - 1);
  ans -= f;
  cout << ans << endl;
}
