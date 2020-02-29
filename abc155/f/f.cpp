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

vector<vector<P>> g;
vector<bool> visited;
vector<ll> ans;
vector<ll> x; // the value of each vettex.

int dfs(int v) {
  int res = x[v];
  for (auto e : g[v]) {
    int nv = e.first;
    if (visited[nv]) { continue; }
    visited[nv] = true;
    int r = dfs(nv);
    if (r) { // if r == 1, we must use this edge
      ans.push_back(e.second);
      res ^= r;
    }
  }
  return res;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n, m;
  cin >> n >> m;
  g.resize(n+1);
  visited.resize(n+1);
  x.resize(n+1);

  vector<P> a(n); // the pair of [pos, 0 or 1]
  rep(i, n) {
    cin >> a[i].first >> a[i].second;
  }
  sort(all(a));
  x[0] = a[0].second; // same with 0^a[0].second
  rep(i, n-1) {
    x[i+1] = a[i].second ^ a[i+1].second;
  }
  x[n] = a[n-1].second; // same with a[n-1].second^0
  rep(i, m) {
    ll l, r;
    cin >> l >> r;
    ll li = lower_bound(all(a), mp(l, 0ll)) - a.begin();
    ll ri = upper_bound(all(a), mp(r, 1ll)) - a.begin();
    g[li].emplace_back(ri, i);
    g[ri].emplace_back(li, i);
  }

  // Check each connected components in graph
  rep(i, n+1) {
    if (visited[i]) { continue; }
    visited[i] = true;
    if (dfs(i)) { // if 1, we can not make all nodes 0
      cout << -1 << endl;
      return 0;
    }
  }
  sort(all(ans));
  cout << ans.size() << endl;
  rep(i, ans.size()) {
    cout << ans[i] + 1;
    if (i < ans.size()-1) {
      cout << " ";
    }
  }
  cout << endl;

}
