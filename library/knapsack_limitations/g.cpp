// ref. https://ei1333.github.io/luzhiled/snippets/dp/knapsack-limitations.html
// ref. https://scrapbox.io/nojima/%E5%80%8B%E6%95%B0%E5%88%B6%E9%99%90%E4%BB%98%E3%81%8D%E3%83%8A%E3%83%83%E3%83%97%E3%82%B5%E3%83%83%E3%82%AF

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

// Knapsack with limitation.
// w[i] .. weight
// m[i] .. limitation of count
// v[i] .. value
// W .. total weight
// NG .. initial value of dp vector
template<typename T, typename Compare = greater<T>>
vector<T> knapsack_limitations(const vector<ll> &w, const vector<ll> &m, const vector<T> &v,
                               const ll& W, const T& NG, const Compare &comp = Compare()) {
  const ll n = (ll)w.size();
  vector<T> dp(W + 1, NG), deqv(W + 1), deq(W + 1);
  dp[0] = T();
  rep(i,n) {
    rep(a,w[i]) {
      ll s = 0, t = 0; // [s,t) is valid range. deqv[s] is used as slide max.
      for (ll j = 0; w[i] * j + a <= W; j++) { // Here, we get slide max of j in [j-m[i],j].
        if (dp[w[i] * j + a] != NG) {
          auto val = dp[w[i] * j + a] - j * v[i]; // value with out contribution of (v[i]*j).
          while(s < t && comp(val, deqv[t - 1])) --t;
          deq[t] = j;      // push
          deqv[t++] = val; // push
        }
        if (s < t) { // [s,t) is not blank
          dp[w[i] * j + a] = deqv[s] + j * v[i];
          if(deq[s] == j - m[i]) ++s;
        }
      }
    }
  }
  return dp;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n,W;
  cin >> n >> W;
  vector<ll> v(n);
  vector<ll> w(n);
  vector<ll> m(n);
  rep(i,n) {
    cin >> v[i] >> w[i] >> m[i];
  }

  vector<ll> dp = knapsack_limitations(w, m, v, W, -1ll);
  ll ans = 0;
  rep(i,W+1) {
    chmax(ans, dp[i]);
  }
  cout << ans << endl;
}
