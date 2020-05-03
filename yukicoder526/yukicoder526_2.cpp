// ref. http://www.math.sci.hokudai.ac.jp/~ishikawa/yasashii/yahosoku.pdf

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

// Matrix<T>.
// Support pow(Matrix<t> a, ll n).
template<class T> struct Matrix {
public:
  Matrix(int n, int m, T x = 0) : val(n, vector<T>(m, x)) {}

  void init(int n, int m, T x = 0) {
    val.assign(n, vector<T>(m, x));
  }
  size_t size() const {
    return val.size();
  }
  inline vector<T>& operator [] (int i) {
    return val[i];
  }

private:
  vector< vector<T> > val;
};

template<class T> ostream& operator << (ostream& s, Matrix<T> A) {
  s << endl;
  rep(i, A.size()) {
    rep(j, A[i].size()) {
      s << A[i][j] << ", ";
    }
    s << endl;
  }
  return s;
}

template<class T> Matrix<T> operator * (Matrix<T> A, Matrix<T> B) {
  Matrix<T> R(A.size(), B[0].size());
  rep(i, A.size()) {
    rep(j, B[0].size()) {
      rep(k, B.size()) {
        R[i][j] += A[i][k] * B[k][j];
      }
    }
  }
  return R;
}

template<class T> Matrix<T> pow(Matrix<T> A, long long n) {
  Matrix<T> R(A.size(), A.size());
  rep(i, A.size()) {
    R[i][i] = 1;
  }
  while (n > 0) {
    if (n & 1) { R = R * A; }
    A = A * A;
    n >>= 1;
  }
  return R;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n >> MOD;
  Matrix<mint> a(2, 2, 0);
  a[0][0] = 1; a[0][1] = 1;
  a[1][0] = 1; a[1][1] = 0;

  Matrix<mint> b = pow(a, n-1);
  mint ans = b[1][0]; // sum of b[1][0]*1 + b[1][1]*0.
  cout << ans << endl;
}
