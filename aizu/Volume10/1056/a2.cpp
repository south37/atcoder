// https://respect2d.hatenadiary.org/entry/20110209/1297332247

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

const ll MAX_X = 15;
const ll MAX_N = 100005;
#define MAX_X 15
#define MAX_N 100005

// dp[i][j] .. probability for using [0,i) and succeeds j times in a row.
double dp[MAX_N][MAX_X];
double per[MAX_X];
double ans[MAX_N];

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  cout << setprecision(10) << fixed;

  rep(i,MAX_X) {
    per[i] = pow(0.5,i);
  }
  dp[0][0] = 1.0;

  double sum = 0;
  rep(i,MAX_N) {
    rep(j,MAX_X) {
      if(dp[i][j] > 0) {
        sum += dp[i][j] * per[j];

        dp[i+1][0]   += dp[i][j] * (1-per[j]); // lose
        dp[i+1][j+1] += dp[i][j] * per[j];     // win
      }
    }

    ans[i] = sum;
  }

  while (true) {
    ll n;
    cin >> n;
    if (n == 0) { break; }
    cout << ans[n-1] << endl;
  }
}
