// Ari-hon. 3-3. P155.
// RMQ (Range Minimum Query) by Segment Tree.

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

const ll INF = 1e9;

// Segment Tree
template <typename T>
class SegTree {
public:
  SegTree(int _n) {
    n = 1;
    while (n < _n) { n *= 2; }
    dat = vector<T>(2 * n - 1, INF);
  }

  void update(int k, T a) {
    k += n - 1;
    dat[k] = a;
    while (k > 0) {
      k = (k - 1) / 2;
      dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]);
    }
  }

  // Calculate the min of [a, b)
  T query(int a, int b) {
    return _query(a, b, 0, 0, n);
  }

  // Calculate the min of [a, b)
  // k is the index (dat[k]). This is matched to [l, r)
  T _query(int a, int b, int k, int l, int r) {
    // The intersection of [a, b) and [r, l) is blank.
    if (r <= a || b <= l) { return INF; }

    if (a <= l && r <= b) {  // [r, l) is completely included in [a, b)
      return dat[k];
    } else {
      int vl = _query(a, b, k * 2 + 1, l, (l + r) / 2);
      int vr = _query(a, b, k * 2 + 2, (l + r) / 2, r);
      return min(vl, vr);
    }
  }

private:
  int n; // The size of source data. The power of 2.
  vector<T> dat; // The data. The size if 2*n-1. The last n elements(dat[n..2*n-2]) are leaves(source data). The first n-1 elements are nodes.
};

int main(int argc, char** argv) {
  int arr[] = { 1, 3, 2, 7, 9, 11 };
  int n = 6;

  SegTree<int> st(n);
  rep(i, n) {
    st.update(i, arr[i]);
  }

  cout << st.query(1, 5) << endl;
  cout << st.query(0, 4) << endl;
  cout << st.query(3, 5) << endl;
}
