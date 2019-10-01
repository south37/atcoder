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

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

ll powmod(ll x, ll n) { // like pow(x, n)
  ll r = 1;
  while (n) {
    if (n & 1) {
      r = r * x % MOD;
    }
    x = x * x % MOD;
    n >>= 1;
  }
  return r;
}

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

// Combination mod prime.
// cf. https://www.youtube.com/watch?v=1Z6ofKN03_Y
struct Combination {
  vector<mint> fact, ifact;
  Combination(int n) : fact(n + 1), ifact(n + 1) {
    assert(n < MOD); // n must be lower than MOD.
    fact[0] = 1;
    for (int i = 1; i <= n; ++i) { fact[i] = fact[i-1] * i; }
    ifact[n] = fact[n].inv();
    for (int i = n; i >= 1; --i) { ifact[i-1] = ifact[i] * i; }
  }
  mint operator() (int n, int k) {
    if (k < 0 || k > n) { return 0; }
    return fact[n] * ifact[k] * ifact[n-k];
  }
  mint perm(int n, int k) {
    if (k < 0 || k > n) { return 0; }
    return fact[n] * ifact[n-k];
  }
};

Combination comb(100010);
int K;
vector< vector<int> > tree;

// Return the number of pattern
mint dfs(int v, int p) {
  // We want to return nk_P_j
  int nk; // number of colors we can use.
  int j; // number of vertices we have to paint.

  if (p == -1) { // root
    nk = K;
    j  = tree[v].size() + 1; // We must paint the root. This is +1.
  } else {
    nk = K - 2;
    j  = tree[v].size() - 1; // Extract parent. This is -1.
  }
  // cout << "v: "<<v<<", p: "<<p << endl;
  // cout << "nk: "<<nk<<", j: "<<j << endl;

  if (nk < j) { // number of color is smaller
    return 0;
  }

  mint res = comb.perm(nk, j);
  for (auto u : tree[v]) {
    if (u == p) { continue; }
    res *= dfs(u, v);
  }
  return res;
}

int main(int argc, char** argv) {
  int N;
  cin >> N >> K;
  tree.resize(N);
  rep(i, N - 1) {
    int a, b;
    cin >> a >> b;
    --a; --b;
    tree[a].push_back(b);
    tree[b].push_back(a);
  }
  // rep(i, N) {
  //   for (auto x : tree[i]) {
  //     cout << i << "->" << x << endl;
  //   }
  // }
  mint ans = dfs(0, -1); // dfs from root (0). -1 indicates the root (no-parent).
  cout << ans.x << endl;
}
