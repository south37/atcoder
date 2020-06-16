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

int main(int argc, char** argv) {
  // int p;
  // cin >> p;

  MOD = 13;
  mint p(10);
  cout << (p + 15).x << endl;    // 12 (25 % 13)
  cout << (p - 15).x << endl;    // 8  (-5 % 13)
  cout << (p * 2).x << endl;     // 7  (20 % 13)
  cout << (p.pow(3)).x << endl;  // 12 (1000 % 13)
  cout << (p / 3).x << endl;     // 12 (12 * 3 = 10 (36 % 13))
  cout << p * mint(3).invWithGcd().x << endl; // 12 (12 * 3 = 10 (36 % 13))

  mint p2(-3);
  cout << p2.x << endl; // 10 (-3 % 13)
}
