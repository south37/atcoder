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

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n, m;
  cin >> n >> m;
  set<P> pairs;
  rep(i,m) {
    ll a, b;
    cin >> a >> b;
    --a; --b;
    if (a > b) { swap(a,b); }
    pairs.insert(P(a,b));
    // pairs.insert(P(b,a));
  }

  ll n2 = n/2;
  // dp[s] .. s is stable set. true or false.
  vector<vector<bool>> dp(2);
  dp[0].assign(1ll<<n2, true);
  dp[1].assign(1ll<<(n-n2), true);
  for (auto& p : pairs) {
    if (p.first < n2 && p.second < n2) {
      dp[0][(1ll<<p.first)|(1ll<<p.second)] = false;
    }
  }
  for (auto& p : pairs) {
    if (n2 <= p.first && n2 <= p.second) {
      dp[1][(1ll<<(p.first-n2))|(1ll<<(p.second-n2))] = false;
    }
  }
  rep(i,1ll<<n2) {
    if (!dp[0][i]) {
      rep(j,n2) {
        if (!(i&(1ll<<j))) { // j is not in i
          dp[0][i|(1ll<<j)] = false;
        }
      }
    }
  }
  rep(i,1ll<<(n-n2)) {
    if (!dp[1][i]) {
      rep(j,(n-n2)) {
        if (!(i&(1ll<<j))) { // j is not in i
          dp[1][i|(1ll<<j)] = false;
        }
      }
    }
  }

  // dp1[i] .. set of vs in v2 which are not connected with i.
  vector<ll> dp1(1ll<<n2);
  dp1[0] = (1ll<<(n-n2))-1;
  rep(i,n2)rep(j,n-n2) {
    if (pairs.find(P(i,j+n2)) == pairs.end()) { // (i,j+n2) is not in pairs
      dp1[1ll<<i] |= 1ll<<j;
    }
  }
  rep(i,1ll<<(n-n2)) {
    rep(j,n-n2) {
      if (!(i&(1ll<<j))) { // j is not in i
        dp1[i|(1ll<<j)] = dp1[i]&dp1[1ll<<j];
      }
    }
  }
  // cout << "dp1: "; printvec(dp1);

  // dp2[i] .. max value in subset of i.
  vector<ll> dp2(1ll<<(n-n2));
  rep(i,1ll<<(n-n2)) {
    if (dp[1][i]) { // stable set
      dp2[i] = __builtin_popcountl(i);
    }
  }
  // cout << "dp2: "; printvec(dp2);
  rep(i,1ll<<(n-n2)) {
    rep(j,n-n2) {
      if (!(i&(1ll<<j))) { // j is not in i
        chmax(dp2[i|(1ll<<j)], dp2[i]);
      }
    }
  }
  // cout << "dp2: "; printvec(dp2);

  ll ans = 0;
  rep(i,1ll<<n2) {
    if (dp[0][i]) { // stable set
      ll j = dp1[i]; // set in v2.
      // cout << "i: " << i << endl;
      // cout << "j: " << j << endl;
      // cout << "dp2[j]: " << dp2[j] << endl;
      chmax(ans, __builtin_popcountl(i) + dp2[j]);
    }
  }
  cout << ans << endl;
}
