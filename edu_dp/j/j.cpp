// ref. https://qiita.com/drken/items/03c7db44ccd27820ea0d

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

const ll MAX_N = 305;

ll n;
// i..1, j..2, k..3
// dp[i][j][k] = dp[i][j][k]*(n-i-j-k)/n + dp[i-1][j][k]*i/n + dp[i+1][j-1][k]*j/n + dp[i][j+1][k-1]*k/n + 1
// dp[i][j][k] = (dp[i−1][j][k]*i + dp[i+1][j−1][k]*j + dp[i][j+1][k−1]*k + n)/(i+j+k)
double dp[MAX_N][MAX_N][MAX_N];

double rec(ll i, ll j, ll k) {
  if (dp[i][j][k] >= 0) { return dp[i][j][k]; }
  double res = 0;
  if (i>0) { res += rec(i-1,j,k)*i; }
  if (j>0) { res += rec(i+1,j-1,k)*j; }
  if (k>0) { res += rec(i,j+1,k-1)*k; }
  res += n;
  res /= i+j+k;
  return dp[i][j][k] = res;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  cout << setprecision(10) << fixed;

  cin >> n;
  vector<ll> cnt(4);
  rep(i, n) {
    ll a;
    cin >> a;
    ++cnt[a];
  }
  // initialization
  memset(dp, -1, sizeof(dp));
  dp[0][0][0] = 0.0;

  cout << rec(cnt[1], cnt[2], cnt[3]) << endl;
}
