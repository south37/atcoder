#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

#define INF INT64_MAX

struct edge {
  int from;
  int to;
  int cost;
};

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
    e.cost = - (e.cost - P);
    edges.push_back(e);
  }

  // For Debug
  // rep(i, M) {
  //   cout << edges[i].from << ", " << edges[i].to << ", " << edges[i].cost << endl;
  // }

  bool negative_existence = false;
  vector<int64_t> d(N + 1, INF);  // d[0] is dummy. Initialize with INF.
  d[1] = 0;  // Set 0 to start point.
  rep(i, N) {
    rep(j, M) {
      edge e = edges[j];
      if ((d[e.from] < INF) && (d[e.to] > d[e.from] + e.cost)) {  // If d[e.from] == INF, it can't be reached.
        d[e.to] = d[e.from] + e.cost;

        // For Deubg
        // cout << i << " loop: " << endl;
        // rep(i, N) {
        //   if (d[i + 1] == INF) {
        //     cout << "INF ";
        //   } else {
        //     cout << d[i + 1] << " ";
        //   }
        // }
        // cout << endl;

        if ((i == N - 1) && (e.to == N)) { // Check loop count. if reached to N times, it means the existence of loop.
          negative_existence = true;
          break;
        }
      }
    }
  }

  if (negative_existence) {
    cout << -1 << endl;
  } else if (d[N] == INF) { // Goal can't be reached.
    cout << -1 << endl;
  } else {
    if (d[N] > 0) {
      cout << 0 << endl;
    } else {
      cout << -d[N] << endl;
    }
  }

  return 0;
}
