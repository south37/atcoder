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
#define sz(x) (ll)(x).size()
#define fr first
#define sc second
#define mp make_pair
#define pb push_back
#define eb emplace_back

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;
typedef vector<ll> vl;
typedef vector<P> vp;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

vector<vector<ll>> g;

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n,m;
  cin >> n >> m;
  g.resize(n);
  rep(i,m) {
    ll a,b;
    cin >> a >> b;
    --a; --b;
    g[a].push_back(b);
    g[b].push_back(a);
  }

  vector<int> dp(n, -1); // source
  // Do bfs
  queue<int> q;
  q.push(0);
  dp[0] = INF; // set sentinel
  while (!q.empty()) {
    int v = q.front(); q.pop();
    for (int u : g[v]) {
      if (dp[u] == -1) {
        dp[u] = v; // source if v.
        q.push(u);
      }
    }
  }

  // Here, all travere is completed.
  bool ok = true;
  rep(i,n) {
    if (dp[i] == -1) { // unvisited
      ok = false;
      break;
    }
  }
  if (!ok) {
    cout << "No" << endl;
    return 0;
  }

  cout << "Yes" << endl;
  for (int i = 1; i < n; ++i) {
    cout << dp[i]+1 << endl; // 1-indexed
  }
}
