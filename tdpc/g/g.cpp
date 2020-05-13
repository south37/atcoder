// ref. http://mayokoex.hatenablog.com/entry/2016/03/30/001735

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
  ll n = s.size();
  ull K;
  cin >> K;
  vector<int> edge(26,-1);
  vector<vector<int>> g(n+1);
  for (int i = n; i > 0; --i) {
    g[i] = edge; // copy
    edge[s[i-1]-'a'] = i; // 1-indexed
  }
  g[0] = edge;

  // dp[i] .. number of cases using [i,n]. 1-indexed
  vector<ull> dp(n+1);
  for (int i = n; i >= 0; --i) {
    dp[i] = (i>0); // include itself if i > 0.
    rep(j,26) {
      int to = g[i][j];
      if (to != -1) {
        dp[i] += dp[to];
        chmin(dp[i], K+1);
      }
    }
  }
  if (dp[0] < K) {
    // We can not reach to K
    cout << "Eel" << endl;
  } else {
    string ans;
    int now = 0; // current position
    ull k = 0;
    while (k < K) {
      rep(j,26) {
        int to = g[now][j];
        if (to == -1) { continue; }
        if (k+dp[to] < K) { // Here, proceed to next character
          k += dp[to];
        } else {
          ++k; // add single character case.
          now = to;
          ans += (char)('a'+j);
          break; // start from next now.
        }
      }
    }
    cout << ans << endl;
  }
}
