// https://www.geeksforgeeks.org/edit-distance-dp-5/

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

int main(int argc, char** argv) {
  string S, T;
  cin >> S >> T;

  // For Debug
  // cout << S << endl;
  // cout << T << endl;

  int s_len = S.size();
  int t_len = T.size();

  // dp[i][j] .. the distance of s[0, i) and t[0, j)
  vector<vector<int>> dp(s_len+1, vector<int>(t_len+1));

  for (int i = 0; i <= s_len; ++i) {
    for (int j = 0; j <= t_len; ++j) {
      if (i == 0) {
        dp[i][j] = j;
        continue;
      }
      if (j == 0) {
        dp[i][j] = i;
        continue;
      }
      // Here, i > 0 && j > 0
      if (S[i-1] == T[j-1]) {
        dp[i][j] = dp[i-1][j-1];
      } else {
        dp[i][j] = dp[i-1][j-1] + 1; // replace
      }
      dp[i][j] = min(dp[i][j], dp[i][j-1] + 1); // insert
      dp[i][j] = min(dp[i][j], dp[i-1][j] + 1); // remove
    }
  }
  cout << dp[s_len][t_len] << endl;
}

// cf. https://qiita.com/drken/items/a5e6fe22863b7992efdb
