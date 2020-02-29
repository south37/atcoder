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

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

const ll D = 80*160 + 10; // abs(A-B) * (H+W) + 10
const ll D2 = D*2;

typedef bitset<D2> bs;

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll h, w;
  cin >> h >> w;
  vector<vector<ll>> a(h, vector<ll>(w));
  rep(i, h) {
    rep(j, w) {
      cin >> a[i][j];
    }
  }
  rep(i, h) {
    rep(j, w) {
      ll x;
      cin >> x;
      a[i][j] = abs(a[i][j] - x);;
    }
  }
  // Here, a contains the diff of A and B

  vector<vector<bs>> dp(h, vector<bs>(w));
  dp[0][0][D-a[0][0]] = 1;
  dp[0][0][D+a[0][0]] = 1;
  rep(i, h) {
    rep(j, w) {
      if (i) {
        dp[i][j] |= dp[i-1][j] << a[i][j];
        dp[i][j] |= dp[i-1][j] >> a[i][j];
      }
      if (j) {
        dp[i][j] |= dp[i][j-1] << a[i][j];
        dp[i][j] |= dp[i][j-1] >> a[i][j];
      }
    }
  }
  // Here, dp[i][j][k] means the reachability of k at (i,j)

  ll ans = D;
  rep(k, 2*D) {
    if (dp[h-1][w-1][k]) { // reachable to k
      ans = min(ans, abs(k-D));
    }
  }
  cout << ans << endl;
}
