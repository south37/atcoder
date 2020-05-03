// https://github.com/south37/atcoder/blob/master/template.cpp
// http://drken1215.hatenablog.com/entry/2019/03/20/174600

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string.h>

using namespace std;

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

int dx[] = { 1, -1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

// BitMatrix.
const ll MAX_ROW = 100; // To be set appropriately.
const ll MAX_COL = 100010; // To be set appropriately.

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
    rep(j, A.W) { s << A[i][j] << ", "; }
    s << endl;
  }
  return s;
}

// GaussJordan
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

int main(int argc, char** argv) {
  int N;
  cin >> N;
  vector<ll> a(N);
  rep(i, N) {
    cin >> a[i];
  }

  const int DIGIT = 61;
  BitMatrix A(DIGIT, N);
  rep(d, DIGIT) {
    rep(i, N) {
      if (a[i] & (1LL << d)) {
        A[d][i] = 1;
      }
    }
  }

  int rank = GaussJordan(A);
  cout << (1LL << rank) << endl;
}
