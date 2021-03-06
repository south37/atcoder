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

int dp[123][123456];

int main(int argc, char** argv) {
  int N, K;
  cin >> N >> K;
  vector<int> a(N);
  rep(i, N) {
    cin >> a[i];
  }
  vector<int> m(N);
  rep(i, N) {
    cin >> m[i];
  }

  rep(i, 123) {
    rep(j, 123456) {
      dp[i][j] = -1;
    }
  }
  dp[0][0] = 0;

  rep(i, N) {
    rep(j, K+1) {
      if (dp[i][j] >= 0) {
        dp[i+1][j] = m[i];
      } else if (j < a[i] || dp[i+1][j-a[i]] <= 0) {
        dp[i+1][j] = -1;
      } else {
        dp[i+1][j] = dp[i+1][j-a[i]] - 1;
      }
    }
  }

  if (dp[N][K] >= 0) {
    cout << "YES" << endl;
  } else {
    cout << "NO" << endl;
  }
}
