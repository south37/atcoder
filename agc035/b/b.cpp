#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string.h>

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

class UnionFind {
public:
  UnionFind(int size) : par(size, -1) {}

  bool same(int x, int y) {
    return root(x) == root(y);
  }
  void unite(int x, int y) {
    x = root(x); y = root(y);
    if (x == y) return;
    if (x > y) { swap(x, y); }
    // here, x < y
    par[y] = x;
  }
  int root(int x) {
    if (par[x] < 0) {
      return x;
    } else {
      return par[x] = root(par[x]);
    }
  }

private:
  vector<int> par;
};

vector<int> cnt;
vector< vector<int> > tree;
vector<P> ans;

void dfs(int now, int p) {
  for (int x : tree[now]) {
    if (x != p) {
      dfs(x, now);
    }
  }

  if (now == 0) { return; } // Skip root

  if (cnt[now] % 2 == 0) { // even
    ans.push_back({ p + 1, now + 1 });
    ++cnt[p];
  } else { // odd
    ans.push_back({ now + 1, p + 1 });
    ++cnt[now];
  }

}

int main(int argc, char** argv) {
  int N, M;
  cin >> N >> M;
  if (M % 2 == 1) {
    cout << -1 << endl;
    return 0;
  }

  cnt.resize(N);
  tree.resize(N);

  UnionFind un(N);
  rep(i, M) {
    int a, b;
    cin >> a >> b;
    --a; --b;
    if (un.same(a, b)) {
      ans.push_back({ a + 1, b + 1 });
      ++cnt[a];
    } else {
      un.unite(a, b);
      tree[a].push_back(b);
      tree[b].push_back(a);
    }
  }

  dfs(0, -1);
  for (auto e : ans) {
    cout << e.first << " " << e.second << endl;
  }
}
