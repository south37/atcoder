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

vector< vector<int> > graph;
vector< vector<int> > revG; // reverse of graph.
int dist[1005]; // distance from s.

int dfs(int v, int s) { // v is current, s is start. returns the shortest cycle length of s -> s. If does not found, it returns INF.
  int res = INF;
  for (int u : graph[v]) {
    if (u == s) { // cycle found.
      return dist[v] + 1; // the length of cycle.
      // cout << "cycle found: " << u << "->" << s << endl;
    }
    dist[u] = dist[v] + 1;  // set the current distance
    // cout << v << "->" << u << endl;
    int d = dfs(u, s);
    if (d < res) { // shorter path is found.
      res = d;
    }
  }
  return res;
}

int main(int argc, char** argv) {
  int N, M;
  cin >> N >> M;
  graph.resize(N);
  revG.resize(N);
  rep(i, M) {
    int A, B;
    cin >> A >> B;
    --A; --B; // 0-indexed
    graph[A].push_back(B);
    revG[B].push_back(A);
  }
  // For Debug
  // rep(i, N) {
  //   for (auto x : graph[i]) {
  //     cout << i << "->" << x << endl;
  //   }
  // }

  int ans_s = -1; // answer start point.
  int ans = INF;
  rep(s, N) { // s: start point
    // cout << "start from " << s << endl;

    memset(dist, 0, sizeof(dist));
    dist[s] = 0;
    int candidate = dfs(s, s); // search the cycle from s -> s and returns the shortest path. If cycle does not found, it returns INF.
    if (candidate < ans) {
      ans = candidate;
      ans_s = s;
    }
  }

  if (ans == INF) { // any cycles do not exist
    cout << -1 << endl;
    return 0;
  }

  cout << ans << endl; // print the shortest length of cycle.

  // Now, path from ans_s is shortest. we have to find the path.
  // We use bfs to find the shortest cycle.
  vector<int> pre(N); // stores the previous point.
  rep(i, N) {
    pre[i] = -1; // initialized by -1.
  }
  queue<int> q;
  q.push(ans_s);
  while (!q.empty()) {
    if (pre[ans_s] >= 0) { break; } // pre[ans_s] is already calculated.

    int v = q.front(); q.pop();
    for (int u : graph[v]) {
      if (u == ans_s) {
        pre[ans_s] = v;
        break;
      }
      pre[u] = v;
      q.push(u);
    }
  }

  // For Debug
  // cout << "ans_s: " << ans_s << endl;
  // rep(i, N) {
  //   cout << pre[i] << "->" << i << endl;
  // }

  vector<int> v_path;
  v_path.push_back(ans_s);
  int v = pre[ans_s];
  // cout << ans_s << "<-";
  while (v != ans_s) {
    v_path.push_back(v);
    v = pre[v]; // change to prev.
    // cout << v << "<-";
  }
  // cout << endl;
  // int v = pre[ans_s];
  // int v2 = pre[v];
  // int v3 = pre[v2]; ...
  for (auto x : v_path) {
    cout << x + 1 << endl; // 1-indexed
  }
}
