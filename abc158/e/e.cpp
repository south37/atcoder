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

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n, p;
  cin >> n >> p;
  string s;
  cin >> s;
  // Here, we should do digit dp
  vector<vector<ll>> dp(n+1, vector<ll>(10)); // count of [0, i) for each digit.
  // initialize
  rep(i, 10) {
    if ((i % p) == 0) {
      dp[0][i] = 1;
    }
  }
  rep(i, n) {
    // Here, dp[i+1][k] is defined from dp[i][l].
    // if (dp[i][l] * 10 + k) % P == 0, then we should add it.
    rep(k, 10) {
      rep(l, 10) {
        if (((dp[i][l] * 10 + k) % p) == 0) {
          dp[i+1][k] *= dp[i][l];
        }
      }
    }
  }

  ll ans = 0;
  rep(i, 10) {
    ans += dp[n][i];
  }
  cout << ans << endl;
}
