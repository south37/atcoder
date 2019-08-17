#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

#define INF 123456789

struct edge {
  int from;
  int to;
  int cost;
};

vector<int> to_from[2505];
vector<int> from_of_to[2505];
bool reachable_from_s[2505];
bool reachable_to_g[2505];
bool reachable[2505];

void dfsFromS(int v) {
  if (reachable_from_s[v]) { return; } // already reached.

  reachable_from_s[v] = true;
  for (int u : to_from[v]) {
    dfsFromS(u);
  }
}

void dfsFromG(int v) {
  if (reachable_to_g[v]) { return; } // already reached.

  reachable_to_g[v] = true;
  for (int u : from_of_to[v]) {
    dfsFromG(u);
  }
}

int main(int argc, char** argv) {
  // N .. vertex
  // M .. edge
  // P .. cost offset
  int N, M, P;
  cin >> N >> M >> P;
  vector<edge> edges;
  rep(i, M) {
    edge e;
    cin >> e.from >> e.to >> e.cost;
    --e.from; // Convert index from [1, N] to [0, N-1].
    --e.to;   // Convert index from [1, N] to [0, N-1].
    e.cost = - (e.cost - P);
    edges.push_back(e);
    to_from[e.from].push_back(e.to);
    from_of_to[e.to].push_back(e.from);
  }

  // For Debug
  // rep(i, M) {
  //   cout << edges[i].from << ", " << edges[i].to << ", " << edges[i].cost << endl;
  // }

  dfsFromS(0);  // For initialization of reachable_from_s
  dfsFromG(N - 1);  // For initialization of reachable_to_g
  rep(i, N) {  // For initialization of reachable
    reachable[i] = reachable_from_s[i] && reachable_to_g[i];
  }

  // NOTE: We focus only reachable vetices.

  bool negative_existence = false;
  vector<int64_t> d(N, INF);  // Initialize with INF.
  d[0] = 0;  // Set 0 to start point.
  rep(i, N) {
    rep(j, M) {
      edge e = edges[j];
      if (d[e.to] > d[e.from] + e.cost) {
        if (!reachable[e.from]) { continue; }
        if (!reachable[e.to]) { continue; }

        d[e.to] = d[e.from] + e.cost;

        // For Deubg
        // cout << i << " loop: " << endl;
        // rep(i, N) {
        //   if (d[i] == INF) {
        //     cout << "INF ";
        //   } else {
        //     cout << d[i] << " ";
        //   }
        // }
        // cout << endl;

        if (i == N - 1) { // Check loop count. if reached to N times, it means the existence of loop.
          negative_existence = true;
          break;
        }
      }
    }
  }

  if (negative_existence) {
    cout << -1 << endl;
  } else if (d[N - 1] == INF) { // Goal can't be reached.
    cout << -1 << endl;
  } else {
    int r = -d[N - 1];
    cout << max(0, r) << endl;
  }

  return 0;
}
