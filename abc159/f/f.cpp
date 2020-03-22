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
const ll MOD = 998244353; // 1000000007;  // 1e9 + 7

const ll MAX_V = 3010;

// Mod int
// cf. https://www.youtube.com/watch?v=1Z6ofKN03_Y
struct mint {
  ll x;
  mint(ll x = 0) : x((x + MOD) % MOD) {}
  mint& operator+= (const mint a) {
    if ((x += a.x) >= MOD) x %= MOD;
    return *this;
  }
  mint operator+ (const mint a) const {
    mint res(*this);
    return res += a;
  }
  mint& operator-= (const mint a) {
    if ((x += MOD - a.x) >= MOD) x %= MOD;
    return *this;
  }
  mint operator- (const mint a) const {
    mint res(*this);
    return res -= a;
  }
  mint& operator*= (const mint a) {
    (x *= a.x) %= MOD;
    return *this;
  }
  mint operator* (const mint a) const {
    mint res(*this);
    return res *= a;
  }
  mint pow(ll t) const {
    if (!t) { return 1; }
    mint a = pow(t >> 1);
    a *= a;
    if (t & 1) a *= *this;
    return a;
  }

  // for prime mod
  mint inv() const {
    return pow(MOD-2);
  }
  mint& operator/= (const mint a) {
    return (*this) *= a.inv();
  }
  mint operator/ (const mint a) const {
    mint res(*this);
    return res /= a;
  }
};

// int main(int argc, char** argv) {
//   // int p;
//   // cin >> p;
//
//   MOD = 13;
//   mint p(10);
//   cout << (p + 15).x << endl;   // 12 (25 % 13)
//   cout << (p - 15).x << endl;   // 8  (-5 % 13)
//   cout << (p * 2).x << endl;    // 7  (20 % 13)
//   cout << (p.pow(3)).x << endl; // 12 (1000 % 13)
//   cout << (p / 3).x << endl;    // 12 (12 * 3 = 10 (36 % 13))
//
//   mint p2(-3);
//   cout << p2.x << endl; // 10 (-3 % 13)
// }


int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n, s;
  cin >> n >> s;
  vector<ll> a(n);
  rep(i, n) {
    cin >> a[i];
  }


  vector<vector<mint>> dp(MAX_V, vector<mint>(MAX_V, 0));
  dp[0][0] = 1; // the count of [0, 0)

  vector<mint> dp2(MAX_V); // dp2[i] .. contains the "contribution from above". dp2[i+1] is the contribution from [0, i).

  rep(i, n) {
    rep(k, s+1) {
      dp[i+1][k] = dp[i][k];
      if (k >= a[i]) { // (k-a[i], a[i]) contributes to dp.
        dp[i+1][k] += dp[i][k-a[i]];

        dp2[i+1] += dp[i][k-a[i]];  // contribution from above.
      }
    }
  }

  cout << "dp2: ";
  rep(i, n+1) {
    cout << dp2[i].x << " ";
  }
  cout << endl;

  // cout << "dp:"; printvec(dpi
  // cout << dp[0][s].x << endl;
  // cout << dp[1][s].x << endl;
  // cout << dp[2][s].x << endl;
  // cout << dp[3][s].x << endl;


  // vector<mint> dp2sum(MAX_V);
  // rep(i, n) {
  // }

  // Here, dp is calculated. f(l,r) = dp[r+1][s] - dp[l][s] - (dp2[l], contribution from abeove).
  mint ans = 0;
  rep(l, n) {
    for (ll r = l; r < n; ++r) {
      cout << dp2[l].x << endl;
      mint now = dp[r+1][s] - dp[l][s] - dp2[l];
      // mint now = dp[r+1][s] - dp[l][s];
      cout << "("<<l<<","<<r<<"): " << now.x << endl;
      ans += now;
    }
  }

  cout << ans.x << endl;
}
