// ref. https://suikaba.hatenablog.com/entry/2017/08/22/223848

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
#define sz(x) (ll)(x).size()
#define fr first
#define sc second
#define mp make_pair
#define pb push_back
#define eb emplace_back

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;
typedef vector<ll> vl;
typedef vector<P> vp;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  string s;
  cin >> s;
  ull K;
  cin >> K;
  int n = s.size();

  // dp[i] .. number of cases using [i,n).
  vector<ull> dp(n+2);
  vector<vector<int>> g(n+1, vector<int>(26, n+1));
  for (int i = n-1; i >= 0; --i) {
    dp[i+1] = 1;
    rep(j,26) {
      dp[i+1] += dp[g[i+1][j]];
      chmin(dp[i+1], K+1);
    }
    g[i] = g[i+1]; // copy
    g[i][s[i]-'a'] = i+1; // update the latest position of s[i]-'a'.
  }

  ll total = 0;
  rep(i,26) {
    int to = g[0][i];
    total += dp[to];
  }
  if (total < K) { // we can not reach to K
    cout << "Eel" << endl;
    return 0;
  }

  string ans;
  int now = 0;
  while (K>0) {
    rep(i,26) {
      int to = g[now][i];
      if (dp[to] < K) {
        K -= dp[to];
      } else {
        --K; // contribution from single character.
        now = to;
        ans += (char)('a'+i);
        break;
      }
    }
  }
  cout << ans << endl;
}
