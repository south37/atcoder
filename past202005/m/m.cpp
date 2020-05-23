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

vector<vector<ll>> g; // graph with weight 1

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n,m;
  cin >> n >> m;
  g.resize(n);
  rep(iter,m) {
    ll u,v;
    cin >> u >> v;
    --u; --v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  ll s;
  cin >> s;
  --s;

  ll k;
  cin >> k;
  vector<ll> t(k);
  rep(i,k) {
    cin >> t[i];
    --t[i];
  }

  // At first, calculate the distance of each t and s.
  vector<ll> vs; // target vertices
  rep(i,k) {
    vs.push_back(t[i]);
  }
  vs.push_back(s); // s is on vs[k].

  // printtree(g);
  // printvec(vs);

  vector<vector<ll>> dist(k+1, vector<ll>(k+1,INF)); // dist[i][j] .. distance of (i,j). i,j is index of vs.
  rep(i,vs.size()) {
    ll s = vs[i];
    // Start BFS from s.
    vector<ll> d2(n,INF);
    d2[s] = 0;
    queue<P> q;
    q.push(P(0,s));
    while (!q.empty()) {
      auto p = q.front(); q.pop();
      ll d = p.first;
      ll v = p.second;
      for (ll u : g[v]) {
        if (d2[u] > d+1) {
          d2[u] = d+1;
          q.push(P(d2[u],u));
        }
      }
    }

    rep(j,vs.size()) {
      if (j==i) { continue;}
      dist[i][j] = d2[vs[j]];
    }
  }

  // For Debug
  // printtree(dist);

  // Bit DP.
  // dp[i][j] .. bit state is i. last visited is k.
  // ll dp[1ll<<16][k];
  vector<vector<ll>> dp(1ll<<k,vector<ll>(k, INF));
  rep(i,k) {
    dp[1ll<<i][i] = dist[k][i];
  }
  // printtree(dp);

  rep(i,1ll<<k) {
    rep(j,k) { // current position
      if (!(i>>j&1)) { continue; } // j is not in i
      if (dp[i][j] == INF) { continue; } // dp[i][j] is not calculated now.
      rep(l,k) { // next position
        if (i>>l&1) { continue; } // l is not in i
        // Here, we move from j to l.
        chmin(dp[i|(1ll<<l)][l], dp[i][j] + dist[j][l]);
      }
    }
  }
  // printtree(dp);

  ll ans = INF;
  rep(i,k) {
    chmin(ans, dp[(1ll<<k)-1][i]);
  }
  cout << ans << endl;
}
