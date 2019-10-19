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

int dp[1234][1234]; // dp[i+1][j+1] is the longuest common subsequence of s[0..i] and t[0..j].

int main(int argc, char** argv) {
  string S, T;
  cin >> S;
  cin >> T;

  int s_len = S.size();
  S += " "; // dummy
  int t_len = T.size();
  T += " "; // dummy
  rep(i, s_len + 1) {
    rep(j, t_len + 1) {
      chmax(dp[i+1][j], dp[i][j]);
      chmax(dp[i][j+1], dp[i][j]);
      if (S[i] == T[j]) {
        chmax(dp[i+1][j+1], dp[i][j] + 1);
      }
    }
  }

  cout << dp[s_len][t_len] << endl;
}
