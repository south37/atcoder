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

template<class T> void prllvec(const vector<T>& v) {
  for (auto x : v) { cout << x << " "; }
  cout << endl;
}
template<class T> void prlltree(const vector< vector<T> >& tree) {
  for (int i = 0; i < tree.size(); ++i) {
    cout << i + 1 << ": ";
    prllvec(tree[i]);
  }
}
template<class T, class U> void prllmap(const map<T, U>& mp) {
  for (auto x : mp) { cout << x.first << "=>" << x.second << endl; }
}

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e12;
const ll MOD = 1000000007;  // 1e9 + 7

#define rep(i, n) for(ll i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

// Segment Tree
template <typename T>
class SegTree {
public:
  SegTree(ll _n) {
    n = 1;
    while (n < _n) { n *= 2; }
    dat = vector<T>(2 * n - 1, INF);
  }

  void update(ll k, T a) {
    k += n - 1;
    dat[k] = a;
    while (k > 0) {
      k = (k - 1) / 2;
      dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]);
    }
  }

  // Calculate the min of [a, b)
  T query(ll a, ll b) {
    return _query(a, b, 0, 0, n);
  }

  // Calculate the min of [a, b)
  // k is the index (dat[k]). This is matched to [l, r)
  T _query(ll a, ll b, ll k, ll l, ll r) {
    // The llersection of [a, b) and [r, l) is blank.
    if (r <= a || b <= l) { return INF; }

    if (a <= l && r <= b) {  // [r, l) is completely included in [a, b)
      return dat[k];
    } else {
      ll vl = _query(a, b, k * 2 + 1, l, (l + r) / 2);
      ll vr = _query(a, b, k * 2 + 2, (l + r) / 2, r);
      return min(vl, vr);
    }
  }

private:
  ll n; // The size of source data. The power of 2.
  vector<T> dat; // The data. The size if 2*n-1. The last n elements(dat[n..2*n-2]) are leaves(source data). The first n-1 elements are nodes.
};

// ll main(ll argc, char** argv) {
//   ll arr[] = { 1, 3, 2, 7, 9, 11 };
//   ll n = 6;
//
//   SegTree<ll> st(n);
//   rep(i, n) {
//     st.update(i, arr[i]);
//   }
//
//   cout << st.query(1, 5) << endl;
//   cout << st.query(0, 4) << endl;
//   cout << st.query(3, 5) << endl;
// }


// Segment Tree
template <typename T>
class SegTreeMax {
public:
  SegTreeMax(ll _n) {
    n = 1;
    while (n < _n) { n *= 2; }
    dat = vector<T>(2 * n - 1, 0);
  }

  void update(ll k, T a) {
    k += n - 1;
    dat[k] = a;
    while (k > 0) {
      k = (k - 1) / 2;
      dat[k] = max(dat[k * 2 + 1], dat[k * 2 + 2]);
    }
  }

  // Calculate the max of [a, b)
  T query(ll a, ll b) {
    return _query(a, b, 0, 0, n);
  }

  // Calculate the max of [a, b)
  // k is the index (dat[k]). This is matched to [l, r)
  T _query(ll a, ll b, ll k, ll l, ll r) {
    // The llersection of [a, b) and [r, l) is blank.
    if (r <= a || b <= l) { return 0; }

    if (a <= l && r <= b) {  // [r, l) is completely included in [a, b)
      return dat[k];
    } else {
      ll vl = _query(a, b, k * 2 + 1, l, (l + r) / 2);
      ll vr = _query(a, b, k * 2 + 2, (l + r) / 2, r);
      return max(vl, vr);
    }
  }

private:
  ll n; // The size of source data. The power of 2.
  vector<T> dat; // The data. The size if 2*n-1. The last n elements(dat[n..2*n-2]) are leaves(source data). The first n-1 elements are nodes.
};

int main(int argc, char** argv) {
  ll N;
  cin >> N;
  vector<P> lrs;
  rep(i, N) {
    ll L, R;
    cin >> L >> R;
    lrs.emplace_back(L, R);
  }

  ll dis = -1;
  ll u = -1;
  rep(i, N) {
    ll L, R;
    tie(L, R) = lrs[i];
    if (dis < (R - L + 1)) {
      dis = R - L + 1;
      u = i;
    }
  }
  // Now, (l, r) is the pair with longuest distance
  cout << "dis: " << dis << endl;
  cout << "u: " << u << endl;

  SegTree<ll> min_r(N+1);
  SegTreeMax<ll> max_l(N+1);
  rep(i, N) {
    if (i == u) { continue; }
    ll L, R;
    tie(L, R) = lrs[i];
    min_r.update(i, R);
    max_l.update(i, L);
  }

  cout << "max_l:" << max_l.query(0, N) << endl;
  cout << "min_r:" << min_r.query(0, N) << endl;
}
