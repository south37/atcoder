// ref. https://www.youtube.com/watch?v=JQmQjJd-sLA

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

  string s;
  cin >> s;
  ll n = s.size();
  ll K;
  cin >> K;

  // dp[i][j][l] .. use [0, i). j .. count of not 0 is k. l=0: equal, l=1: smaller.
  vector<vector<vector<ll>>> dp(n+1, vector<vector<ll>>(4, vector<ll>(2)));
  dp[0][0][0] = 1;

  rep(i, n) rep(j, 4) rep(k, 2) {
    ll nd = s[i]-'0';
    rep(d, 10) {
      ll ni = i+1;
      ll nj = j;
      ll nk = k;
      if (d != 0) { ++nj; }
      if (nj > K) { continue; } // we need only [0, K]
      if (k == 0) {
        if (d > nd) { continue; } // larger value.
        if (d < nd) { nk = 1; } // becomes smaller
      }
      dp[ni][nj][nk] += dp[i][j][k];
    }
  }

  cout << dp[n][K][0] + dp[n][K][1] << endl;
}
