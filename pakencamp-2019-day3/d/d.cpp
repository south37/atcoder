#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string.h>
#include <set>
#include <stack>

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

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  vector<vector<ll>> S(5, vector<ll>(n));
  rep(i,5) {
    string s;
    cin >> s;

    rep(j,n) {
      if (s[j] == 'R') {
        S[i][j] = 0;
      } else if (s[j] == 'B') {
        S[i][j] = 1;
      } else if (s[j] == 'W') {
        S[i][j] = 2;
      } else { // #
        S[i][j] = 3;
      }
    }
  }

  vector<vector<ll>> dp(n+1, vector<ll>(3,INF));
  rep(i,3) {
    dp[0][i] = 0;
  }
  rep(i,n) {
    rep(k,3) { // current color
      ll now = 0; // current cost.
      rep(j,5) {
        if (S[j][i] != k) { ++now; }
      }

      rep(j,3) { // prev color
        if (j == k) { continue; } // can not be same
        chmin(dp[i+1][k], dp[i][j] + now);
      }
    }
  }

  ll ans = INF;
  rep(i,3) {
    chmin(ans, dp[n][i]);
  }
  cout << ans << endl;
}
