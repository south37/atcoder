// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2530
// http://drken1215.hatenablog.com/entry/2019/03/20/164100

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string.h>

using namespace std;

#define COUT(x) cout << #x << " = " << (x) << " (L" << __LINE__ << ")" << endl

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

int gcd(int a, int b) {
  if (a < b) { swap(a, b); }
  if (b == 0) { return a; }
  return gcd(b, a % b);
}

bool prime(int n) {
  for (int i = 2; i <= sqrt(n); ++i) {
    if (n % i == 0) { return false; }
  }
  return n != 1;
}

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }

const ll INF = 1e9;
const ll MOD = 1000000009;  // 1e9 + 9

ll powmod(ll x, ll y) {
  ll r = 1;
  while (y) {
    if (y & 1) {
      r = r * x % MOD;
    }
    x = x * x % MOD;
    y >>= 1;
  }
  return r;
}

const int COM_MAX = 500010;
ll fac[COM_MAX], facinv[COM_MAX], inv[COM_MAX];
void COMinit() {
  fac[0] = fac[1] = 1;
  facinv[0] = facinv[1] = 1;
  inv[1] = 1;
  for(int i = 2; i < COM_MAX; ++i) {
    fac[i] = fac[i-1] * i % MOD;
    inv[i] = MOD - inv[MOD%i] * (MOD / i) % MOD;
    facinv[i] = facinv[i-1] * inv[i] % MOD;
  }
}

ll COM(ll n, ll k) {
  return (fac[n] * facinv[k] % MOD) * facinv[n-k] % MOD;
}

ll PERM(ll n, ll k) {
  return (fac[n] * facinv[k] % MOD);
}

const int MAX_ROW = 3010; // To be set appropriately.
const int MAX_COL = 3010; // To be set appropriately.

class BitMatrix {
public:
  BitMatrix(int m = 1, int n = 1) : H(m), W(n) {}
  inline bitset<MAX_COL>& operator [] (int i) { return val[i]; }

  int H, W;

private:
  bitset<MAX_COL> val[MAX_ROW];
};

ostream& operator << (ostream& s, BitMatrix A) {
  s << endl;
  rep(i, A.H) {
    rep(j, A.W) {
      s << A[i][j] << ", ";
    }
    s << endl;
  }
  return s;
}

int GaussJordan(BitMatrix &A, bool is_extended = false) {
  int rank = 0;
  rep(col, A.W) {
    if (is_extended && col == A.W - 1) { break; }
    int pivot = -1;
    for (int row = rank; row < A.H; ++row) {
      if (A[row][col]) {
        pivot = row;
        break;
      }
    }
    if (pivot == -1) continue;
    swap(A[pivot], A[rank]);
    rep(row, A.H) {
      if (row != rank && A[row][col]) {
        A[row] ^= A[rank];
      }
    }
    ++rank;
  }
  return rank;
}

int linear_equation(BitMatrix A, vector<int> b, vector<int> &res) {
  int m = A.H, n = A.W;
  BitMatrix M(m, n + 1);
  rep(i, m) {
    rep(j, n) {
      M[i][j] = A[i][j];
    }
    M[i][n] = b[i];
  }
  int rank = GaussJordan(M, true);

  // check if it has no solution
  for (int row = rank; row < m; ++row) {
    if (M[row][n]) { return -1; }
  }

  // answer
  res.assign(n, 0);
  rep(i, rank) {
    res[i] = M[i][n];
  }
  return rank;
}

const int dx[8] = {1, 0, -1, 0, 1, -1, 1, -1};
const int dy[8] = {0, 1, 0, -1, 1, -1, -1, 1};

int main(int argc, char** argv) {
  int R, C;
  cin >> R >> C;
  BitMatrix A(R*C, R*C);
  vector<int> b(R*C);
  rep(i, R) {
    rep(j, C) {
      cin >> b[i*C + j];
    }
  }

  rep(i, R) {
    rep(j, C) {
      int c = i*C + j;
      A[c][c] = 1;
      rep(k, 8) {
        for (int l = 1; l < 50; ++l) {
          int ni = i + dx[k]*l, nj = j + dy[k]*l;
          if (ni < 0 || ni >= R || nj < 0 || nj >= C) { break; }
          A[ni*C+nj][c] = 1;
        }
      }
    }
  }

  vector<int> res;
  int rank = linear_equation(A, b, res);
  // COUT(rank);
  if (rank == -1) {
    cout << 0 << endl;
  } else {
    cout << powmod(2LL, R*C - rank) << endl;
  }
}
