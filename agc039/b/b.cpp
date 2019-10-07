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

vector< vector<int> > tree;
vector<int> dst;  // distance
int r = 0;

void dfs(int now, int p) {
  for (auto x : tree[now]) {
    if (x == p) { continue; }
    dst[x] = dst[now] + 1;
    if (dst[x] > dst[r]) { r = x; }
    dfs(x, now);
  }
}

int main(int argc, char** argv) {
  int N;
  cin >> N;
  tree.resize(N);
  rep(i, N) {
    string S;
    cin >> S;
    rep(j, N) {
      if (j > i) { // consider only this case
        if (S[j] == '1') {
          tree[i].push_back(j);
          tree[j].push_back(i);
        }
      }
    }
  }

  // For Debug
  // rep(i, N) {
  //   for (auto x : tree[i]) {
  //     cout << x << ",";
  //   }
  //   cout << endl;
  // }

  ll ans = 0;

  // bfs from all points. The largest length is answer. If different distance is detected, then answer is -1 (odd cycle exists).
  rep(s, N) {
    vector<int> d(N, -1);
    queue<P> q; // A queue of pairs. A pair is (vertex, prev).
    d[s] = 0;
    q.emplace(s, -1); // start from s.
    while (!q.empty()) {
      P p = q.front(); q.pop();
      for (int u : tree[p.first]) {
        if (u == p.second) { continue; } // skip prev

        if (d[u] == -1) { // u is not visited
          d[u] = d[p.first] + 1;
          q.emplace(u, p.first);
          if (d[u] > ans) { ans = d[u]; } // ans is max distance
          continue;
        }

        // Here, d[u] is already calculated
        if ((d[u] != d[p.first] + 1) && (d[u] != d[p.first] - 1)) { // different distance!
          // For Debug
          // cout << "s: "<<s << endl;
          // cout << "d["<<u<<"]: "<<d[u]<<", d["<<p.first<<"]: "<<d[p.first] << endl;
          cout << -1 << endl;
          return 0;
        }
      }
    }
  }

  cout << ans + 1 << endl;
}
