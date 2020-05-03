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

const ll MAX_ROW = 105; // To be set appropriately.
const ll MAX_COL = 105; // To be set appropriately.

class BitMatrix {
public:
  BitMatrix(int h = 1, int w = 1) : H(h), W(w) {}
  inline bitset<MAX_COL>& operator [] (int i) { return val[i]; }
  inline const bitset<MAX_COL>& operator [] (int i) const { return val[i]; }
  int H, W;
  size_t size() const { return H; }
  BitMatrix transpose() const {
    BitMatrix R(W, H);
    rep(r,H)rep(c,W) {
      R[c][r] = val[r][c];
    }
    return R;
  }

private:
  bitset<MAX_COL> val[MAX_ROW];
};

ostream& operator << (ostream& s, BitMatrix& A) {
  s << endl;
  rep(i, A.H) {
    rep(j, A.W) { s << A[i][j] << ", "; }
    s << endl;
  }
  return s;
}

BitMatrix operator * (const BitMatrix& A, const BitMatrix& B) {
  BitMatrix revB = B.transpose();
  BitMatrix R(A.size(), B[0].size());
  rep(r,A.H)rep(c,B[0].size()) {
    R[r][c] = (A[r]&revB[c]).count()&1;
  }
  return R;
}

BitMatrix pow(BitMatrix& A, ll n) {
  BitMatrix R(A.size(), A.size());
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

  ll k, m;
  cin >> k >> m;
  vector<ull> a(k);
  vector<ull> c(k);
  rep(i,k) {
    cin >> a[i];
  }
  rep(i,k) {
    cin >> c[i];
  }

  ull ans = 0;
  rep(i,32) {
    BitMatrix A(k, k);
    rep(j,k) { A[0][j] = (c[j]>>i)&1; }
    rep(j,k-1) { A[j+1][j] = 1; }
    BitMatrix B = pow(A, m-k);

    ull now = 0;
    rep(j,k) {
      now ^= B[0][j] & ((a[k-1-j]>>i)&1);
    }
    ans |= now<<i;
  }
  cout << ans <<endl;
}
