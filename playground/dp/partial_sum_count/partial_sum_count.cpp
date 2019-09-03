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

const int INF = 1e9;
const int64_t MOD = 1000000009;

int dp[123][12345];

int main(int argc, char** argv) {
  int N, A;
  cin >> N >> A;
  vector<int> a(N);
  rep(i, N) {
    cin >> a[i];
  }

  dp[0][0] = 1;
  rep(i, N) {
    rep(j, A + 1) {
      if (j >= a[i]) {
        dp[i+1][j] = dp[i][j] + dp[i][j-a[i]];
      } else {
        dp[i+1][j] = dp[i][j];
      }
      dp[i+1][j] %= MOD;
    }
  }

  cout << dp[N][A] << endl;
}

// cf. https://qiita.com/drken/items/a5e6fe22863b7992efdb
