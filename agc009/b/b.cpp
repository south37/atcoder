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

#define rep(i, n) for(ll i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

vector< vector<ll> > tree;

ll dfs(ll p) {
  if (tree[p].size() == 0) {
    return 0;
  }

  vector<ll> d;
  for (auto u : tree[p]) {
    d.push_back(dfs(u));
  }
  sort(all(d));
  reverse(all(d));
  // cout << "d: ";
  // rep(i, d.size()) {
  //   cout << d[i] << " ";
  // }
  // cout << endl;

  ll res = 0;
  rep(i, d.size()) {
    ll c = d[i] + i + 1;
    if (res < c) {
      res = c;
    }
  }
  // cout << "res: " << res << endl;

  return res;
}

int main(int argc, char** argv) {
  ll N;
  cin >> N;
  tree.resize(N);
  for (int i = 1; i < N; ++i) {
    ll j;
    cin >> j;
    --j; // 0-indexed
    tree[j].push_back(i);
  }

  // For Debug
  // rep(i, N) {
  //   cout << i + 1 << ": ";
  //   for (auto j : tree[i]) {
  //     cout << j + 1 << " ";
  //   }
  //   cout << endl;
  // }

  cout << dfs(0) << endl;
}
