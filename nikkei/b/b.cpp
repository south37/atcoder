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

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  vector<ll> d(n);
  rep(i, n) {
    cin >> d[i];
  }
  // cout << "debug";
  // printvec(d);

  if (d[0] != 0) { // d[0] must be 0
    cout << 0 << endl;
    return 0;
  }

  vector<ll> dist(n); // The distribution of d[i]. 0 <= d[i] <= n-1
  for (int i = 1; i < n; ++i) {
    ++dist[d[i]];
  }
  if (dist[0] > 0) { // 0 exists
    cout << 0 << endl;
    return 0;
  }

  // Check the fullfillness
  ll last_i = -1; // The last presence index.
  for (int i = 1; i < n; ++i) {
    if (dist[i] > 0) { last_i = i; }
  }
  // Here, last_i contains the last_i. If j < last_i & d[j] == 0 exists, it is invalid.
  for (int i = 1; i < last_i; ++i ) {
    if (dist[i] == 0 && i < last_i) {
      cout << 0 << endl;
      return 0;
    }
  }

  // cout <<"debug" << endl;
  // cout <<"dist:";
  // printvec(dist);

  // Now, dist contains the distribution of d[i].
  mint ans(1);
  for (int i = 1; i <= last_i; ++i) { // select each i.
    if (i == 1) {
      // cout << "i: " << i << endl;
      // cout << "coeff: " << 1 << endl;
      // Do nothing
    } else {
      mint coeff(dist[i-1]);
      coeff.pow(dist[i]);

      // cout << "i: " << i << endl;
      // cout << "dist[i-1]: " << dist[i-1] << endl;
      // cout << "dist[i]: " << dist[i] << endl;
      // cout << "coeff: " << coeff.pow(dist[i]).x << endl;
      ans *= coeff.pow(dist[i]);
    }
  }

  cout << ans.x << endl;
}
