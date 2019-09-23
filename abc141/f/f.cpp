#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

int dx[] = { 1, -1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> P;
typedef tuple<int, int, int> triple;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

// GaussJordan by BitMatrix
const int MAX_ROW = 100010; // To be set appropriately.
const int MAX_COL = 60; // To be set appropriately.

class BitMatrix {
public:
  BitMatrix(int h = 1, int w = 1) : H(h), W(w) {}
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


int main(int argc, char** argv) {
  int N;
  cin >> N;
  vector<ull> A(N);
  rep(i, N) {
    cin >> A[i];
  }

  ull allxor = 0;
  rep(i, N) {
    allxor ^= A[i];
  }
  // NOTE: leave only significant bits.
  rep(i, N) {
    A[i] &= ~allxor;
  }

  BitMatrix matrix(N, 60);
  rep(i, N) {
    for (int j = 59; j >= 0; --j) { // j represents the bit of A[i]. e.g. The j of 1 in 100 is 2.
      matrix[i][59 - j] = (A[i] >> j) & 1LL;
    }
  }
  int rank = GaussJordan(matrix, false); // rank is not used.

  vector<ull> B(N); // The result of GaussJordan transformation.
  rep(i, N) {
    ull x = 0;
    for (int j = 59; j >= 0; --j) {
      if (matrix[i][59 - j] > 0) {
        x += 1LL << j;
      }
    }
    B[i] = x;
  }

  ull x = 0;
  rep(i, N) {
    x = max(x, x ^ B[i]);
  }

  cout << (x * 2) + allxor << endl;
}
