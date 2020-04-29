// ref. https://www.hamayanhamayan.com/entry/2019/01/12/151211

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

  ll n;
  cin >> n;
  vector<vector<ll>> a(n, vector<ll>(n));
  rep(i,n)rep(j,n) {
    cin >> a[i][j];
  }
  vector<ll> s(1ll<<n);
  rep(msk,1ll<<n) {
    rep(i,n)rep(j,i) {
      if ((msk&(1ll<<i)) && (msk&(1ll<<j))) {
        s[msk] += a[i][j];
      }
    }
  }
  vector<ll> dp(1ll<<n);
  // Here, do DP in O(3^n). cf. https://codeforces.com/blog/entry/45223
  rep(msk,1ll<<n) {
    for (ll msk2 = msk; msk2 > 0; msk2 = (msk2-1)&msk) {
      chmax(dp[msk], dp[msk^msk2] + s[msk2]);
    }
  }
  cout << dp[(1ll<<n)-1] << endl;
}
