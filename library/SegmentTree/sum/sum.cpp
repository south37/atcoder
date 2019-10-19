#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string.h>
#include <set>

using namespace std;

#define COUT(x) cout << #x << " = " << (x) << " (L" << __LINE__ << ")" << endl

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

// Segment Tree
template <typename T>
class SegTree {
public:
  SegTree(ll _n) {
    n = 1;
    while (n < _n) { n *= 2; }
    dat = vector<T>(2 * n - 1, 0);
  }

  // void update(ll k, T a) {
  //   k += n - 1;
  //   dat[k] = a;
  //   while (k > 0) {
  //     k = (k - 1) / 2;
  //     dat[k] = dat[k * 2 + 1] + dat[k * 2 + 2];
  //   }
  // }

  void add(ll k, T a) {
    k += n - 1;
    dat[k] += a;
    while (k > 0) {
      k = (k - 1) / 2;
      dat[k] = dat[k * 2 + 1] + dat[k * 2 + 2];
    }
  }

  // Calculate the sum of [a, b)
  T query(ll a, ll b) {
    return _query(a, b, 0, 0, n);
  }

  // Calculate the sum of [a, b)
  // k is the index (dat[k]). This is matched to [l, r)
  T _query(ll a, ll b, ll k, ll l, ll r) {
    // The intersection of [a, b) and [r, l) is blank.
    if (r <= a || b <= l) { return 0; }

    if (a <= l && r <= b) {  // [r, l) is completely included in [a, b)
      return dat[k];
    } else {
      ll vl = _query(a, b, k * 2 + 1, l, (l + r) / 2);
      ll vr = _query(a, b, k * 2 + 2, (l + r) / 2, r);
      return vl + vr;
    }
  }

private:
  ll n; // The size of source data. The power of 2.
  vector<T> dat; // The data. The size if 2*n-1. The last n elements(dat[n..2*n-2]) are leaves(source data). The first n-1 elements are nodes.
};

int main(int argc, char** argv) {
  ll arr[] = { 1, 3, 2, 7, 9, 11 };
  ll n = 6;

  SegTree<ll> st(n);
  rep(i, n) {
    st.add(i, arr[i]);
  }

  cout << st.query(1, 5) << endl; // 21
  cout << st.query(0, 4) << endl; // 13
  cout << st.query(3, 5) << endl; // 16

  st.add(4, 10);
  cout << st.query(3, 5) << endl; // 26
}
