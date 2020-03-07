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
  //cout << setprecision(10) << fixed;

  ll n, p;
  cin >> n >> p;
  string s;
  cin >> s;

  // dp[i][k] ..we count the number of remaining k
  vector<vector<ll>> dp(n+1, vector<ll>(p)); // count of [0, i) for each digit.
  // initialize
  ll ans = 0;

  rep(i, n) {
    ll digit = s[i] - '0';
    // cout << "digit: " << digit << endl;
    // dp[i][k] .. the number of remaining k which include i.

    // Try only this digit.
    ll remain = digit % p;
    dp[i+1][remain] += 1;
    rep(k, p) {
      ll remain = (k * 10 + digit) % p;
      // cout << "k: " << k << endl;
      // cout << "remain: " << remain << endl;
      dp[i+1][remain] += dp[i][k];
    }
    // printvec(dp[i+1]);
    if (dp[i+1][0] > 0) { // k == 0 means divisable
      ans += dp[i+1][0];
    }
  }

  cout << ans << endl;
}
