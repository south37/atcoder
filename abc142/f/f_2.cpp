// Answer by drken1215
// cf. http://drken1215.hatenablog.com/entry/2019/09/29/012000

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

int main(int argc, char** argv) {
  int N, M;
  cin >> N >> M;
  graph.resize(N);
  rep(i, M) {
    int A, B;
    cin >> A >> B;
    --A; --B; // 0-indexed
    graph[A].push_back(B);
  }

  int shortest = INF;
  vector<int> res;
  rep(s, N) {
    vector<int> dist(N, -1);
    vector<int> prev(N, -1);
    queue<int> q;
    q.push(s);
    dist[s] = 0;
    while (!q.empty()) {
      auto v = q.front(); q.pop();
      for (auto nv : graph[v]) {
        if (dist[nv] == -1) {
          dist[nv] = dist[v] + 1;
          prev[nv] = v;
          q.push(nv);
        }
      }
    }
    rep(t, N) {
      if (t == s) { continue; } // t is not s
      if (dist[t] == -1) { continue; } // t is not reachable
      for (auto nt : graph[t]) {
        if (nt == s) {
          vector<int> tmp({s});
          int cur = t;
          while (cur != s) {
            tmp.push_back(cur);
            cur = prev[cur];
          }
          if (shortest > tmp.size()) {
            shortest = tmp.size();
            res = tmp;
          }
        }
      }
    }
  }

  if (shortest == INF) { // shortest is not updated. So, no cycle is found.
    cout << -1 << endl;
  } else {
    cout << res.size() << endl;
    for (auto v : res) {
      cout << v + 1 << endl; // shortest path
    }
  }
}
