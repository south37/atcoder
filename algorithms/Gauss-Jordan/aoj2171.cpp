// AOJ 2171 Strange Couple. http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2171
// http://drken1215.hatenablog.com/entry/2019/03/20/000200
// http://drken1215.hatenablog.com/entry/2019/03/20/202800

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <unordered_map>
#include <vector>
#include <iomanip>

using namespace std;

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

int dx[] = { 1, -1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };

typedef long long ll;
typedef pair<ll, ll> P;
typedef tuple<int, int, int> triple;
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
const ll MOD = 1000000007;  // 1e9 + 7

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

const double EPS = 1e-10;

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

template<class T> int GaussJordan(Matrix<T> &A, bool is_extended = false) {
  int m = A.size(), n = A[0].size();
  int rank = 0;
  rep(col, n) {
    if (is_extended && col == n - 1) { break; }
    int pivot = -1;
    T ma = EPS;
    for (int row = rank; row < m; ++row) {
      if (abs(A[row][col]) > ma) {
        ma = abs(A[row][col]);
        pivot = row;
      }
    }

    if (pivot == -1) { continue; } // No match
    swap(A[pivot], A[rank]);
    auto fac = A[rank][col];
    rep(col2, n) {
      A[rank][col2] /= fac;
    }
    // Now, A[rank][col] = 1.0
    rep(row, m) {
      if (row != rank && abs(A[row][col]) > EPS) {
        auto fac = A[row][col];
        rep(col2, n) {
          A[row][col2] -= A[rank][col2] * fac;
        }
      }
    }
    // Now, A[row][col] = 0.0 (for row != rank).
    ++ rank;
  }
  return rank;
}

template<class T> vector<T> linear_equation(Matrix<T> A, vector<T> b) {
  int m = A.size(), n = A[0].size();
  Matrix<T> M(m, n + 1);
  rep(i, m) {
    rep(j, n) {
      M[i][j] = A[i][j];
    }
    M[i][n] = b[i];
  }
  int rank = GaussJordan(M, true);

  // Check the existence of the solution;
  vector<T> res;
  for (int row = rank; row < m; ++row) {
    if (abs(M[row][n]) > EPS) {
      return res;
    }
  }
  res.assign(n, 0);
  rep(i, rank) {
    res[i] = M[i][n];
  }
  return res;
}

int N, s, t;
vector<int> q;
vector< vector<int> > a;

void solve() {
  vector<int> d(N, INF);
  d[t] = 0;
  priority_queue<P, vector<P>, greater<P>> p_q;
  p_q.push(P(0, t));

  while (!p_q.empty()) {
    P p = p_q.top(); p_q.pop();
    int v = p.second;
    if (d[v] < p.first) { continue; } // Already updated.
    rep(i, N) {
      if (a[v][i] == 0) { continue; } // There is no road between v and i.
      if (d[i] > d[v] + a[v][i]) {
        d[i] = d[v] + a[v][i];
        p_q.push(P(d[i], i));
      }
    }
  }

  Matrix<D> A(N, N, 0); vector<D> b(N, 0);
  rep(v, N) { // row (vertical)
    if (v == t) {
      A[v][v] = 1;
      b[v] = 0;
    } else {
      vector<int> neighbour;
      rep(w, N) {
        if (a[v][w] == 0) { continue; } // No road.
        if ((q[v] == 1) && (d[w] + a[v][w] != d[v])) { continue; }
        neighbour.push_back(w);
      }
      int K = neighbour.size();
      for (auto w : neighbour) {
        A[v][w] -= 1;
        b[v] += a[v][w];
      }
      A[v][v] += K;
    }
  }
  auto res = linear_equation(A, b);
  if (res.empty()) {
    cout << "impossible" << endl;
  } else {
    cout << fixed << setprecision(15) << res[s] << endl;
  }
}

int main(int argc, char** argv) {
  while (cin >> N >> s >> t, N) {
    --s, --t;
    q.resize(N);
    rep(i, N) {
      cin >> q[i];
    }
    a.assign(N, vector<int>(N));
    rep(i, N) {
      rep(j, N) {
        cin >> a[i][j];
      }
    }
    solve();
  }
}
