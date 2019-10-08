// Base: https://atcoder.jp/contests/agc039/submissions/7898920

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

vector<mint> cnt;

int main(int argc, char** argv) {
  ll N;
  cin >> N;
  string S;
  cin >> S;

  ll N2 = N * 2;
  cnt.resize(N2 + 1);

  // dividers such as (N2 % k) == 0 and (N2 / k) % 2 == 1 (odd).
  for (ll k = 1; k <= N2; ++k) {
    if (N2 % k == 0 && (N2 / k) % 2 == 1) {
      ll t = k / 2;  // k is even.

      // 1. calculate the count from prefix (below S[0..t-1]).
      {
        mint calc(0);
        // calc is the bit representation of S[0..t-1]. e.g. if t=3 and S[0..2] is 101, then calc is 5. This is 6 (from 0 to 5) - 1 (5).
        rep(i, t) {
          calc *= 2;
          if (S[i] == '1') {
            calc += 1;
          }
        }
        cnt[k] += calc;
      }
      // 2. calculate the count from S[0..t-1]S^[0..t-1]....S^[0..t-1]. The prefix is same with S[0..t-1].
      {
        string x1; // The prefix of S.
        string x2; // The swapped prefix of S (0 <-> 1).
        rep(i, t) {
          x1 += S[i];
          x2 += '0' + ('1' - S[i]);
        }
        string comp; // A concatenated string.
        rep(i, N / t) {
          if (i % 2 == 0) {
            comp += x1;
          } else {
            comp += x2;
          }
        }
        // Here, the length of comp is the same with S.
        if (comp <= S) { // comp is smaller than S in lexical order.
          cnt[k] += 1;
        }
      }

      // Calculate cnt with inclusion-exclusion principle.
      for(int i = k * 2; i <= N2; i += k) {
        cnt[i] -= cnt[k];
      }
    }
  }

  mint ans(0);
  for (int k = 1; k <= N2; ++k) {
    if (N2 % k == 0 && (N2 / k) % 2 == 1) {
      ans += cnt[k] * k; // The cycle is k, so k is added for each form.
    }
  }
  cout << ans.x << endl;
}
