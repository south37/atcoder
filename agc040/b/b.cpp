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
  for (int i = 0; i < tree.size(); ++i) {
    cout << i + 1 << ": ";
    printvec(tree[i]);
  }
}
template<class T, class U> void printmap(const map<T, U>& mp) {
  for (auto x : mp) { cout << x.first << "=>" << x.second << endl; }
}

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }

#define rep(i, n) for(ll i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e12;
const ll MOD = 1000000007;  // 1e9 + 7

int main(int argc, char** argv) {
  ll N;
  cin >> N;
  vector<P> lr; // [L, R)
  ll mx = -1; // max of l
  ll mn = INF; // min of r
  rep(i, N) {
    ll l, r;
    cin >> l >> r;
    ++r;
    lr.emplace_back(l, r);
    chmax(mx, l);
    chmin(mn, r);
  }

  ll ans = 0;

  // Check "[mx, mn) + 1 problem" case
  for (auto x : lr) {
    chmax(ans, max(0LL, mn-mx) + (x.second - x.first));
  }

  // Check "[mx, r) + [l, mn)" case
  vector<P> t;
  rep(i, N) {
    ll a = max(0LL, mn-lr[i].first);
    ll b = max(0LL, lr[i].second-mx);
    t.emplace_back(b, -a); // to sort by (b, -a). Increasing by b, decreasing by a.
  }
  sort(all(t));

  ll c = INF; // the min of a in front elements of t.
  rep(i, N) {
    ll a, b;
    tie(b, a) = t[i];
    a = -a;
    if (i > 0) {
      chmax(ans, c+b);
    }
    chmin(c, a);
  }
  cout << ans << endl;
}
