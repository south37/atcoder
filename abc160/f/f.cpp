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

Combination c(1);

// int main(int argc, char** argv) {
//   MOD = 13;
//
//   Combination c(12);
//   cout << c(12, 0).x << endl;  // 1  = 1 % 13
//   cout << c(12, 1).x << endl;  // 12 = 12 % 13
//   cout << c(12, 2).x << endl;  // 1  = 66 % 13 = (12 * 11 / 2) % 13
//   cout << c(12, 3).x << endl;  // 12 = 220 % 13 = (12 * 11 * 10 / (3 * 2 * 1)) % 13
//   cout << c(12, 11).x << endl; // 12 = 12 % 13
//   cout << c(12, 12).x << endl; // 1  = 12 % 13
//
//   cout << c.perm(12, 3).x << endl; // 7 = 12 * 11 * 10 % 13
// }

vector<vector<ll>> g; // tree

vector<mint> ans;

// vector<vector<pair<ll, mint>>> subCnts; // cnts[i][j] .. parent i to subtree j
// vector<vector<pair<ll, mint>>> subCnts; // cnts[i][j] .. parent i to subtree j

map<ll, map<ll, pair<ll, mint>>> subCnts;

// return the count of subtree
pair<ll, mint> dfs(int v, int p) {
  if (p != -1 && subCnts[p].find(v) != subCnts[p].end()) {
    return subCnts[p][v];
  }

  vector<ll> cnts;
  vector<mint> patterns;
  vector<ll> subs;

  for (int nv : g[v]) {
    if (nv == p) { continue; } // skip parent
    auto p = dfs(nv, v); // { cnt, pattern }
    cnts.push_back(p.first);
    patterns.push_back(p.second);
    subs.push_back(nv);
  }
  // cout << "v:" << v << endl;
  // cout << "cnts:";
  // printvec(cnts);
  // cout << "patterns:";
  // rep(i, patterns.size()) {
  //   cout << patterns[i].x << " ";
  // }
  // cout << endl;

  ll totalCnt = 0;
  mint totalPattern(1);
  rep(i, cnts.size()) {
    ll cnt = cnts[i];
    totalCnt += cnt;
  }
  totalPattern *= c.fact[totalCnt];
  // cout << "perm(2): " << c.fact[2].x << endl;

  rep(i, cnts.size()) {
    ll cnt = cnts[i];
    mint p = patterns[i];

    totalPattern *= p;
    totalPattern /= c.fact[cnt];
  }

  // Memorize at root
  if (p == -1) {
    // Here, we can calculate subCnts[subV][v] easily
    rep(i, cnts.size()) {
      int nv = subs[i];
      int cnt = cnts[i];
      mint p = patterns[i];

      mint subP = totalPattern;
      subP *= c.fact[cnt];
      subP /= c.fact[totalCnt];
      subP *= c.fact[totalCnt - cnt];
      subP /= p;

      subCnts[nv][v] = { totalCnt + 1 - cnt, subP };
    }
  }

  // cout << "totalCnt: " << totalCnt << endl;
  // cout << "totaPattern: " << totalPattern.x << endl;

  subCnts[p][v] = { totalCnt + 1, totalPattern };
  return subCnts[p][v];
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  ans.resize(n);

  // subCnts = vector<vector<pair<ll, mint>>(n+1, vector<pair<ll, mint>>(n+1, pair<ll, mint>(INF, mint(0)));

  c.init(n+5);

  g.resize(n);
  rep(i, n-1) {
    ll a, b;
    cin >> a >> b;
    --a; --b;
    g[a].push_back(b);
    g[b].push_back(a);
  }

  // Here, we should do tree dp.
  rep(i, n) {
    auto p = dfs(i, -1);
    // Here, p is the result from 0
    ll cnt = p.first;
    mint ans = p.second;
    cout << ans.x << endl;
  }
}
