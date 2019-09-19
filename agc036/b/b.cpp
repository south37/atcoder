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

const ll INF = 1e18;
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

const int MAXN = 200010;
const int MAXA = 200010;

vector<ll> G[MAXA];
ll dob[60][MAXA]; // dob[0][i]: distances from i. dob[k] is doubled by 2**k;

int main(int argc, char** argv) {
  ll N, K;
  cin >> N >> K;
  vector<ll> A(N);
  rep(i, N) {
    cin >> A[i];
    G[A[i]].push_back(i);
  }
  rep(a, MAXA) {
    int n = G[a].size();
    rep(j, n) {
      if (j == n - 1) {
        dob[0][G[a][j]] = (N + G[a][0]) - G[a][j] + 1;
      } else {
        dob[0][G[a][j]] = G[a][j + 1] - G[a][j] + 1;
      }
    }
  }

  rep(k, 59) {
    rep(i, N) {
      if (dob[k][i] == INF) {
        dob[k + 1][i] = INF;
      } else {
        ll tmp = dob[k][i] + dob[k][(i + dob[k][i]) % N];
        dob[k + 1][i] = min(tmp, INF);
      }
    }
  }

  ll t = 0;
  for (int k = 59; k >= 0; --k) {
    if (t + dob[k][t % N] <= N * K) {
      t = t + dob[k][t % N];
    }
  }

  if (t == N * K) { // No more characters.
    cout << endl;
    return 0;
  }

  t %= N;

  while (t < N) {
    if (t + dob[0][t] - 1 > N - 1) { // No more characters same with A[t].
      cout << A[t] << " ";
      ++t;
    } else {
      t = t + dob[0][t];
    }
  }

  return 0;
}
