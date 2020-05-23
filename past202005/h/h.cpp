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

const ll INF = 1e15;
const ll MOD = 1000000007;  // 1e9 + 7

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n,l;
  cin >> n >> l;
  vector<bool> isObj(l+1);
  rep(i,n) {
    ll x;
    cin >> x;
    isObj[x] = true;
  }
  // printvec(isObj);

  ll t1,t2,t3;
  cin >> t1 >> t2 >> t3;

  vector<ll> dp(l+1,INF);
  dp[0] = 0;
  for (ll i = 1; i <= l; ++i) {
    ll w = 0;
    if (isObj[i]) {
      w += t3;
    }
    // 1.
    chmin(dp[i], dp[i-1] + t1 + w);
    // 2.
    if (i-2 >= 0) {
      chmin(dp[i], dp[i-2] + t1 + t2 + w);
    }
    // 3.
    if (i-4 >= 0) {
      chmin(dp[i], dp[i-4] + t1 + 3*t2 + w);
    }
  }
  cout << dp[l] << endl;
}
