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

int dx[] = { 1, -1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

vector<ll> to[200010];
vector<ll> ans;

void dfs(int v, int p) {
  for (int u : to[v]) {
    // if (u == p) { continue; }
    ans[u] += ans[v];
    dfs(u, v);
  }
}

int main(int argc, char** argv) {
  int N, Q;
  cin >> N >> Q;
  rep(i, N-1) {
    ll a, b;
    cin >> a >> b;
    --a; --b;
    to[a].push_back(b);
    // to[b].push_back(a);
  }
  ans.resize(N);
  rep(i, Q) {
    ll p, x;
    cin >> p >> x;
    --p;
    ans[p] += x;
  }
  dfs(0, -1);

  rep(i, N) {
    cout << ans[i];
    if (i != N-1) {
      cout << " ";
    }
  }
  cout << endl;
}
