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

// Combination mod prime.
// cf. https://www.youtube.com/watch?v=1Z6ofKN03_Y
struct Combination {
  vector<mint> fact, ifact;
  Combination(int n) { init(n); }
  void init(int n) {
    assert(n < MOD); // n must be lower than MOD.

    fact.resize(n + 1);
    ifact.resize(n + 1);

    fact[0] = 1;
    for (int i = 1; i <= n; ++i) { fact[i] = fact[i-1] * i; }
    ifact[n] = fact[n].inv();
    for (int i = n; i >= 1; --i) { ifact[i-1] = ifact[i] * i; }
  }
  mint operator() (int n, int k) const {
    if (k < 0 || k > n) { return 0; }
    return fact[n] * ifact[k] * ifact[n-k];
  }
  mint perm(int n, int k) const {
    if (k < 0 || k > n) { return 0; }
    return fact[n] * ifact[n-k];
  }
};

const ll N = 1005;
Combination comb(N);

// Tree DP. Rerooting.
struct DP {
  mint dp;
  int t;
  DP(mint dp=1, int t=0) : dp(dp), t(t) {};
  DP& operator+=(const DP& a) {
    dp *= a.dp;
    dp *= comb(t+a.t, t);
    t += a.t;
    return *this;
  }
  DP operator+(const DP& a) const {
    DP res(*this);
    return res += a;
  }
  DP& operator-=(const DP& a) {
    t -= a.t;
    dp /= comb(t+a.t, a.t);
    dp /= a.dp;
    return *this;
  }
  DP operator-(const DP& a) const {
    DP res(*this);
    return res -= a;
  }
  DP addRoot() const {
    DP res(*this);
    ++res.t;
    return res;
  }
};

DP dp[N];

vector<vector<ll>> g;

void dfs1(ll v, ll p = -1) {
  DP now;
  for (ll u : g[v]) {
    if (u == p) { continue; }
    dfs1(u,v);
    now += dp[u].addRoot();
  }
  dp[v] = now;
}

void dfs2(ll v, ll p = -1) {
  for (ll u : g[v]) {
    if (u == p) { continue; }
    DP now = dp[v];
    now -= dp[u].addRoot();
    dp[u] += now.addRoot();
    dfs2(u,v);
  }
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  g.resize(n);
  rep(i,n-1) {
    ll a,b;
    cin >> a >> b;
    --a; --b;
    g[a].push_back(b);
    g[b].push_back(a);
  }
  // Do rerooting
  dfs1(0);
  dfs2(0);
  mint ans = 0;
  rep(i,n) {
    ans += dp[i].dp;
  }
  cout << ans/2 << endl; // ans is count of vertices, so we must divide it by 2.
}
