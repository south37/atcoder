#include <algorithm>
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

  ull rank = 0;
  for (int i = 59; i >= 0; --i) {
    int j;
    for (j = rank; j < N; ++j) {
      if (A[j] & (1LL << i)) { break; }
    }
    if (j == N) { // No match
      continue;
    }
    if (j > rank) {
      A[rank] ^= A[j];  // Set 1 to i-bit of A[rank]
    }

    for (int k = rank + 1; k < N; ++k) {
      A[k] = min(A[k], A[k] ^ A[rank]);  // Set 0 to i-bit of A[k].
    }

    ++rank;
  }

  ull x = 0;
  rep(i, N) {
    x = max(x, x ^ A[i]);
  }

  cout << (x * 2) + allxor << endl;
}
