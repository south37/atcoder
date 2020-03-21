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

template<class T> void printvec(const vector<T>& v) {
  for (auto x : v) { cout << x << " "; }
  cout << endl;
}
template<class T> void printtree(const vector< vector<T> >& tree) {
  for (long long i = 0; i < tree.size(); ++i) {
    cout << i + 1 << ": "; printvec(tree[i]);
  }
}
template<class T, class U> void printmap(const map<T, U>& mp) {
  for (auto x : mp) { cout << x.first << "=>" << x.second << endl; }
}

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }

#define rep(i, n) for(ll i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()
#define fr first
#define sc second
#define mp make_pair
#define pb push_back

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

int dr[2] = { 1, 0 };
int dc[2] = { 0, 1 };

int revDr[2] = { -1, 0 };
int revDc[2] = { 0, -1 };

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll h, w;
  cin >> h >> w;
  vector<string> maze(h);
  rep(r, h) {
    cin >> maze[r];
  }

  vector<vector<ll>> dp(h, vector<ll>(w, INF));
  if (maze[h-1][w-1] == '#') {
    dp[h-1][w-1] = 1;
  } else {
    dp[h-1][w-1] = 0;
  }
  // We calculate rsult by dp. dp[i][j] .. min black for reach to (h-1,w-1).
  for (int r = h-1; r >= 0; --r) {
    for (int c = w-1; c >= 0; --c) {
      if (r < h-1) { // try bottom
        ll cand = dp[r+1][c];
        if (maze[r][c] == '#' && maze[r+1][c] != '#') {
          cand += 1;
        }
        dp[r][c] = min(dp[r][c], cand);
      }
      if (c < w-1) { // try right
        ll cand = dp[r][c+1];
        if (maze[r][c] == '#' && maze[r][c+1] != '#') {
          cand += 1;
        }
        dp[r][c] = min(dp[r][c], cand);
      }
      cout << "(r,c):" << r<<","<<c<<endl;
      cout << "dp[r][c]:" << dp[r][c] <<endl;
    }
  }

  cout << dp[0][0] << endl;
}
