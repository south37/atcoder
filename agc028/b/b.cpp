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

// Mod int
// cf. https://www.youtube.com/watch?v=1Z6ofKN03_Y
struct mint {
  ll x;
  mint(ll x = 0) : x((x + MOD) % MOD) {}
  mint& operator+= (const mint a) {
    if ((x += a.x) >= MOD) x %= MOD;
    return *this;
  }
  mint operator+ (const mint a) const {
    mint res(*this);
    return res += a;
  }
  mint& operator-= (const mint a) {
    if ((x += MOD - a.x) >= MOD) x %= MOD;
    return *this;
  }
  mint operator- (const mint a) const {
    mint res(*this);
    return res -= a;
  }
  mint& operator*= (const mint a) {
    (x *= a.x) %= MOD;
    return *this;
  }
  mint operator* (const mint a) const {
    mint res(*this);
    return res *= a;
  }
  mint pow(ll t) const {
    if (!t) { return 1; }
    mint a = pow(t >> 1);
    a *= a;
    if (t & 1) a *= *this;
    return a;
  }

  // for prime mod
  mint inv() const {
    return pow(MOD-2);
  }
  mint& operator/= (const mint a) {
    return (*this) *= a.inv();
  }
  mint operator/ (const mint a) const {
    mint res(*this);
    return res /= a;
  }
};

int main(int argc, char** argv) {
  int N;
  cin >> N;
  vector<ll> A(N);
  rep(i, N) {
    cin >> A[i];
  }
  vector<mint> inv(N + 1);
  for (int i = 1; i <= N; ++i) {
    inv[i] = mint(i).inv();
  }
  vector<mint> suminv(N + 1); // suminv[n] = 1/1 + 1/2 + ... + 1/n.
  suminv[0] = 1; // dummy
  suminv[1] = 1;
  for (int i = 2; i <= N; ++i) {
    suminv[i] = suminv[i-1] + inv[i];
  }

  // we want to calculate the w[j]. w[j] = sum_i p(i,j). p(i,j) = 1/(abs(j-i) + 1)
  vector<mint> w(N);
  rep(j, N) {
    // If j is 2, the left is (1/3 + 1/2). right is (1/2 + 1/3 + ... 1/(N - 1 - j + 1)) = (1/2 + 1/3 + ... + 1/(N-j)). self is 1.
    if (j > 0) {
      w[j] += suminv[j+1] - 1;
    }
    if (j < N-1) {
      w[j] += suminv[N-j] - 1;
    }
    w[j] += 1;
  }

  mint ans(0);
  rep(i, N) {
    ans += w[i] * A[i];
  }
  // ans * N!
  rep(i, N) {
    ans *= i + 1;
  }

  cout << ans.x << endl;
}
