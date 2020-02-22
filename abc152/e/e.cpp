// start: 18:15
// end: 18:28 (13 minutes)
// debug end: 18:39 (24 minutes)

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


int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  vector<ll> A(n);
  for (int i = 0; i < n; ++i) {
    cin >> A[i];
  }

  vector<map<int, int>> factorCntsList(n);
  map<int, int> smallestP; // the count of each factor for smallest product.
  for (int j = 0; j < n; ++j) {
    int num = A[j];
    // Here, we calculate the prime factor
    map<int, int>& factorCnts = factorCntsList[j];

    for (int i = 2; i*i <= num; ++i) {
      while (num % i == 0) {
        ++factorCnts[i];
        num /= i;
      }
    }
    if (num > 1) {
      ++factorCnts[num];
    }
    // cout << "A[i]: " << A[j] << endl;
    // cout << "factorCnts: "; printmap(factorCnts);

    // Next, iterate all (factor, cnts) pairs in factorcnts
    for (auto& p : factorCnts) {
      int factor = p.first;
      int cnt = p.second;
      smallestP[factor] = max(smallestP[factor], cnt);
    }
  }
  // cout << "smallestP: "; printmap(smallestP);

  // Here, smallestP has the information of divisee. B[i] = divisee / A[i].
  // divisee may be very large, so we use factor cnts for each B[i].

  ll ans = 0;
  for (int i = 0; i < n; ++i) {
    map<int, int>& factorCnts = factorCntsList[i];
    ll B = 1;
    for (auto& p : smallestP) {
      int factor = p.first;
      int cnt = p.second - factorCnts[factor];
      // cout << "i: " << i << endl;
      // cout << "B factor; " << factor << endl;
      // cout << "B cnt; " << cnt << endl;
      // we should multiply by pow(factor, cnt)
      if (cnt > 0) { // exist
        mint contrib(factor);
        B *= contrib.pow(cnt).x;
        B %= MOD;
      }
    }
    // cout << "B: " << B.x << endl;
    // Here, B is the multiplier of all contribution from each factors.
    ans += B;
    ans %= MOD;
  }

  cout << ans << endl;
}
