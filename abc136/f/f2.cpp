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

// BIT (Fenwick Tree) with 0-indexed query
// https://youtu.be/lyHk98daDJo?t=7960
template<typename T>
struct BIT {
  int n;
  vector<T> d;
  BIT(int n=0) : n(n), d(n+1) {}
  void add(int i, T x=1) {
    i++; // 0-indexed to 1-indexed
    for (; i <= n; i += i&-i) {
      d[i] += x;
    }
  }
  // The sum of [0, i]
  T sum(int i) {
    i++; // 0-indexed to 1-indexed
    T x = 0;
    for (; i; i -= i&-i) {
      x += d[i];
    }
    return x;
  }
  // The sum of [l, r)
  T sum(int l, int r) {
    assert(l <= r);
    if (r == 0) { return 0; } // Here, l == 0 && r == 0
    if (l == 0) { return sum(r-1); }
    return sum(r-1) - sum(l-1);
  }
};

// int main(int argc, char** argv) {
//   int N;
//   cin >> N;
//   vector<int> v(N);
//   rep(i, N) {
//     cin >> v[i];
//   }
//
//   BIT<int> bit(N);
//   rep(i, N) {
//     bit.add(i, v[i]);
//   }
//
//   cout << bit.sum(4) << endl; // sum of [0,4]. 24
//   cout << bit.sum(9) << endl; // sum of [0,9]. 55
// }

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

mint f(int a, int b, int c, int d) {
  mint res = 0;
  vector<int> num = { a, b, c, d };
  vector<mint> o(4), ox(4);
  rep(i,4) {
    ox[i] = mint(2).pow(num[i]);
    o[i] = ox[i] - 1;
  }
  // add the contribution without target
  res += ox[0]*o[1]*o[2]*ox[3];
  res += o[0]*ox[1]*ox[2]*o[3];
  res -= o[0]*o[1]*o[2]*o[3];
  // add the contribution with target
  res += ox[0]*ox[1]*ox[2]*ox[3];
  return res;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  int n;
  cin >> n;
  vector<P> p(n);
  rep(i,n) {
    cin >> p[i].first >> p[i].second;
  }
  // compress x
  {
    map<int,int> mp;
    rep(i,n) { mp[p[i].first] = 0; }
    int i = 0;
    for (auto& x : mp) { x.second = i++; }
    rep(i,n) {
      p[i].first = mp[p[i].first];
    }
  }
  // compress y
  {
    map<int,int> mp;
    rep(i,n) { mp[p[i].second] = 0; }
    int i = 0;
    for (auto& x : mp) { x.second = i++; }
    rep(i,n) {
      p[i].second = mp[p[i].second];
    }
  }

  // For Debug
  // rep(i,n) {
  //   cout << p[i].first << "," << p[i].second << endl;
  // }

  sort(all(p));
  vector<int> a(n), b(n), c(n), d(n);
  rep(_,2) {
    { // calc a,b (or c,d)
      BIT<int> bit(n);
      rep(i,n) {
        a[i] = bit.sum(0,p[i].second);
        b[i] = i-a[i];
        bit.add(p[i].second,1);
      }
    }
    reverse(all(p));
    swap(a,c);
    swap(b,d);
  }
  // Here, c and d should be reversed.
  reverse(all(c));
  reverse(all(d));

  mint ans = 0;
  rep(i,n) {
    ans += f(a[i],b[i],c[i],d[i]);
  }
  cout << ans << endl;
}
