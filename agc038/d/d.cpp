#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>
#include <string.h>

using namespace std;

#define COUT(x) cout << #x << " = " << (x) << " (L" << __LINE__ << ")" << endl

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

int dx[] = { 1, -1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

class UnionFind {
public:
  UnionFind(int n) : par(n, -1), rnk(n, 0), _size(n) {}

  bool same(int x, int y) {
    return root(x) == root(y);
  }
  void unite(int x, int y) {
    x = root(x); y = root(y);
    if (x == y) return;

    --_size;

    if (rnk[x] < rnk[y]) {
      par[x] = y;
    } else {
      par[y] = x;
      if (rnk[x] == rnk[y]) { ++rnk[x]; }
    }
  }
  int root(int x) {
    if (par[x] < 0) {
      return x;
    } else {
      return par[x] = root(par[x]);
    }
  }
  int size() {
    return _size;
  }

private:
  vector<int> par;
  vector<int> rnk;
  int _size; // The number of connected components. Decreases by unite.
};

int main(int argc, char** argv) {
  ll N, M, Q;
  cin >> N >> M >> Q;

  UnionFind tree(N);
  vector<P> edges; // different edges.
  rep(i, Q) {
    ll A, B, C;
    cin >> A >> B >> C;
    if (C == 0) {
      tree.unite(A, B);
    } else {
      edges.emplace_back(A, B);
    }
  }

  if (M == N - 1) { // G must be a tree.
    if (edges.size() == 0) {
      cout << "Yes" << endl;
      return 0;
    } else {
      cout << "No" << endl;
      return 0;
    }
  }

  // Check different edges
  for (auto e : edges) {
    if (tree.same(e.first, e.second)) {
      cout << "No" << endl;
      return 0;
    }
  }

  ll K = tree.size(); // the number of connected components.

  // H must be lower than or equals to (N-K) + K*(K-1)/2 = N + K(K-3)/2
  if (M <= N + K * (K - 3) / 2) {
    cout << "Yes" << endl;
  } else {
    cout << "No" << endl;
  }
}
