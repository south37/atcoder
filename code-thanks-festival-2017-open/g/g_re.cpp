// ref. https://img.atcoder.jp/code-thanks-festival-2017-open/editorial.pdf

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

// dp[k][s] .. s is stable set. true or false.
bool dp[2][1<<20];
int dp1[1<<20], dp2[1<<20];
vector<int> g[40];

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  int n, m;
  cin >> n >> m;
  rep(i,m) {
    int a, b;
    cin >> a >> b;
    --a; --b;
    g[a].push_back(b);
    g[b].push_back(a);
  }

  int n1 = (n+1)/2, n2 = n-n1;
  fill(dp[0], dp[0]+(1<<n1), true);
  fill(dp[1], dp[1]+(1<<n2), true);
  rep(v,n1) {
    for (auto u : g[v]) {
      if (u < n1) {
        dp[0][(1<<u)|(1<<v)] = false;
      }
    }
  }
  for (ll v = n1; v < n; ++v) {
    for (auto u : g[v]) {
      if (u >= n1) {
        dp[1][(1<<(u-n1))|(1<<(v-n1))] = false;
      }
    }
  }
  rep(i,1<<n1) {
    if (!dp[0][i]) {
      rep(j,n1) {
        dp[0][i|(1<<j)] = false;
      }
    }
  }
  rep(i,1<<n2) {
    if (!dp[1][i]) {
      rep(j,n2) {
        dp[1][i|(1<<j)] = false;
      }
    }
  }

  // dp1[i] .. set of vs in v2 which are not connected with i.
  dp1[0] = (1<<n2)-1;
  rep(i,n1) {
    dp1[1<<i] = (1<<n2)-1;
    for (auto u : g[i]) { // loop for all u connected with i.
      if (u >= n1) {
        dp1[1<<i] ^= (1<<(u-n1));
      }
    }
  }
  rep(i,1<<n2) {
    rep(j,n2) {
      dp1[i|(1<<j)] = dp1[i]&dp1[1<<j];
    }
  }
  // cout << "dp1: "; printvec(dp1);

  // dp2[i] .. max value in subset of i.
  rep(i,1<<n2) {
    if (dp[1][i]) { // stable set
      dp2[i] = __builtin_popcountll(i);
    }
  }
  // cout << "dp2: "; printvec(dp2);
  rep(i,1<<n2) {
    rep(j,n2) {
      chmax(dp2[i|(1<<j)], dp2[i]);
    }
  }
  // cout << "dp2: "; printvec(dp2);

  int ans = 0;
  rep(i,1<<n1) {
    if (dp[0][i]) { // stable set
      ll j = dp1[i]; // set in v2.
      // cout << "i: " << i << endl;
      // cout << "j: " << j << endl;
      // cout << "dp2[j]: " << dp2[j] << endl;
      chmax(ans, __builtin_popcountll(i) + dp2[j]);
    }
  }
  cout << ans << endl;
}
