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
const ll MOD = 998244353; // 1000000007;  // 1e9 + 7

const ll MAX_V = 3010;

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

vector<ll> a;
ll s;

// Segment Tree
template <typename T>
class SegTree {
public:
  SegTree(int _n) {
    n = 1;
    while (n < _n) { n *= 2; }
    // dat[i] contains the information of counts in s. dat[i] .. [0, i)
    dat = vector<vector<T>>(2 * n - 1, vector<T>(MAX_V, 0));
    dat[n-1][0] = 1;
  }

  void update(int id) {
    ll k = id + n - 1;
    // Here, we update the count of dat[k]
    // dat[k] = val;
    rep(j, s+1) { // loop from 0 to s
      dat[k][j] = dat[k-1][j];
      if (j >= a[id-1]) {
        dat[k][j] += dat[k-1][j-a[id-1]];
      }
    }
    cout << "dat["<<k-(n-1)<<"]:";
    rep(i, 7) {
      cout << dat[k][i].x << " ";
    }
    cout << endl;
    cout << "dat["<<k-(n-1)<<"][s]: " << dat[k][s].x << endl;

    while (k > 0) {
      k = (k - 1) / 2;
      // dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]);
      rep(j, s+1) { // loop from 0 to s
        dat[k][j] = max(dat[k*2+1][j], dat[k*2+2][j]);
      }
    }
  }

  // Calculate the min of [a, b)
  T query(int a, int b) {
    return _query(a, b, 0, 0, n);
  }

  // Calculate the min of [a, b)
  // k is the index (dat[k]). This is matched to [l, r)
  T _query(int a, int b, int k, int l, int r) {
    // The intersection of [a, b) and [r, l) is blank.
    if (r <= a || b <= l) { return 0; }

    if (a <= l && r <= b) {  // [r, l) is completely included in [a, b)
      return dat[k][s];
    } else {
      T vl = _query(a, b, k * 2 + 1, l, (l + r) / 2);
      T vr = _query(a, b, k * 2 + 2, (l + r) / 2, r);
      return max(vl.x, vr.x);
    }
  }

private:
  int n; // The size of source data. The power of 2.
  vector<vector<T>> dat; // The data. The size if 2*n-1. The last n elements(dat[n..2*n-2]) are leaves(source data). The first n-1 elements are nodes.
};

// int main(int argc, char** argv) {
//   int arr[] = { 1, 3, 2, 7, 9, 11 };
//   int n = 6;
//
//   SegTree<int> st(n);
//   rep(i, n) {
//     st.update(i, arr[i]);
//   }
//
//   cout << st.query(1, 5) << endl;
//   cout << st.query(0, 4) << endl;
//   cout << st.query(3, 5) << endl;
// }

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n >> s;
  a.resize(n);
  rep(i, n) {
    cin >> a[i];
  }

  SegTree<mint> st(MAX_V);
  rep(i, n) {
    st.update(i+1); //, a[i]);
  }

  // Here, st contains the information of count in each range.
  mint ans = 0;
  rep(l, n) {
    for (ll r = l; r < n; ++r) {
      cout << "("<<l<<","<<r<<"):" << st.query(l+1, r+2).x << endl;
      ans += st.query(l+1, r+2);
    }
  }
  cout << ans.x << endl;
}
