// ref. https://suikaba.hatenablog.com/entry/2017/08/20/150043

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

string s;
vector<vector<int>> dp;

// maximum length in [l,r)
int rec(int l, int r) {
  if (r-l <= 2) { return 0; } // length must be at least 3.
  if (dp[l][r] >= 0) { return dp[l][r]; }
  int& res = dp[l][r];
  for (int m = l+1; m < r-1; ++m) { // loop in [l+1, r-1)
    int now = rec(l,m)+rec(m,r);
    chmax(res, now);
    if (s[l] == 'i' && s[m] == 'w' && s[r-1] == 'i' && rec(l+1,m) == m-l-1 && rec(m+1,r-1) == r-m-2) {
      res = r-l;
    }
  }
  return res;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  cin >> s;
  int n = s.size();
  dp.assign(n+1, vector<int>(n+1, -1));

  cout << rec(0,n)/3 << endl;
}
