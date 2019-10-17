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

class UnionFind {
public:
  UnionFind(int n) : par(n, -1), rnk(n, 0), cnt(n, 1), _size(n) {}

  bool same(int x, int y) {
    return root(x) == root(y);
  }
  void unite(int x, int y) {
    x = root(x); y = root(y);
    if (x == y) return;

    --_size;

    if (rnk[x] < rnk[y]) { swap(x, y); }
    par[y] = x;
    cnt[x] += cnt[y];
    if (rnk[x] == rnk[y]) { ++rnk[x]; }
  }
  int root(int x) {
    if (par[x] < 0) {
      return x;
    } else {
      return par[x] = root(par[x]);
    }
  }
  int count(int x) {
    return cnt[root(x)];
  }
  int size() {
    return _size;
  }

private:
  vector<int> par;
  vector<int> rnk;
  vector<int> cnt; // The number of vertices in each connected components.
  int _size; // The number of connected components. Decreases by unite.
};

int main(int argc, char** argv) {
  int N, M;
  cin >> N >> M;

  UnionFind tree(N);
  rep(i, M) {
    int X, Y, Z;
    cin >> X >> Y >> Z;
    --X; --Y; // 0-indexied.
    tree.unite(X, Y);
  }

  cout << tree.size() << endl;
}
