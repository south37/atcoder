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

template<typename T>
struct lca {
  int n, root, l;
  vector< vector<int> > to;
  vector< vector<T> > co; // co[i][j] .. costs between i - to[i][j]
  vector<int> dep; // depth from root.
  vector<T> costs; // cumulative cost from root.
  vector< vector<int> > par; // par[i][j] .. i's anccestor. The distance from i is 2**j.

  lca(int n) : n(n), to(n), co(n), dep(n), costs(n) {
    l = 0;
    while ((1<<l) < n) { ++l; }
    par = vector< vector<int> >(n, vector<int>(l, -1));
  }
  void addedge(int a, int b, T c) {
    to[a].push_back(b);
    co[a].push_back(c);
    to[b].push_back(a);
    co[b].push_back(c);
  }
  void init(int _root) {
    root = _root;
    dfs(root);
    rep(i, l-1) {
      rep(v, n) {
        if (par[v][i] != -1) {
          par[v][i+1] = par[par[v][i]][i];
        }
      }
    }
  }
  void dfs(int v, int d = 0, T c = 0, int p = -1) {
    par[v][0] = p;
    dep[v] = d;
    costs[v] = c;
    rep(i, to[v].size()) {
      int u = to[v][i];
      if (u == p) { continue; }
      dfs(u, d + 1, c + co[v][i], v)
    }
  }
}

vector< vector<int> > tree;

int main(int argc, char** argv) {
  int N, Q;
  cin >> N >> Q;
  tree.resize(N);
  rep(i, N-1) {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    int
  }

  cout << n << endl;
}
