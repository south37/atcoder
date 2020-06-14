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

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  ll k = 0;
  {
    ll t = 1; // t == 2^k
    while (t < n) {
      t *= 2;
      ++k;
    }
  }
  // Here, 2^(k-1) < n <= 2^k.

  vector<ll> V(n), W(n);
  rep(i,n) {
    cin >> V[i] >> W[i];
  }
  ll q;
  cin >> q;
  ll maxL = 0;
  vector<ll> v(q), L(q);
  rep(i,q) {
    cin >> v[i] >> L[i];
    chmax(maxL, L[i]);
  }

  ll k1 = (k+1)/2;
  ll k2 = k-k1;
  // cout << "k1:" << k1 << endl;
  // cout << "k2:" << k2 << endl;

  // Here, as pre-calculation, calculate dp.
  // dp[i][j] .. using [0,i], j is weight. maximum value. i is 1-indexed.
  vector<vector<ll>> dp(1ll<<k1, vector<ll>(maxL+1));
  rep(i,1ll<<k1) {
    if (i == 0) { continue; } // skip
    // Here, parent is i/2
    for (ll j = maxL; j >= 0; --j) {
      ll p = i/2;
      if (j-W[(i-1)] >= 0) {
        chmax(dp[i][j], dp[p][j-W[(i-1)]] + V[(i-1)]);
      }
    }
  }

  // printvec(dp[0]);
  // printvec(dp[1]);

  rep(i,q) {
    ll vi = v[i]; // vi is 1-indexed
    ll li = L[i];

    if (vi<(1ll<<k1)) { // v[i] is in dp
      cout << dp[vi][li] << endl;
      continue;
    }

    // Here, we check all values in a upper half.
    vector<ll> b;
    while (vi >= (1<<k1)) {
      b.push_back(vi);
      vi = vi/2;
    }
    // Here, vi < (1ll<<k1)

    ll ans = 0; // maximum value
    ll ni = b.size();
    rep(j,1ll<<ni) {
      ll wj = 0, vj = 0;
      rep(k,ni) {
        if (j>>k&1) {
          wj += W[b[k]-1];
          vj += V[b[k]-1];
        }
      }
      if (wj > li) { continue; }
      // Here, wj <= li
      chmax(ans, vj+dp[vi][li-wj]);
    }
    cout << ans << endl;
  }
}
