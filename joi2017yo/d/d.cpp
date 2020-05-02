// ref. https://www.ioi-jp.org/joi/2016/2017-yo/2017-yo-t4/review/2017-yo-t4-review.html

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

const ll N = 100000 + 5;
const ll M = 20;

ll cnt[M]; // cnt[k] .. count of k.
ll s[M][N]; // s[k][i] .. cummulative sum of [0,i) at k.
vector<ll> dp; // dp[i] .. i is state bit , min cost at i.

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n, m;
  cin >> n >> m;

  // initilization
  dp.assign(1ll<<m, INF);

  vector<ll> a(n);
  rep(i,n) {
    cin >> a[i];
    --a[i]; // 0-indexed
    ++cnt[a[i]];
  }

  rep(i,n) {
    rep(k,m) {
      s[k][i+1] = s[k][i] + (k == a[i] ? 1 : 0);
    }
  }

  dp[0] = 0;
  rep(i,1ll<<m) {
    ll l = 0;
    rep(j,m) {
      if (i&(1ll<<j)) { l += cnt[j]; }
    }
    rep(j,m) {
      if (!(i&(1ll<<j))) { // j is not in i.
        ll r = l + cnt[j];
        // Here, we consider [l, r)
        ll now = s[j][r] - s[j][l]; // sum of [l, r)
        ll diff = cnt[j] - now;
        chmin(dp[i|(1ll<<j)], dp[i] + diff);
      }
    }
  }
  // printvec(dp);

  cout << dp[(1ll<<m)-1] << endl;
}
