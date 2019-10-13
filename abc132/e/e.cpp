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

int main(int argc, char** argv) {
  ll N, M;
  cin >> N >> M;
  vector< vector<ll> > tree(3 * N); // We use 3 * N vertices.
  rep(i, M) {
    ll u, v;
    cin >> u >> v;
    --u; --v; // 0-indexed.
    // u -> v is treated as u0->v1, u1->v2, u2->v0.
    tree[u].push_back(v + N);
    tree[u + N].push_back(v + 2 * N);
    tree[u + 2 * N].push_back(v);
  }
  ll s, t;
  cin >> s >> t;
  --s; --t;

  // Dijkstra
  // Calculate the shortest path from s with Dijkstra.
  vector<ll> d(3 * N, INF);
  d[s] = 0;
  priority_queue<P, vector<P>, greater<P> > q;
  q.push(P(0, s));

  while (!q.empty()) {
    P p = q.top(); q.pop();
    ll v = p.second;
    if (d[v] < p.first) { continue; }  // Already updated.
    for (auto u : tree[v]) {
      if (d[u] > d[v] + 1) {
        d[u] = d[v] + 1;
        q.push(P(d[u], u));
      }
    }
  }

  if (d[t] == INF) { // can't reach
    cout << -1 << endl;
  } else {
    cout << d[t] / 3 << endl;
  }
}
