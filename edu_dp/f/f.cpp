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

const ll MAX_N = 3005;

// dp[i][j] .. longest common substring in [0,i) and [0,j)
ll dp[MAX_N][MAX_N];

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  string s;
  string t;
  cin >> s;
  cin >> t;
  ll n = s.size();
  ll m = t.size();
  rep(i, n) rep(j, m) {
    if (s[i] == t[j]) {
      chmax(dp[i+1][j+1], dp[i][j]+1);
    } else {
      chmax(dp[i+1][j+1], dp[i+1][j]);
      chmax(dp[i+1][j+1], dp[i][j+1]);
    }
  }
  string ans;
  ll i = n;
  ll j = m;
  while (i > 0 && j > 0) {
    if (dp[i][j] == dp[i-1][j]) {
      --i;
    } else if (dp[i][j] == dp[i][j-1]) {
      --j;
    } else { // Here, s[i-1] == t[j-1]
      ans += s[i-1];
      --i;
      --j;
    }
  }
  reverse(all(ans));

  rep(i, ans.size()) {
    cout << ans[i];
  }
  cout << endl;
}
