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
  ll N, M;
  cin >> N >> M;
  vector<P> pairs;
  rep(i, M) {
    ll A, B;
    cin >> A >> B;
    --A; --B;
    pairs.emplace_back(A, B);
  }
  reverse(all(pairs));
  vector<ll> ans;
  UnionFind tree(N);
  ll cost = N * (N-1) / 2; // The initial cost. This is the final state.
  ans.push_back(cost);

  rep(i, M-1) {
    P p = pairs[i];

    // For Debug
    // cout << p.first << ", " << p.second << ": " << tree.same(p.first, p.second) << endl;

    // Now, we unite p.first and p.second.
    // We want to calculate the diff.
    if (tree.same(p.first, p.second)) { // if already united, the cost does not change.
      ans.push_back(cost);
    } else {
      ll x = tree.root(p.first);
      ll y = tree.root(p.second);
      ll c1 = tree.count(x);
      ll c2 = tree.count(y);

      // For Debug
      // cout << x << ": " << c1 << ", " << y << ": " << c2 << endl;

      ll c = c1 + c2; // new size
      ll diff = c*(c-1)/2 - c1*(c1-1)/2 - c2*(c2-1)/2; // cost changes by diff.
      cost -= diff;
      ans.push_back(cost);

      tree.unite(p.first, p.second);
    }
  }

  reverse(all(ans));
  rep(i, M) {
    cout << ans[i] << endl;
  }
}
