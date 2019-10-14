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

// dp[i][j] .. the longest common prefix of s[i..-1] and s[j..-1]
// if s[i] != s[j], then dp[i][j] = 0
// if s[i] == s[j], then dp[i][j] = dp[i+1][j+1] + 1
int dp[5010][5010];

int main(int argc, char** argv) {
  int N;
  cin >> N;
  string S;
  cin >> S;

  for (int i = N - 1; i >= 0; --i) {
    for (int j = N - 1; j > i; --j) {
      if (S[i] == S[j]) {
        dp[i][j] = dp[i+1][j+1] + 1;
      } else { // S[i] != S[j]
        dp[i][j] = 0;
      }
    }
  }

  int ans = 0;
  rep(i, N) {
    for (int j = i + 1; j < N; ++j) {
      int lcp = min(dp[i][j], j - i);
      ans = max(ans, lcp);
    }
  }
  cout << ans << endl;
}
