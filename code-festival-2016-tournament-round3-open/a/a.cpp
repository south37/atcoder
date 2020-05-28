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

const ll INF = 1e15;
const ll MOD = 1000000007;  // 1e9 + 7

// SlideMin
// res[i] .. min value in [i-m+1,i]
template<typename T>
vector<T> slide_min(const vector<T> &v, int k)
{
  deque< int > deq;
  vector< T > ret;
  for(int i = 0; i < v.size(); i++) {
    while(!deq.empty() && v[deq.back()] >= v[i]) {
      deq.pop_back();
    }
    deq.push_back(i);
    if(i - k + 1 >= 0) {
      ret.emplace_back(v[deq.front()]);
      if(deq.front() == i - k + 1) deq.pop_front();
    }
  }
  return ret;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n,m,k;
  cin >> n >> m >> k;
  vector<ll> a(n);
  rep(i,n) {
    cin >> a[i];
  }
  // dp[i][j] .. maximum value when consider element j as position i.
  // dp[i][j] = i*a[j] + max_k dp[i-1][k] (j-M <= k <= j-1)
  vector<vector<ll>> dp(k,vector<ll>(n));
  rep(i,n) {
    dp[0][i] = a[i];
  }

  for (int i = 1; i < k; ++i) { // at position j. 0-indexed
    vector<ll> dp2(n+m-1, INF); // dp2[j+m-1] .. dp[i-1][j]. dp2 contains m-1 elements as offset.
    rep(j,n) {
      dp2[j+m-1] = -dp[i-1][j];  // minus value of dp[j-1] for calculating max value
    }
    vector<ll> p = slide_min(dp2, m); // p[i] .. min value of dp2 in [i-m+1, i]
    rep(j,n) {
      if (j < i) { continue; } // j must be equal or larger than i.
      chmax(dp[i][j], (i+1)*a[j] - p[j-1]);
    }
  }

  ll ans = 0;
  rep(i,n) {
    chmax(ans, dp[k-1][i]);
  }
  cout << ans << endl;
}
