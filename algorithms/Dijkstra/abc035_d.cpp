// ABC035-D. https://abc035.contest.atcoder.jp/tasks/abc035_d

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <unordered_map>

using namespace std;

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

typedef long long ll;

const ll INF = 1e12;

struct edge {
  int from;
  int to;
  int cost;
  edge(int from, int to, int cost) : from(from), to(to), cost(cost) {}
};
vector<vector<edge>> g;
vector<vector<edge>> revG;

typedef pair<ll, ll> P;  // first is the sortest distance, the second is vertex number.

int main(int argc, char** argv) {
  int n, m;
  ll T;
  cin >> n >> m >> T;
  vector<int> a(n);
  rep(i, n) {
    cin >> a[i];
  }
  g.resize(n);
  revG.resize(n);
  rep(i, m) {
    ll u, v, cost;
    cin >> u >> v >> cost;
    --u; --v;
    edge e(u, v, cost);
    g[u].push_back(e);
    revG[v].push_back(e);
  }

  // Dijkstra
  // Calculate the shortest path from 0 with Dijkstra.
  vector<ll> d(n, INF);
  d[0] = 0;
  priority_queue<P, vector<P>, greater<P> > q;
  q.push(P(0, 0));

  while (!q.empty()) {
    P p = q.top(); q.pop();
    int v = p.second;
    if (d[v] < p.first) { continue; }  // Already updated.
    for (auto e : g[v]) {
      if (d[e.to] > d[v] + e.cost) {
        d[e.to] = d[v] + e.cost;
        q.push(P(d[e.to], e.to));
      }
    }
  }

  // Dijkstra
  // Calculate the shortest path to 0 with Dijkstra.
  vector<ll> revD(n, INF);
  revD[0] = 0;
  priority_queue<P, vector<P>, greater<P> > revQ;
  revQ.push(P(0, 0));

  while (!revQ.empty()) {
    P p = revQ.top(); revQ.pop();
    int v = p.second;
    if (revD[v] < p.first) { continue; }  // Already updated.
    for (auto e : revG[v]) {
      if (revD[e.from] > revD[v] + e.cost) {
        revD[e.from] = revD[v] + e.cost;
        revQ.push(P(revD[e.from], e.from));
      }
    }
  }

  ll ans = -1;
  rep(i, n) {
    ll score = a[i] * (T - d[i] - revD[i]);
    if (ans < score) {
      ans = score;
    }
  }
  cout << ans << endl;

  // For Debug
  // cout << "d[]" << endl;
  // rep(i, N) {
  //   cout << d[i] << " ";
  // }
  // cout << endl;

  // For Debug
  // cout << "revD[]" << endl;
  // rep(i, N) {
  //   cout << revD[i] << " ";
  // }
  // cout << endl;
}
