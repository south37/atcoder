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

ll powmod(ll x, ll n) { // like pow(x, n)
  ll r = 1;
  while (n) {
    if (n & 1) {
      r = r * x % MOD;
    }
    x = x * x % MOD;
    n >>= 1;
  }
  return r;
}

// GaussJordan by Matrix(double)
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

template<class T> int GaussJordan(Matrix<T> &A, bool is_extended = false) {
  int m = A.size(), n = A[0].size();
  int rank = 0;
  rep(col, n) {
    if (is_extended && col == n - 1) { break; }
    int pivot = -1;
    int ma = INF; // Find a row with minimum A[row][n-1]
    for (int row = rank; row < m; ++row) {
      if ((A[row][col] == 1) && (A[row][n-1] < ma)) {
        pivot = row;
        ma = A[row][n-1];
      }
    }

    if (pivot == -1) { continue; } // No match
    swap(A[pivot], A[rank]);
    // Now, A[rank][col] = 1
    for (int row = rank + 1; row < m; ++row) {
      if (A[row][col] == 1) {
        rep(col2, n) {
          A[row][col2] -= A[rank][col2];
          A[row][col2] = max<T>(0, A[row][col2]);
        }
      }
    }
    // Now, A[row][col] = 0.0 (for row != rank).
    ++rank;
  }
  return rank;
}

int main(int argc, char** argv) {
  int N, M;
  cin >> N >> M;

  vector<int> a(M);
  vector<int> b(M); // the number of boxes
  vector< vector<int> > c(M);
  rep(i, M) {
    cin >> a[i] >> b[i];
    c[i].resize(b[i]);
    rep(j, b[i]) {
      cin >> c[i][j];
      --c[i][j]; // 0-indexed
    }
  }
  rep(i, M) {
    rep(j, b[i]) {
      cout << c[i][j] << " ";
    }
    cout << endl;
  }

  vector<P> pairs;
  rep(i, M) {
    pairs.emplace_back(a[i], i);
  }
  sort(all(pairs)); // pairs are sorted by a[i];
  rep(i, M) {
    cout << pairs[i].first << ", " << pairs[i].second << endl;
  }

  Matrix<ll> A(M, N+1, 0);
  rep(i, M) {
    P p = pairs[i];
    int cost = p.first;
    int id = p.second;

    rep(j, b[id]) {
      int k = c[id][j];
      A[i][k] = 1;
    }
    A[i][N] = cost;
  }
  cout << A << endl;

  int rank = GaussJordan(A, true);
  cout << A << endl;


  // Do GaussJordan by myself.
  //
  // ull rank = 0;
  // for (int i = 59; i >= 0; --i) {
  //   int j;
  //   for (j = rank; j < N; ++j) {
  //     if (A[j] & (1LL << i)) { break; }
  //   }
  //   if (j == N) { // No match
  //     continue;
  //   }
  //   if (j > rank) {
  //     A[rank] ^= A[j];  // Set 1 to i-bit of A[rank]
  //   }
  //
  //   for (int k = rank + 1; k < N; ++k) {
  //     A[k] = min(A[k], A[k] ^ A[rank]);  // Set 0 to i-bit of A[k].
  //   }
  //
  //   ++rank;
  // }
}
