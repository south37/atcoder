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

// dp[i+1][j][k]
// i .. checked until i.
// j .. the size of undefined numbers.
// k .. score
mint dp[55][55][2605];

// a. select 2 from i. they are connected with each other. a--b
// b. leave 2 numbers undefined. a, b
// c. 1 is selected, 1 is left to be undefined a--x, b (or a, x--b)
// d. select 2 and they are connected with numbers appeared above. (a--x, y--b)

int main(int argc, char** argv) {
  int N, score;
  cin >> N >> score;
  if (score % 2 == 1) { // odd
    cout << 0 << endl;
    return 0;
  }
  dp[0][0][0] = 1;
  rep(i, N) {
    rep(j, i + 1) {
      rep(k, score + 1) {
        { // a
          int nj = j;
          dp[i+1][nj][k+nj*2] += dp[i][j][k];
        }
        { // b
          int nj = j+1;
          dp[i+1][nj][k+nj*2] += dp[i][j][k];
        }
        { // c
          int nj = j;
          mint x = j*2;
          dp[i+1][nj][k+nj*2] += dp[i][j][k] * x;
        }
        if (j >= 1) {
          int nj = j-1;
          mint x = j*j;
          dp[i+1][nj][k+nj*2] += dp[i][j][k] * x;
        }
      }
    }
  }

  cout << dp[N][0][score].x << endl;
}
