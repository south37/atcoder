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
  UnionFind(ll n) : par(n, -1), rnk(n, 0), cnt(n, 1), _size(n) {}

  bool same(ll x, ll y) {
    return root(x) == root(y);
  }
  void unite(ll x, ll y) {
    x = root(x); y = root(y);
    if (x == y) return;

    --_size;

    if (rnk[x] < rnk[y]) { swap(x, y); }
    par[y] = x;
    cnt[x] += cnt[y];
    if (rnk[x] == rnk[y]) { ++rnk[x]; }
  }
  ll root(ll x) {
    if (par[x] < 0) {
      return x;
    } else {
      return par[x] = root(par[x]);
    }
  }
  ll count(ll x) {
    return cnt[root(x)];
  }
  ll size() {
    return _size;
  }

private:
  vector<ll> par;
  vector<ll> rnk;
  vector<ll> cnt; // The number of vertices in each connected components.
  ll _size; // The number of connected components. Decreases by unite.
};

// int main(int argc, char** argv) {
//   ll N, M;
//   cin >> N >> M;
//   UnionFind tree(N);
//   rep(i, M) {
//     ll p, a, b;
//     cin >> p >> a >> b;
//     if (p == 0) { // Connect
//       tree.unite(a, b);
//     } else { // Judge
//       if (tree.same(a, b)) {
//         cout << "Yes" << endl;
//         cout << "size: " << tree.size() << endl;
//         cout << "count(" << a << "): " << tree.count(a) << endl;
//         cout << "count(" << b << "): " << tree.count(b) << endl;
//       } else {
//         cout << "No" << endl;
//         cout << "size: " << tree.size() << endl;
//         cout << "count(" << a << "): " << tree.count(a) << endl;
//         cout << "count(" << b << "): " << tree.count(b) << endl;
//       }
//     }
//   }
// }

int main(int argc, char** argv) {
  int N;
  cin >> N;
  vector<P> vertices(N);
  map<ll, vector<ll> > X; // stores the group of vertices with same x
  map<ll, vector<ll> > Y; // stores the group of vertices with same y
  rep(i, N) {
    int x, y;
    cin >> x >> y;
    vertices[i].first = x;
    vertices[i].second = y;
    X[x].push_back(i);
    Y[y].push_back(i);
  }
  // For Debug
  // cout << "X:" << endl;
  // for (auto e : X) {
  //   cout << e.first << ": ";
  //   for (auto i : e.second) {
  //     cout << i << ", ";
  //   }
  //   cout << endl;
  // }
  // cout << "Y:" << endl;
  // for (auto e : Y) {
  //   cout << e.first << ": ";
  //   for (auto i : e.second) {
  //     cout << i << ", ";
  //   }
  //   cout << endl;
  // }

  UnionFind tree(N);
  // Unite vertices in same X[i].
  for (auto e : X) {
    for (auto i : e.second) {
      if (i == 0) { continue; }
      tree.unite(e.second[0], i);
    }
  }
  // Unite vertices in same Y[i].
  for (auto e : Y) {
    for (auto i : e.second) {
      if (i == 0) { continue; }
      tree.unite(e.second[0], i);
    }
  }

  // Here, the target groups are conected components in tree.
  // The answer is the sum of (len(x) * len(y) - size(connected verteices))

  // We make 3 maps.
  // 1: (connected componet id) => len(x)
  // 2: (connected componet id) => len(y)
  // 3: (connected componet id) => size(vertices)
  map<int, set<int>> mp_x;
  map<int, set<int>> mp_y;
  rep(i, N) {
    int r = tree.root(i);
    int x = vertices[i].first;
    int y = vertices[i].second;
    mp_x[r].insert(x);
    mp_y[r].insert(y);
  }

  ll ans = 0;
  for (auto e : mp_x) {
    int r = e.first; // root id
    int len_x = e.second.size(); // len(x)
    int len_y = mp_y[r].size(); // len(y)
    int size_v = tree.count(r);
    ans += len_x * len_y - size_v;
  }

  cout << ans << endl;
}
