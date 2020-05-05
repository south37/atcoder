// problem: https://atcoder.jp/contests/dp/tasks/dp_w
// ref. https://www.hamayanhamayan.com/entry/2019/01/12/153435

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

// Lazy SegmentTree.
// NV must be power of 2. (e.g. 1ll<<18 ~= 2.6e5)
template<class V, int NV>
struct LazySegTree { // [L,R)
  vector<V> dat, lazy;
  LazySegTree() {
    dat.resize(NV * 2, def); lazy.resize(NV * 2, ldef);
  }
  void update(int a, int b, V v) {
    update(a, b, v, 0, 0, NV);
  }
  V get(int a, int b) {
    return get(a, b, 0, 0, NV);
  }
  void update(int a, int b, V v, int k, int l, int r) {
    push(k, l, r);
    if (r <= a || b <= l) { return; }
    if (a <= l && r <= b) {
      setLazy(k, v);
      push(k, l, r);
    } else {
      update(a, b, v, k * 2 + 1, l, (l + r) / 2);
      update(a, b, v, k * 2 + 2, (l + r) / 2, r);
      dat[k] = comp(dat[k * 2 + 1], dat[k * 2 + 2]);
    }
  }
  V get(int a, int b, int k, int l, int r) {
    push(k, l, r);
    if (r <= a || b <= l) { return def; } // TODO: Here, we should return INF when we need min.
    if (a <= l && r <= b) { return dat[k]; }
    auto x = get(a, b, k * 2 + 1, l, (l + r) / 2);
    auto y = get(a, b, k * 2 + 2, (l + r) / 2, r);
    return comp(x, y);
  }
  // ---- Template ---------------------------------------------------------------------------------

  // add, max
  const V def = 0, ldef = 0;
  V comp(V l, V r) { return max(l, r); } // max
  void setLazy(int i, V v) { lazy[i] += v; } // add
  void push(int k, int l, int r) {
    if (lazy[k] != ldef) { // check the update of lazy
      dat[k] += lazy[k]; // add. Use "dat[k] += lazy[k] * (r-l)" when we need "sum".
      if (r - l > 1) { setLazy(k * 2 + 1, lazy[k]); setLazy(k * 2 + 2, lazy[k]); }
      lazy[k] = ldef;
    }
  }
};

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n, m;
  cin >> n >> m;
  vector<vector<pair<ll, ll>>> R(n); // R[r] .. pair of <l, a>
  rep(iter, m) {
    ll l, r, a;
    cin >> l >> r >> a;
    --l; --r;
    R[r].emplace_back(l, a);
  }

  LazySegTree<ll, 1ll<<18> dp;
  rep(r, n) {
    ll now = dp.get(0, r); // maximum in [0, r)
    dp.update(r, r+1, now); // add now to r
    for (auto& p : R[r]) {
      ll l, a;
      tie(l,a) = p;
      dp.update(l, r+1, a); // add a to [l, r]
    }
  }
  ll ans = dp.get(0, n); // maximum in [0, n)
  cout << ans << endl;
}
