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

const ll INF = 1e15;
const ll MOD = 1000000007;  // 1e9 + 7

struct edge {
  ll from;
  ll to;
  ll cost;
  ll time;
};

ll n, m;
vector<vector<ll>> dp; // min cost
vector<vector<ll>> cnt; // count
vector<vector<edge>> g;

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  cin >> n >> m;
  dp.assign(1ll<<n, vector<ll>(n, INF));
  cnt.assign(1ll<<n, vector<ll>(n));
  g.resize(n);

  rep(iter,m) {
    ll u, v, d, time;
    cin >> u >> v >> d >> time;
    --u; --v;
    g[u].push_back({ u, v, d, time });
    g[v].push_back({ v, u, d, time });
  }

  dp[0][0] = 0;
  cnt[0][0] = 1;
  rep(i,1ll<<n) { // bit state
    rep(v,n) { // from vertex v
      // Here, consider (i,v) to other
      if (dp[i][v] == INF) { continue; } // not updated
      for (edge& e : g[v]) {
        if (!(i&(1ll<<e.to))) { // e.to is not reached
          if (dp[i][v] + e.cost <= e.time) { // time is ok
            ll nex = i|(1ll<<e.to);
            if (dp[nex][e.to] == dp[i][v] + e.cost) { // same cost
              cnt[nex][e.to] += cnt[i][v];
            } else if (dp[nex][e.to] > dp[i][v] + e.cost) { // lower cost
              dp[nex][e.to] = dp[i][v] + e.cost;
              cnt[nex][e.to] = cnt[i][v];
            }
          }
        }
      }
    }
  }
  // printtree(dp);

  ll ans = dp[(1ll<<n)-1][0];
  if (ans != INF) {
    cout << ans << " " << cnt[(1ll<<n)-1][0] << endl;
  } else {
    cout << "IMPOSSIBLE" << endl;
  }
}
