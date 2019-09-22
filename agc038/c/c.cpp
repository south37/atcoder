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

const ll INF = 1e9;
const ll MOD = 998244353;

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

const int COM_MAX = 1000100;
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

#define MAX_A 1000100

int main(int argc, char** argv) {
  int N;
  cin >> N;
  vector<ll> A(N);
  rep(i, N) {
    cin >> A[i];
  }

  COMinit();

  // sigma_d/i w[d] = 1/i
  vector<ll> w(MAX_A);
  for (ll i = 1; i < MAX_A; ++i) {
    w[i] += inv[i];
    if (w[i] < 0) {
      w[i] = w[i] % MOD + MOD; // w[i] >= 0
    }
    for (ll j = 2; i * j < MAX_A; ++j) {
      w[i*j] -= w[i];
    }
  }

  vector<ll> freq(MAX_A); // frequency of each A[i].
  rep(i, N) {
    ++freq[A[i]];
  }

  vector<ll> sumA(MAX_A);  // sumA[d] has the summension of A[i] (A[i] is the multiple of d).
  vector<ll> sumA2(MAX_A); // sumA2[d] has the summension of A[i] ** 2 (A[i] is the multiple of d).

  ll res = 0;
  for (ll i = 1; i < MAX_A; ++i) {
    for (ll j = 1; i * j < MAX_A; ++j) {
      ll a = i * j;
      sumA[i] += (a * freq[a]) % MOD;
      sumA[i] %= MOD;
      sumA2[i] += ((a * a % MOD) * freq[a]) % MOD;
      sumA2[i] %= MOD;
    }

    // For Debug
    // cout << sumA[i] << " -* " << sumA2[i] << "*" << w[i] << endl;
    // cout << (((sumA[i] * sumA[i] - sumA2[i]) % MOD) * w[i] % MOD) * inv[2] % MOD << endl;

    // (sumA[d] ** 2 - sumA2[d]) / 2 = summension of A[i]*A[j] (A[i], A[j] is the multiple of d, i < j)
    res += (((((sumA[i] * sumA[i] - sumA2[i]) % MOD) * w[i]) % MOD) * inv[2]) % MOD;
    res %= MOD;
    if (res < 0) {
      res = res % MOD + MOD; // res >= 0
    }
  }
  cout << res << endl;
}
