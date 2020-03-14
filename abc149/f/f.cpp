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

ll n;
vector<vector<ll>> tree;
mint ans(0);

ll dfs(ll v, ll p = -1) {
  ll cnt = 1; // the count without parent
  vector<ll> ts; // the size of subtrees
  for (ll nv : tree[v]) {
    if (nv == p) { continue; } // skip parent
    ll t = dfs(nv, v);
    cnt += t;
    ts.push_back(t);
  }
  if (p != -1) {
    ts.push_back(n - cnt);
  }
  // Add contribution from this node.
  mint now = mint(2).pow(n-1);
  now -= 1; // The case in which all-white
  for (int t : ts) {
    now -= mint(2).pow(t)-1; // The case in which only t has black
  }
  ans += now;
  return cnt;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  cin >> n;
  tree.resize(n);
  rep(i, n-1) {
    ll a, b;
    cin >> a >> b;
    --a; --b; // 0-indexed
    tree[a].push_back(b);
    tree[b].push_back(a);
  }

  dfs(0); // start dfs from 0
  ans /= mint(2).pow(n);
  cout << ans.x << endl;
}
