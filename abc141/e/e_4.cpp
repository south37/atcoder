// base: http://drken1215.hatenablog.com/entry/2019/09/16/014600

#include <algorithm>
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

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

typedef long long ll;
typedef pair<int, int> P;
typedef tuple<int, int, int> triple;

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

// RollingHash with mod1 and mod2
struct RollingHash {
  static const int base1 = 1007, base2 = 2009;
  static const int mod1 = 1000000007, mod2 = 1000000009;
  vector<ll> hash1, hash2, power1, power2;

  RollingHash(const string& S) { init(S); }
  void init(const string& S) {
    int n = S.size();
    hash1.resize(n+1);
    hash2.resize(n+1);
    power1.assign(n+1, 1);
    power2.assign(n+1, 1);
    rep(i, n) {
      hash1[i+1] = (hash1[i] * base1 + S[i]) % mod1;
      hash2[i+1] = (hash2[i] * base2 + S[i]) % mod2;
      power1[i+1] = (power1[i] * base1) % mod1;
      power2[i+1] = (power2[i] * base2) % mod2;
    }
  }

  // get hash of S[left:right]
  inline pair<ll, ll> get(int l, int r) const {
    ll res1 = hash1[r] - hash1[l] * power1[r-l] % mod1;
    if (res1 < 0) res1 += mod1;
    ll res2 = hash2[r] - hash2[l] * power2[r-l] % mod2;
    if (res2 < 0) res2 += mod2;
    return {res1, res2};
  }

  // get lcp of S[a:] and T[b:]
  inline int getLCP(int a, int b) const {
    int len = min((int)hash1.size()-a, (int)hash1.size()-b);
    int low = 0, high = len;
    while (high - low > 1) {
      int mid = (low + high) >> 1;
      if (get(a, a+mid) != get(b, b+mid)) high = mid;
      else low = mid;
    }
    return low;
  }
};

int main(int argc, char** argv) {
  int N;
  cin >> N;
  string S;
  cin >> S;

  RollingHash rh(S);

  int ans = 0;
  rep(i, N) {
    for (int j = i + 1; j < N; ++j) {
      int lcp = rh.getLCP(i, j);
      lcp = min(lcp, j - i);
      ans = max(ans, lcp);
    }
  }

  cout << ans << endl;
}
