// ref. https://suikaba.hatenablog.com/entry/2017/08/22/163506

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

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  vector<ll> freq;
  rep(i,26) {
    ll f;
    cin >> f;
    if (f > 0) {
      freq.push_back(f);
    }
  }
  ll n = freq.size(); // effective count

  vector<ll> s(n+1); // s[i] .. total sum of [0,i)
  rep(i,n) {
    s[i+1] = s[i] + freq[i];
  }
  Combination comb(305);

  // printvec(freq);
  // printvec(s);

  // dp[i][j] .. using [0,i), j .. count of bad.
  vector<vector<mint>> dp(n+1,vector<mint>(305));
  dp[0][0] = 1;

  rep(i,n) {
    for (ll k = 1; k <= freq[i]; ++k) {
      rep(l,s[i]+1) { // loop in [0,s[i]]. bad at i-1.
        rep(m,l+1) { // loop in [0,l]
          if (m > k) { continue; } // m must be equal or lower than k.
          mint now = 1;
          now *= comb(l,m); // select m from bad
          now *= comb(s[i]+1-l,k-m); // select k-m from good
          now *= comb(freq[i]-1,k-1); // cut freq[i] to k
          now *= dp[i][l];

          ll nl = l-m+freq[i]-k; // next count of bad
          dp[i+1][nl] += now;
          // cout << "i: " << i << endl;
          // cout << "nl: " << nl << endl;
          // cout << "now: " << now << endl;
        }
      }
    }
  }

  cout << dp[n][0] << endl;
}
