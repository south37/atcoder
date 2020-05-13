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

const ll N = 105;
const ll A = 65; // 2
const ll B = 40; // 3
const ll C = 30; // 5
double dp[N][A][B][C];

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  cout << setprecision(10) << fixed;

  ll n, d;
  cin >> n >> d;
  // factors of 2, 3, 5
  vector<ll> nums = { 2, 3, 5 };
  vector<ll> factors(3);
  rep(i,3) {
    while (d%nums[i] == 0) {
      ++factors[i];
      d /= nums[i];
    }
  }
  if (d > 1) { // d has prime factor without [2,3,5]
    cout << 0 << endl;
    return 0;
  }

  // Here, we calculate the probability.
  dp[0][0][0][0] = 1.0;
  rep(i,n) {
    rep(j,A)rep(k,B)rep(l,C) {
      // 1. unchange.
      dp[i+1][j][k][l] += dp[i][j][k][l] / 6;
      // 2. 2
      if (j < A-1) {
        dp[i+1][j+1][k][l] += dp[i][j][k][l] / 6;
      }
      // 3. 3
      if (k < B-1) {
        dp[i+1][j][k+1][l] += dp[i][j][k][l] / 6;
      }
      // 4. 2^2
      if (j < A-2) {
        dp[i+1][j+2][k][l] += dp[i][j][k][l] / 6;
      }
      // 5. 5
      if (l < C-1) {
        dp[i+1][j][k][l+1] += dp[i][j][k][l] / 6;
      }
      // 6. 2,3
      if (j < A-1 && k < B-1) {
        dp[i+1][j+1][k+1][l] += dp[i][j][k][l] / 6;
      }
    }
  }

  double ans = 0;
  rep(j,A)rep(k,B)rep(l,C) {
    if (j >= factors[0] && k >= factors[1] && l >= factors[2]) {
      ans += dp[n][j][k][l];
    }
  }
  cout << ans << endl;
}
