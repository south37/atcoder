#include <iostream>

using namespace std;

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
  for (i = 0; i < n; ++i) {
    int c;
    if (s[i] == '?') {
      c = -1;
    } else {
      c = s[i] - '0';
    }

    for (j = 0; j < 10; ++j) {
      if ((c != -1) && (c != j)) continue;
      for (k = 0; k < 13; ++k) {
        dp[i + 1][(k * 10 + j) % 13] += dp[i][k];
      }
    }
    for (j = 0; j < 13; ++j) dp[i + 1][j] %= MOD;
  }
  res = dp[n][5];

  cout << res << endl;
  return 0;
}
