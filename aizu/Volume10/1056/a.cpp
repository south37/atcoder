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

const double eps = 1e-13;

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  cout << setprecision(10) << fixed;

  // dp[i] .. expected value in i days.
  // dp[i] = sum of p*(1-win)*(k+dp[max(0,n-k-1)])
  vector<double> dp(MAX_N);
  dp[1] = 1.0;

  for (int i = 2; i < MAX_N; ++i) {
    double p = 1, win = 0.5;
    int k = 1;
    while (eps < p && k < i) {
      double lose = p*(1-win); // probability of lose after winning k times.
      dp[i] += lose*(k+dp[0,i-k-1]);
      p *= win;
      win /= 2;
      ++k;
    }
    dp[i] += i*p; // win i times.
  }

  while (true) {
    ll n;
    cin >> n;
    if (n == 0) { break; }
    cout << dp[n] << endl;
  }
}
