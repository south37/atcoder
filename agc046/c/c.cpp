// ref. https://atcoder.jp/contests/agc046/submissions/14500508
// ref. https://img.atcoder.jp/agc046/editorial.pdf

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
const ll MOD = 998244353;

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
  // ref. https://qiita.com/drken/items/3b4fdf0a78e7a138cd9a
  mint invWithGcd() const {
    ll a = x, b = MOD, u = 1, v = 0;
    while (b) {
      ll t = a/b;
      a -= t*b; swap(a,b);
      u -= t*v; swap(u,v);
    }
    u %= MOD;
    if (u < 0) { u += MOD; }
    return mint(u);
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
//   cout << (p + 15).x << endl;    // 12 (25 % 13)
//   cout << (p - 15).x << endl;    // 8  (-5 % 13)
//   cout << (p * 2).x << endl;     // 7  (20 % 13)
//   cout << (p.pow(3)).x << endl;  // 12 (1000 % 13)
//   cout << (p / 3).x << endl;     // 12 (12 * 3 = 10 (36 % 13))
//   cout << p * mint(3).invWithGcd().x << endl; // 12 (12 * 3 = 10 (36 % 13))
//
//   mint p2(-3);
//   cout << p2.x << endl; // 10 (-3 % 13)
// }

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  string s;
  ll k;
  cin >> s >> k;

  s += '0'; // sentinel
  ll t = 0; // current count of 1
  ll ones = 0;
  vector<ll> a;
  for (char c : s) {
    if (c == '0') {
      a.push_back(t);
      t = 0;
    } else {
      ++ones;
      ++t;
    }
  }

  ll len = s.size();
  ll cnt = a.size();
  vector<ll> pref(cnt+1); // pref[i] .. cummulative sum of a[0,i).
  rep(i,cnt) {
    pref[i+1] = pref[i] + a[i];
  }

  // dp[i][j][op] .. using [0,i) in a, j is used count of 1, op is effective op added to [0,i).
  vector<vector<vector<mint>>> dp(cnt+1, vector<vector<mint>>(ones+1, vector<mint>(ones+1)));
  dp[0][0][0] = 1;
  rep(i,cnt) {
    rep(j,ones+1) {
      rep(op,ones+1) {
        if (dp[i][j][op].x == 0) { continue; }

        // Here, x is added.
        for (int x = 0; x <= ones-j; ++x) {
          if (j+x < pref[i+1]) {
            continue;
          }
          ll nj  = j+x;
          ll nop = op+max(x-a[i],0ll);
          dp[i+1][nj][nop] += dp[i][j][op];
        }
      }
    }
  }

  mint ans = 0;
  rep(op,min(ones,k)+1) {
    ans += dp[cnt][ones][op];
  }
  cout << ans << endl;
}
