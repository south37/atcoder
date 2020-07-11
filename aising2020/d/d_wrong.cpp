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
// const ll MOD = 1000000007;  // 1e9 + 7

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

  ll n;
  cin >> n;
  string s;
  cin >> s;

  ll c = 0; // count of 1 at first state
  rep(i,n) {
    if (s[i] == '1') {
      ++c;
    }
  }

  // table[i] .. answer of i.
  vector<ll> table(n+1);
  table[0] = 0;
  table[1] = 1;
  rep(i,n+1) {
    if (i == 0) { continue; }
    ll now = i % __builtin_popcountll(i);
    // cout << "i: " << i << endl;
    // cout << "popcount(i): " << __builtin_popcountll(i) << endl;
    // cout << "now: " << now << endl;
    table[i] = table[now] + 1;
  }

  // rep(i,n+1) {
  //   cout << "table["<<i<<"]: " << table[i] << endl;
  // }

  auto flip = [&](ll i) {
    if (s[i] == '1') { s[i] = '0';
    } else { s[i] = '1'; }
  };

  ll firstState1 = 0; // remain for first value by n+1.
  {
    MOD = n+1;
    mint now = 0;
    rep(i,n) {
      if (s[i] == '1') {
        now += mint(2).pow(n+1-i);
      }
    }
    // Here, now represents the mod representation of first value.
    firstState1 = now.x;
  }
  ll firstState2 = 0; // remain for first value by n-1.
  if (n > 1) {
    MOD = n-1; // n-1 >= 1
    mint now = 0;
    rep(i,n) {
      if (s[i] == '1') {
        now += mint(2).pow(n+1-i);
      }
    }
    // Here, now represents the mod representation of first value.
    firstState2 = now.x;
  }

  // calculate s
  // ll now = 0;
  // rep(i,n) {
  //   now *= 2;
  //   now += (s[i] - '0');
  // }
  // cout << "num: " << now << endl;

  // We necessary only under 16 bit of first number.
  rep(i,n) {
    // cout << s << endl;

    ll nc = c; // current c
    if (s[i] == '1') { // we flip i, so decrease c.
      --nc;
    } else {
      ++nc;
    }

    // flip
    flip(i);

    // Check 0
    bool isAllZero = true;
    rep(i,n) {
      if (s[i] != '0') {
        isAllZero = false;
        break;
      }
    }
    if (isAllZero) { // already 0
      flip(i); // revert
      cout << 0 << endl;
      continue;
    }

    ll now = 0;
    // use last 32 bit.
    // rep(j,n) {
    rep(j,n) {
      if (s[n-1-j] == '1') {
        now += 1ll<<j;
      }
      // for (ll j = max(0ll, n-1-16); j < n; ++j) {
      // now *= 2;
      // now += (s[j] - '0');
      // cout << "n-1-j: " << n-1-j << endl;
      // cout << "s[n-1-j]:" << s[n-1-j] << endl;
    }
    // Here, this value represent value of last 16bit

    // cout << "i: " << i << endl;
    // cout << "c: " << c << endl;
    // cout << "nc: " << nc << endl;
    // cout << "now: " << now << endl;

    // We simulat from "now".
    ll cnt = 0;
    ++cnt;
    now %= nc; // decrease.
    cout << table[now] + 1 << endl;

    // {
    //   while (now > 0) {
    //     ++cnt;
    //     now %= __builtin_popcountll(now);
    //   }
    // }
    // cout << cnt << endl;

    // revert
    flip(i);
  }

  // rep(i,10) {
  //   if (i==0) { continue; }

  //   cout << "i: " << i << endl;
  //   // simulate by i
  //   {
  //     ll now = 0;

  //     ll j = i;
  //     while (j > 0) {
  //       ++now;
  //       j %= __builtin_popcountll(j);
  //       // cout << "j: " << j << endl;
  //     }
  //     cout << now << endl;
  //   }
  // }
}
