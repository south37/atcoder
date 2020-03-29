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

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  cout << setprecision(10) << fixed;

  ll n, m;
  cin >> n >> m;
  vector<vector<ll>> g(n);
  rep(i, m) {
    int s, t;
    cin >> s >> t;
    --s; --t; // 0-indexed
    g[s].push_back(t);
  }

  vector<double> dp(n); // dp[i] .. expected valud from i.
  // dp[n-1] = 0;
  for (int v = n-2; v >= 0; --v) {
    double now = 0;
    for (int u : g[v]) {
      now += dp[u];
    }
    now /= g[v].size();
    now += 1; // one-hop
    dp[v] = now;
  }

  double ans = dp[0];
  for (int nv = 0; nv < n-1; ++nv) {
    if (g[nv].size() == 1) { continue; } // skip 1-degree
    int nu = g[nv][0];
    for (int u : g[nv]) {
      if (dp[u] > dp[nu]) { nu = u; }
    }
    // Here, nu is the maximum dp[nu]

    double nowAns;
    {
      for (int v = n-2; v >= 0; --v) {
        double now = 0;
        for (int u : g[v]) {
          if (v == nv && u == nu) { continue; } // skip removed edge
          now += dp[u];
        }
        int deg = g[v].size();
        if (v == nv) { --deg; }
        now /= deg;
        now += 1; // one-hop
        dp[v] = now;
      }
      nowAns = dp[0];
    }
    ans = min(ans, nowAns);
  }
  cout << ans << endl;
}
