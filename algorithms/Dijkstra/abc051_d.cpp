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

#define INF 123456789123

struct edge {
  int from;
  int to;
  int cost;
};

typedef pair<int64_t, int> P;  // first is the sortest distance, the second is vertex number.

int main(int argc, char** argv) {
  int N, M;
  int64_t T;
  cin >> N >> M >> T;
  vector<int> A(N);
  rep(i, N) {
    cin >> A[i];
  }
  vector< vector<edge> > G(N);
  vector< vector<edge> > revG(N);
  rep(i, M) {
    edge e;
    cin >> e.from >> e.to >> e.cost;
    --e.from;
    --e.to;
    G[e.from].push_back(e);
    revG[e.to].push_back(e);
  }

  // Calculate the shortest path from 0 with dijkstra.
  vector<int64_t> d(N, INF);
  d[0] = 0;
  priority_queue<P, vector<P>, greater<P> > q;
  q.push(P(0, 0));

  while (!q.empty()) {
    P p = q.top(); q.pop();
    int v = p.second;
    if (d[v] < p.first) { continue; }  // Already updated.
    for (auto e : G[v]) {
      if (d[e.to] > d[v] + e.cost) {
        d[e.to] = d[v] + e.cost;
        q.push(P(d[e.to], e.to));
      }
    }
  }

  // Calculate the shortest path to 0 with dijkstra.
  vector<int64_t> revD(N, INF);
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

  int64_t ans = -1;
  rep(i, N) {
    int64_t score = A[i] * (T - d[i] - revD[i]);
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
