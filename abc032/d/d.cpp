// ref. https://qiita.com/e869120/items/acba3dd8649d913102b5

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

  ll n, W;
  cin >> n >> W;
  vector<ll> v(n), w(n);
  rep(i,n) {
    cin >> v[i] >> w[i];
  }
  ll n2 = n/2;
  ll remain = n-n2;

  vector<map<ll, ll>> dp2(2);
  vector<ll> size = { n2, remain };

  rep(k,2) {
    map<ll, ll>& dp = dp2[k]; // weight=>max value
    ll nn = size[k]; // current size

    rep(i,1ll<<nn) {
      ll nw = 0; // current weight
      ll nv = 0; // current value
      rep(j,nn) {
        if((i>>j)&1) {
          nw += w[j];
          nv += v[j];
        }
      }
      chmax(dp[nw], nv);
    }
    reverse(all(w));
    reverse(all(v));
  }
  // printmap(dp2[0]);

  ll pre = 0;
  map<ll,ll> smp; // s[w] .. muximum value where weight is equal or lower than w.
  for (auto& p : dp2[0]) {
    ll nw = p.first;
    ll nv = p.second;
    smp[nw] = max(pre, nv);
    pre = smp[nw];
  }
  // printmap(smp);

  ll ans = 0;
  for (auto& p : dp2[1]) {
    ll nw = p.first;
    ll nv = p.second;
    // Here, we want to know the maximum value where w0 + nw <= W.
    // <=> w0 <= W-nw.
    auto it = smp.upper_bound(W-nw);
    if (it == smp.begin()) { continue; }
    chmax(ans, nv + prev(it)->second);
  }
  cout << ans << endl;
}
