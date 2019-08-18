#include <iostream>

using namespace std;

#define rep(i, n) for(int i = 0; i < n; ++i)

static const uint64_t MOD = 1000000007LL;

int n;
char s[123456];
uint64_t dp[123456][13];

int main(int argc, char** argv) {
  int i, j, k;
  uint64_t res = 0;

  scanf("%s", s);
  n = strlen(s);

  dp[0][0] = 1;
  rep(i, n) {
    int c;
    if (s[i] == '?') {
      c = -1;
    } else {
      c = s[i] - '0';
    }

    rep(j, 10) {
      if (c != -1 && j != c) {
        // If c is not '?', only the specified number must be summed.
        continue;
      }
      rep(k, 13) {
        dp[i + 1][(k * 10 + j) % 13] += dp[i][k];
      }
    }

    // MOD
    rep(k, 13) {
      dp[i + 1][k] %= MOD;
    }
  }
  res = dp[n][5];

  cout << res << endl;
  return 0;
}
