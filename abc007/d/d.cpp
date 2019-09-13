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

typedef pair<int, int> P;
typedef tuple<int, int, int> triple;
typedef long long ll;

int gcd(int a, int b) {
  if (a < b) { swap(a, b); }
  if (b == 0) { return a; }
  return gcd(b, a % b);
}

bool prime(int n) {
  for (int i = 2; i <= sqrt(n); i++) {
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

ll fac[200010], facinv[200010];  // 200010 is Larger than 1e5 + 1e5.
void cominit() {
  fac[0] = facinv[0] = 1;
  ll c = 1;
  for (int i = 1; i < 200010; ++i) {
    c = c * i % MOD;
    fac[i] = c;
    facinv[i] = powmod(c, MOD-2);
  }
}

ll combination(ll n, ll k) {
  return (fac[n] * facinv[k] % MOD) * facinv[n-k] % MOD;
}

ll permutation(ll n, ll k) {
  return (fac[n] * facinv[k] % MOD);
}

// Digit DP.
ll f(string s) {
  int l = s.size();
  ll dp[20][2][2] = {}; // dp[i][j][k] top i digit, less than s(j), includes 4 or 9(k)
  dp[0][0][0] = 1;
  rep(i, l) {
    int D = s[i] - '0'; // number at s[i];
    rep(j, 2) {
      rep(k, 2) {
        for (int d = 0; d <= (j ? 9 : D); ++d) {
          dp[i+1][j||(d<D)][k||(d==4||d==9)] += dp[i][j][k];
        }
      }
    }
  }
  return dp[l][0][1] + dp[l][1][1];
}

int main(int argc, char** argv) {
  ll A, B;
  cin >> A >> B;

  cout << f(to_string(B)) - f(to_string(A-1)) << endl;
}
