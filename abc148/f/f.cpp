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

template<class T> void printvec(const vector<T>& v) {
  for (auto x : v) { cout << x << " "; }
  cout << endl;
}
template<class T> void printtree(const vector< vector<T> >& tree) {
  for (long long i = 0; i < tree.size(); ++i) {
    cout << i + 1 << ": "; printvec(tree[i]);
  }
}
template<class T, class U> void printmap(const map<T, U>& mp) {
  for (auto x : mp) { cout << x.first << "=>" << x.second << endl; }
}

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }

#define rep(i, n) for(ll i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()
#define fr first
#define sc second
#define mp make_pair
#define pb push_back

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

ll n; // the number of nodes
vector<ll> dist; // distance from s
vector<vector<ll>> g; // adjacency list

void dfs(int v, int d, int p) {
  dist[v] = d;
  for (int nv : g[v]) {
    if (nv == p) { continue; } // skip parent
    dfs(nv, d+1, v);
  }
}

vector<ll> calcDist(int s) {
  dist.assign(n, 0); // reset
  dfs(s, 0, -1);
  return dist;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll u, v;
  cin >> n >> u >> v;
  --u; --v; // 0-indexed
  g.resize(n);

  rep(i, n-1) {
    ll a, b;
    cin >> a >> b;
    --a; --b; // 0-indexed
    g[a].push_back(b);
    g[b].push_back(a);
  }

  vector<ll> dist_t = calcDist(u); // takahashi
  vector<ll> dist_a = calcDist(v); // aoki
  // Here, we want to find maximum distance where dist_t[i] < dist_a[i]
  ll ans = 0;
  rep(i, n) {
    if (dist_t[i] < dist_a[i]) {
      ans = max(ans, dist_a[i] - 1);
    }
  }
  cout << ans << endl;
}
