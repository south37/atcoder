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

struct edge {
  ll from;
  ll to;
  ll cost;
};

ll n, E;
vector<vector<edge>> g;
// dp[i][j] .. i is state bit, j is last element. Total number when start from (i,j).
vector<vector<ll>> dp;

// state .. bit representation, v .. last reached
ll rec(ll state, ll v) {
  if (dp[state][v] < INF) { return dp[state][v]; }
  if ((state == (1ll<<n)-1) && v == 0) { // returned to 0.
    return dp[state][v] = 0;
  }

  bool found = false;
  for (edge& e : g[v]) {
    if ((state&(1ll<<e.to)) == 0) { // e.to is not reached yet
      ll now = rec(state|(1ll<<e.to), e.to);
      if (now >= 0) {
        found = true;
        chmin(dp[state][v], now + e.cost);
      }
    }
  }
  if (!found) { return dp[state][v] = -1; }
  return dp[state][v];
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  cin >> n >> E;
  g.resize(n);
  dp.assign(1ll<<n, vector<ll>(n, INF));

  rep(i, E) {
    ll s, t, d;
    cin >> s >> t >> d;
    g[s].push_back({ s, t, d });
  }

  ll ans = rec(0, 0); // start from 0.
  if (ans >= 0) {
    cout << ans << endl;
  } else { // invalid
    cout << -1 << endl;
  }
}
