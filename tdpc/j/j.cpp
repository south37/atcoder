// ref. https://suikaba.hatenablog.com/entry/2017/08/22/135124

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

const double eps = 1e-9;

ll n;
// idx[i] .. true if effective, false if not.
vector<bool> idx(16);
// dp[s] .. expected value at state s. last state is 0.
vector<double> dp(1ll<<16,-1);

double rec(ll s) {
  if (__builtin_popcountll(s) == n) { // all is ok
    return 0;
  }
  if (dp[s] >= 0) { return dp[s]; }

  double res = INF;
  for (ll i = 1; i <= 14; ++i) { // loop in [1,14]
    double self = 1;
    double right = 0;
    for (ll j = i-1; j <= i+1; ++j) {
      if (!idx[j] || (s&(1ll<<j))) { // "not effective" or "already visited".
        right += 1.0/3;
        self -= 1.0/3;
      } else {
        right += (rec(s|(1ll<<j)) + 1)/3;
      }
    }
    if (abs(self) < eps) { // self is 0. invalid.
      continue;
    }
    double now = right / self;
    chmin(res, now);
    // cout << "self: " << self << endl;
    // cout << "right: " << right << endl;
    // cout << "now: " << now << endl;
  }
  // cout << "s: " << s << endl;
  // cout << "res: " << res << endl;
  return dp[s] = res;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  cout << setprecision(10) << fixed;

  cin >> n;
  rep(i,n) {
    ll x;
    cin >> x;
    idx[x] = true;
  }
  // printvec(idx);
  cout << rec(0) << endl;
}
