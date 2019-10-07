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
  rep(i, N) {
    for (auto x : tree[i]) {
      cout << x << ",";
    }
    cout << endl;
  }

  // Double-Sweep for calculating the diameter of a tree.
  // cf. https://www.slideshare.net/chokudai/arc022 C
  // dfs(0, -1);  // At first, start dfs from a random position.
  // dst[r] = 0;
  // dfs(r, -1);  // Next, start dfs from the farthest position.
  // int diameter = dst[r];
}
