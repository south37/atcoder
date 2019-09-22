#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>
#include <string.h>

using namespace std;

#define COUT(x) cout << #x << " = " << (x) << " (L" << __LINE__ << ")" << endl

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

int dx[] = { 1, -1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };

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

class UnionFind {
public:
  UnionFind(int size) : par(size, -1) {}

  bool same(int x, int y) {
    return root(x) == root(y);
  }
  void unite(int x, int y) {
    x = root(x); y = root(y);
    if (x == y) return;
    if (x > y) { swap(x, y); }
    // here, x < y
    par[y] = x;
  }
  int root(int x) {
    if (par[x] < 0) {
      return x;
    } else {
      return par[x] = root(par[x]);
    }
  }

private:
  vector<int> par;
};

int main(int argc, char** argv) {
  ll N, M, Q;
  cin >> N >> M >> Q;

  UnionFind tree(N);
  vector<P> edges; // different edges.
  rep(i, Q) {
    ll A, B, C;
    cin >> A >> B >> C;
    if (C == 0) {
      tree.unite(A, B);
    } else {
      edges.emplace_back(A, B);
    }
  }

  if (M == N - 1) { // G must be a tree.
    if (edges.size() == 0) {
      cout << "Yes" << endl;
      return 0;
    } else {
      cout << "No" << endl;
      return 0;
    }
  }

  // Check different edges
  for (auto e : edges) {
    if (tree.same(e.first, e.second)) {
      cout << "No" << endl;
      return 0;
    }
  }

  set<int> st;
  rep(i, N) {
    int r = tree.root(i);
    st.insert(r);
  }
  ll K = st.size(); // the number of connected components.

  // H must be lower than or equals to (N-K) + K*(K-1)/2 = N + K(K-3)/2
  if (M <= N + K * (K - 3) / 2) {
    cout << "Yes" << endl;
  } else {
    cout << "No" << endl;
  }
}
