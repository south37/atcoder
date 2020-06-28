// ref. https://www.youtube.com/watch?v=v8ppNGf49Nk

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

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

const int K = 43;

// dp[i][j][k] .. i: digit i, j: carry, k: 0 .. eqal or smqll, 1 .. large. maximum number.
ll dp[K][2][2];

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  vector<ll> _a(n);
  rep(i,n) {
    cin >> _a[i];
  }
  ll x = 0;
  for (int i = 2; i < n; ++i) {
    x ^= _a[i];
  }
  ll a = _a[0], b = _a[1];
  ll s = a+b;

  // Digit dp
  // initialize
  rep(i,K)rep(j,2)rep(k,2) {
    dp[i][j][k] = -1;
  }
  dp[0][0][0] = 0;
  ll v = 1;
  rep(i,K-1) {
    int cx = x&1;
    int cs = s&1;
    int ca = a&1;
    rep(j,2)rep(k,2) {
      if (dp[i][j][k] == -1) { continue; } // invalid
      rep(na,2)rep(nb,2) {
        int ni = i+1;
        int nj = 0, nk;
        if ((na^nb) != cx) { continue; } // invalid.
        int ns = na+nb+j;
        if (ns%2 != cs) { continue; } // invalid.
        if (ns >= 2) { nj = 1; } // carry
        if (ca < na) {
          nk = 1;
        } else if (ca == na) {
          nk = k;
        } else { // ca > na
          nk = 0;
        }
        chmax(dp[ni][nj][nk], dp[i][j][k]|(v*na));
      }
    }
    x >>= 1;
    s >>= 1;
    a >>= 1;
    v <<= 1;
  }

  // For Debug
  // rep(i,K) {
  //   rep(j,2)rep(k,2) {
  //     cout << dp[i][j][k] << " ";
  //   }
  //   cout << endl;
  // }
  // For Debug
  // cout << "a': " << dp[K-1][0][0] << endl;

  if (dp[K-1][0][0] <= 0) { // 0 or -1
    cout << -1 << endl;
  } else {
    cout << (_a[0] - dp[K-1][0][0]) << endl;
  }
}
