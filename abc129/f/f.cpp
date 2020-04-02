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
ll MOD;
ll L, a, b;

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

// f(l) .. contribution from a.
// f(l+1) = f(l)*10^k + 1
// f(l*2) = f(l)*10^kl + f(l)

// g(l) .. contribution from b.
// g(l+1) = g(l)*10^k + bl
// g(l*2) = g(l)*10^kl + g(l) + bl*f(l)

mint f(ll l, ll ten) {
  if (l == 0) { return 0; }
  if (l%2 == 1) {
    ll pl = l-1;
    mint x = f(pl, ten);
    return x * ten + 1;
  } else {
    ll pl = l/2;
    mint x = f(pl, ten);
    return x * mint(ten).pow(pl) + x;
  }
}

mint g(ll l, ll ten) {
  if (l == 0) { return 0; }
  if (l%2 == 1) {
    ll pl = l-1;
    mint x = g(pl, ten);
    return x*ten + b*pl;
  } else {
    ll pl = l/2;
    mint x = g(pl, ten);
    return x * mint(ten).pow(pl) + x + mint(b)*pl*f(pl, ten);
  }
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  cin >> L >> a >> b >> MOD;
  ll last = a+b*(L-1);
  ll ten = 10;
  mint ans(0);
  for (int i = 1; i <= 18; ++i, ten *= 10) {
    ll l = ten/10, r = ten-1; // e.g. [10, 99] for i=2
    if (last < l) { continue; } // skip small value
    if (a > r) { continue; } // skip large value

    ll na = 0; // initial term
    ll nl = 0; // length
    {
      if (a >= l) {
        na = a;
      } else {
        ll i = ((l-a)+(b-1))/b; // round up of (l-a)/b
        na = a+b*i; // minimum value equal or larger than l
        na = min(na, last);
      }
    }
    {
      ll nlast = 0;
      if (last <= r) {
        nlast = last;
      } else {
        ll i = (r-a)/b;
        nlast = a+b*i; // maximum value equal or smaller than r.
      }
      nl = (nlast-na)/b + 1;
    }
    ans *= mint(ten).pow(nl);
    ans += mint(na)*f(nl, ten);
    ans += g(nl, ten);
  }

  cout << ans.x << endl;
}
