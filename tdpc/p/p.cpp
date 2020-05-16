// ref. https://suikaba.hatenablog.com/entry/2017/08/26/024334

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
istream& operator>>(istream& is, const mint& a) { return is >> a.x;}
ostream& operator<<(ostream& os, const mint& a) { return os << a.x;}

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

const ll MAX_N = 1005;
const ll MAX_K = 55;
vector<vector<ll>> g;
mint dp[MAX_N][MAX_K][3];
mint dp2[MAX_N][MAX_K][3];
ll n,K;

void dfs(int v, int p=-1) {
  vector<int> childs;
  for (ll u : g[v]) {
    if (u == p) { continue; }
    childs.push_back(u);
    dfs(u,v);
  }

  // initialization
  rep(i,n+1)rep(j,K+1)rep(l,3) {
    dp2[i][j][l] = 0;
  }
  dp2[0][0][0] = 1;
  // i .. idx of child.
  // j .. count of paths at v (when seeing i)
  // k .. path degree at v (when seeing i)
  // l .. count of paths at child i.
  // m .. path degree at child i.
  rep(i,childs.size())rep(j,K+1)rep(k,3) {
    rep(l,K+1)rep(m,3) {
      if (j+l > K+1) { continue; } // j+l must be equal or lower than K+1. The count of paths may decrease by once, so we allow +1.

      mint now = dp2[i][j][k] * dp[childs[i]][l][m];
      // 1. not connect v<->i.
      if (j+l <= K) {
        dp2[i+1][j+l][k] += now;
      }
      // 2. connect v<->i.
      if (k == 0) {
        if (m == 0 && j+l+1 <= K) { // The count of paths increases by 1.
          dp2[i+1][j+l+1][1] += now;
        } else if (m == 1 && j+l <= K) { // The count of paths does not change.
          dp2[i+1][j+l][1] += now;
        }
      } else if (k == 1) {
        if (m == 0 && j+l <= K) { // The count of paths does not change. The degree increases by 1.
          dp2[i+1][j+l][2] += now;
        } else if (m == 1 && j+l-1 <= K) { // The count of paths decreases by 1. The degree increases by 1.
          dp2[i+1][j+l-1][2] += now;
        }
      }
    }
  }

  // Here, copy dp2[childs.size()] to dp[v].
  rep(j,K+1)rep(k,3) {
    dp[v][j][k] = dp2[childs.size()][j][k];
  }
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  cin >> n >> K;
  g.resize(n);
  rep(i,n-1) {
    ll a,b;
    cin >> a >> b;
    --a; --b;
    g[a].push_back(b);
    g[b].push_back(a);
  }
  dfs(0);
  mint ans = 0;
  rep(i,3) {
    ans += dp[0][K][i];
  }
  cout << ans << endl;
}
