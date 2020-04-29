// ref. https://www.hamayanhamayan.com/entry/2019/01/12/152428

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
ll MOD;

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

vector<vector<ll>> g;
vector<mint> dp;
vector<mint> ans;

void dfs1(ll v, ll p=-1) {
  mint res(1);
  for (ll u : g[v]) {
    if (u == p) { continue; }
    dfs1(u, v);
    res *= dp[u]+1;
  }
  dp[v] = res;
}

void dfs2(ll v, ll p=-1) {
  ans[v] = 1;
  for (ll u : g[v]) {
    ans[v] *= dp[u]+1;
  }

  ll m = g[v].size();
  vector<mint> lft(m); // lft[i] .. [0,i]
  vector<mint> rht(m); // rht[i] .. [i,m]
  rep(i,m) {
    ll u = g[v][i];
    lft[i] = rht[i] = dp[u] + 1;
  }
  rep(i,m-1) {
    lft[i+1] *= lft[i];
  }
  for (ll i = m-2; i >= 0; --i) {
    rht[i] *= rht[i+1];
  }

  rep(i,m) {
    ll u = g[v][i];
    if (u == p) { continue; }
    mint now(1);
    if (i) { now *= lft[i-1]; }
    if (i<m-1) { now *= rht[i+1]; }
    dp[v] = now;
    dfs2(u, v);
  }
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n >> MOD;
  g.resize(n);
  dp.resize(n);
  ans.resize(n);

  rep(i,n-1) {
    ll x, y;
    cin >> x >> y;
    --x; --y;
    g[x].push_back(y);
    g[y].push_back(x);
  }

  // Do rerooting
  dfs1(0);
  dfs2(0);

  rep(i,n) {
    cout << ans[i] << endl;
  }
}
