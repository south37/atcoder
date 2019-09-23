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

const ll MOD = 1000000007;  // 1e9 + 7

// Dinic's algorithm.
// from https://qiita.com/drken/items/e805e3f514acceb87602

typedef ll FLOW;       // Type of flow. int here.
const int MAX_V = 105;  // Maximum number of nodes in a graph.
const FLOW INF = 1e15;

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
  int N;
  cin >> N;
  vector<ll> A(N);
  rep(i, N) {
    cin >> A[i];
  }

  Graph g(N + 2); // s(0), N vertices, t(N+1)
  // We treat crash as 0, reserve as 1.
  // If a[i] is crashed, then a[i*2], a[i*3].. must be crashed. so we treat a[i] -> a[i*j] (j>=2) as INF.
  // Above example is 1-indexed case. If 0-indexed, then we should consider a[(i+1)*j-1].
  rep(i, N) {
    if (A[i] > 0) { // Should not be crashed. So crash(0) is cost. So add edge v-t. (v is 0)
      g.addedge(i + 1, N + 1, A[i]);
    } else { // Should crash. So no-crash(1) is cost. So add s-v (v is 1).
      g.addedge(0, i + 1, - A[i]);
    }

    for (int j = 2; (i + 1) * j - 1 < N; ++j) { // i is 0-indexed, so calculate (i + 1) * j - 1
      int k = (i + 1) * j - 1;

      // Add edge from i (i+1) to k (k + 1).
      g.addedge(i + 1, k + 1, INF);
    }
  }

  ll cost = Dinic(g, 0, N + 1);

  ll m = 0; // Maximum base.
  rep(i, N) {
    m += max(0LL, A[i]);
  }
  cout << m - cost << endl;
}
