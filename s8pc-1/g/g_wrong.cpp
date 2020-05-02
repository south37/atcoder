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
vector<vector<P>> dp; // pair of <min cost, cnt>
vector<vector<edge>> g;

// state .. bit, v .. last visited vertex, cost .. current cost
P rec(ll state, ll v, ll cost) {
  if (dp[state][v].first != INF) {
    return dp[state][v];
  }
  if ((state == (1ll<<n)-1) && v == 0) { // reached to last
    return P(0,1);
  }

  bool found = false;
  for (edge& e : g[v]) {
    if (state&(1ll<<e.to)) { continue; } // already visited
    if (cost + e.cost > e.time) { continue; } // cost is too large
    P now = rec(state|(1ll<<e.to), e.to, cost+e.cost);
    if (now.first >= 0) { // valid
      found = true;
      if (dp[state][v].first == now.first + e.cost) { // same
        dp[state][v].second += now.second;;
      } else if (dp[state][v].first > now.first + e.cost) {
        dp[state][v] = P(now.first + e.cost, now.second);
      }
    }
  }
  if (!found) {
    return dp[state][v] = P(-1,0);
  }
  return dp[state][v];
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  cin >> n >> m;
  dp.assign(1ll<<n, vector<P>(n, P(INF,0)));
  g.resize(n);

  rep(iter,m) {
    ll u, v, d, time;
    cin >> u >> v >> d >> time;
    --u; --v;
    g[u].push_back({ u, v, d, time });
    g[v].push_back({ v, u, d, time });
  }

  P ans = rec(0,0,0);
  // printtree(dp);

  if (ans.first >= 0) {
    cout << ans.first << " " << ans.second << endl;
  } else {
    cout << "IMPOSSIBLE" << endl;
  }
}
