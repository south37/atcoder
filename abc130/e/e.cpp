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

mint dp0[2005][2005];
mint dp1[2005][2005];

int main(int argc, char** argv) {
  ll N, M;
  cin >> N >> M;
  vector<ll> S(N+1); // S[N] is dummy
  vector<ll> T(M+1); // T[M] is dummy
  rep(i, N) {
    cin >> S[i];
  }
  rep(i, M) {
    cin >> T[i];
  }

  dp0[0][0] = 1;
  rep(i, N+1) rep(j, M+1) {
    dp0[i+1][j] += dp0[i][j]; // i increaes in dp0
    dp1[i][j] += dp0[i][j];
    dp1[i][j+1] += dp1[i][j]; // j increaes in dp1
    if (S[i] == T[j]) {
      dp0[i+1][j+1] += dp1[i][j];
    }
  }

  mint ans = dp1[N][M];
  cout << ans.x << endl;
}
