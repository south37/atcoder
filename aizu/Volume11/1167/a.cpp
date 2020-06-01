#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string.h>
#include <set>
#include <stack>

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

const ll MAX_N = 1000005;
// const ll MAX_N = 200;

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  vector<ll> table(205); // table[n] .. n(n+1)(n+2)/6
  rep(i,205) {
    table[i] = i*(i+1)*(i+2)/6;
  }
  // dp[i] .. min count to represent i.
  vector<ll> dp(MAX_N, INF);
  dp[0] = 0;
  dp[1] = 1;
  rep(i,MAX_N) {
    rep(j,205) {
      if (table[j] > i) { break; }
      assert(i-table[j] >= 0);
      chmin(dp[i], dp[i-table[j]] + 1);
    }
  }
  // printvec(dp);

  // dp2[i] .. min count to represent i when using only odd.
  vector<ll> dp2(MAX_N, INF);
  dp2[0] = 0;
  rep(i,MAX_N) {
    rep(j,205) {
      if (table[j] > i) { break; }
      assert(i-table[j] >= 0);
      if (table[j]%2 == 0) { continue; } // even
      chmin(dp2[i], dp2[i-table[j]] + 1);
      // cout << "j:" << j << endl;
      // cout << "table[j]:" << table[j] << endl;
      // cout << "i:" << i << endl;
      // cout << "dp2[i]:" << dp2[i] << endl;
      // cout << "dp2[i-table[i]]:" << dp2[i-table[j]] << endl;
    }
  }

  while (true) {
    ll n;
    cin >> n;
    if (n == 0) { break; }
    cout << dp[n] << " " << dp2[n] << endl;
  }
}
