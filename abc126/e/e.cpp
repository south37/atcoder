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

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

// GaussJordan by BitMatrix
const int MAX_ROW = 100010; // To be set appropriately.
const int MAX_COL = 100010; // To be set appropriately.

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

int GaussJordan(BitMatrix* A, bool is_extended = false) {
  int rank = 0;
  rep(col, (*A).W) {
    if (is_extended && col == (*A).W - 1) { break; }
    int pivot = -1;
    for (int row = rank; row < (*A).H; ++row) {
      if ((*A)[row][col]) {
        pivot = row;
        break;
      }
    }
    if (pivot == -1) continue;
    swap((*A)[pivot], (*A)[rank]);
    rep(row, (*A).H) {
      if (row != rank && (*A)[row][col]) {
        (*A)[row] ^= (*A)[rank];
      }
    }
    ++rank;
  }
  return rank;
}

int linear_equation(BitMatrix* A, vector<int>& b, vector<int> &res) {
  int m = (*A).H, n = (*A).W;
  BitMatrix* M = new BitMatrix(m, n + 1);
  rep(i, m) {
    rep(j, n) {
      (*M)[i][j] = (*A)[i][j];
    }
    (*M)[i][n] = b[i];
  }
  int rank = GaussJordan(M, true);

  // check if it has no solution
  for (int row = rank; row < m; ++row) {
    if ((*M)[row][n]) { return -1; }
  }

  // answer
  res.assign(n, 0);
  rep(i, rank) {
    res[i] = (*M)[i][n];
  }
  return rank;
}

// We want to calculate the count of answers for M equations.
// A[Xi] + A[Yi] = Zi MOD 2
// If Zi is odd, then A[Xi] + A[Yi] is odd (same with even).
//
// This is represented as a matrix. By GaussJordan, we can calculate the count of answers

int main(int argc, char** argv) {
  int N, M;
  cin >> N >> M;

  BitMatrix* matrix = new BitMatrix(M, N);
  vector<int> b(M);

  rep(i, M) {
    int X, Y, Z;
    cin >> X >> Y >> Z;
    --X; --Y; // 0-indexied.
    (*matrix)[i][X] = 1;
    (*matrix)[i][Y] = 1;
    b[i] = Z % 2;
  }
  // rep(i, M) {
  //   rep(j, N) {
  //     cout << (*matrix)[i][j] << " ";
  //   }
  //   cout << endl;
  // }

  vector<int> res;
  int rnk = linear_equation(matrix, b, res);
  cout << N - rnk << endl;
}
