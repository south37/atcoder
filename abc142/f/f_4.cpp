// From youtube - atcoder abc142 f
// https://www.youtube.com/watch?v=l4pTJy13sbM

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
vector<int> state;
vector<int> vs;

bool dfs(int v) {
  if (state[v] == 1) { // intermediate
    vs.erase(vs.begin(), find(all(vs), v)); // remove all elements before v.
    return true;
  }
  if (state[v] == -1) { // Already visited
    return false;
  }
  // state[v] == 0
  vs.push_back(v);
  state[v] = 1;
  for (int u : graph[v]) {
    if (dfs(u)) { return true; }
  }
  state[v] = -1;
  vs.pop_back();
  return false;
}

int N, M;

void solve() {
  vector<int> nxt(N), visited(N), erased(N, 1);
  rep(i, vs.size()) {
    int v = vs[i];
    int u = vs[(i+1)%vs.size()];
    nxt[v] = u;
    erased[v] = 0;
  }
  int v = vs[0];
  while (!visited[v]) {
    for (int u : graph[v]) {
      if (erased[u]) { continue; }
      int nv = v;
      while (nxt[nv] != u) {
        nv = nxt[nv];
        erased[nv] = 1;
      }
      nxt[v] = u;
    }
    visited[v] = 1;
    v = nxt[v];
  }

  vector<int> ans;
  int sv = v;
  while (true) {
    ans.push_back(v);
    v = nxt[v];
    if (v == sv) { break; }
  }
  cout << ans.size() << endl;
  for (auto v : ans) {
    cout << v + 1 << endl;
  }
}

int main(int argc, char** argv) {
  cin >> N >> M;
  graph.resize(N);
  rep(i, M) {
    int A, B;
    cin >> A >> B;
    --A; --B; // 0-indexed
    graph[A].push_back(B);
  }

  state.resize(N);
  rep(i, N) {
    if (!state[i]) {
      if (dfs(i)) {
        // for (int v : vs) { cout << v << endl; }
        solve();
        return 0;
      }
    }
  }

  cout << -1 << endl;
}
