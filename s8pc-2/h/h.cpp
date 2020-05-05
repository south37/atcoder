// ref. http://mayokoex.hatenablog.com/entry/2016/04/25/223326

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
  vector<ll> width; // Used only for sum.
  LazySegTree() {
    dat.resize(NV * 2, def); lazy.resize(NV * 2, ldef); width.resize(NV * 2, 1);
    for (ll i = NV-2; i >= 0; --i) {
      width[i] = width[i*2+1] + width[i*2+2];
    }
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

  // xor, sum
  const V def = 0, ldef = 0;
  V comp(V l, V r) { return l + r; } // sum
  void setLazy(int i, V v) { lazy[i] ^= v; } // xor
  void push(int k, int l, int r) {
    if (lazy[k] != ldef) { // check the update of lazy
      dat[k] = r-l-dat[k]; // xor in this range. [l,r)
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

  ll n, q;
  cin >> n >> q;
  LazySegTree<ll, 1ll<<18> dp;
  rep(iter,q) {
    ll q,l,r;
    cin >> q >> l >> r;
    if (q == 1) { // update
      dp.update(l,r,1);
    } else { // query
      cout << dp.get(l,r) << endl;
    }
  }
}
