// ref. https://www.hamayanhamayan.com/entry/2019/01/12/154729

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

const ll MAX_S = 2e4 + 5; // maximum of s+w

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  vector<ll> w(n), s(n), v(n);
  rep(i, n) {
    cin >> w[i] >> s[i] >> v[i];
  }

  vector<ll> ord; // order
  rep(i, n) { ord.push_back(i); }
  sort(all(ord), [&](ll a, ll b) {
    return min(s[a], s[b]-w[a]) > min(s[b], s[a]-w[b]);
  });

  // dp[i][j] .. using [0, i), total amount is j.
  vector<vector<ll>> dp(n+1, vector<ll>(MAX_S));
  rep(i, n) rep(tot, MAX_S) {
    ll a = ord[i];
    chmax(dp[i+1][tot], dp[i][tot]);
    if (tot <= s[a]) {
      chmax(dp[i+1][tot+w[a]], dp[i][tot] + v[a]);
    }
  }
  ll ans = 0;
  rep(i, MAX_S) { chmax(ans, dp[n][i]); }
  cout << ans << endl;
}
