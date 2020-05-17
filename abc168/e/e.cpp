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

const double eps = 1e-10;

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  vector<ll> as(n);
  vector<ll> bs(n);
  vector<pair<double,ll>> v2; // pair of <degree, id>. used for debug
  vector<double> v; // degree
  rep(i,n) {
    ll a,b;
    cin >> a >> b;
    double deg = atan2(b,a); // y,x
    v.emplace_back(deg);

    // For Debugh
    v2.emplace_back(deg, i);
    as[i] = a;
    bs[i] = b;
  }
  sort(all(v));
  sort(all(v2));

  mint badCnt = 0; // contribution from bad pairs.
  rep(i,n) {
    double deg90 = M_PI/2;
    double deg270 = M_PI*3/2;
    ll cnt90;
    ll cnt270;
    {
      auto uit90 = upper_bound(all(v), v[i]-deg90+eps);
      auto lit90 = lower_bound(all(v), v[i]-deg90-eps)
      cnt90 = uit90 - lit90;
      // cnt90 = upper_bound(all(v), v[i]-deg90+eps) - lower_bound(all(v), v[i]-deg90-eps);
      auto uit270 = upper_bound(all(v), v[i]-deg90+eps);
      auto lit270 = lower_bound(all(v), v[i]-deg90-eps);
      cnt270 = uit270 - lit270;
      // cnt270 = upper_bound(all(v), v[i]-deg270+eps) - lower_bound(all(v), v[i]-deg270-eps);
    }
    for (auto it = lower_bound(all(v), v[i]-deg90-eps); it !=
    // cout << "i:" << i << endl;
    cout << "cnt90:" << cnt90 << endl;
    cout << "cnt270:" << cnt270 << endl;
    // int j = v2[i].second;
    // cout << "v[i]:" << as[i] << "," << bs[i] << endl;
    badCnt += mint(cnt90+cnt270) * mint(2).pow(n-2);
  }
  cout << "badCnt:" << badCnt << endl;

  mint ans = mint(2).pow(n) - 1; // 1 is empty
  ans -= badCnt;
  cout << ans << endl;
}
