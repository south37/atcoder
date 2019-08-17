#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

struct edge {
  int from;
  int to;
  int cost;
};

int main(int argc, char** argv) {
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
  rep(i, M) {
    cout << edges[i].from << ", " << edges[i].to << ", " << edges[i].cost << endl;
  }

  // rep(i, N) {
  //   rep(j, M) {
  //   }
  // }

  return 0;
}
