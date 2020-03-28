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
  ll k;
  cin >> k;

  // dp[i][j][l] .. i=0: smaller, i=1: equal. j .. use [0, j). l .. count of not 0 is k.
  vector<vector<vector<ll>>> dp(2, vector<vector<ll>>(n+1, vector<ll>(k+2)));
  dp[1][0][0] = 1;
  rep(j, n) {
    ll digit = s[j] - '0';
    rep(i, 2) {
      rep(l, k+1) {
        rep(m, 10) { // consider number m
          if (i == 1 && m > digit) { continue; } // skip

          ll ni = (i==0) ? 0 : ((m < digit) ? 0 : 1);
          ll nl = (m == 0) ? l : (l+1); // the next count of not-0
          dp[ni][j+1][nl] += dp[i][j][l];
        }
      }
    }
  }

  cout << dp[0][n][k] + dp[1][n][k] << endl;
}
