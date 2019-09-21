// https://atcoder.jp/contests/arc008/tasks/arc008_4
// http://drken1215.hatenablog.com/entry/2018/02/14/121239

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

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

int dx[] = { 1, -1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

template<class T> struct SegTree {
  const function<T(T, T)> F;
  const T UNITY;
  int SIZE_R;
  vector<T> dat;

  SegTree(int n, const function<T(T, T)> f, const T &unity): F(f), UNITY(unity) { init(n); }

  void init(int n) {
    SIZE_R = 1;
    while (SIZE_R < n) { SIZE_R *= 2; }
    dat.assign(SIZE_R * 2, UNITY);
  }

  /* set, a is 0-indexed */
  void set(int a, const T &v) { dat[a + SIZE_R] = v; }

  void build() {
    for (int k = SIZE_R - 1; k > 0; --k) {
      dat[k] = F(dat[k*2], dat[k*2+1]);
    }
  }

  /* update, a is 0-indexed */
  void update(int a, const T &v) {
    int k = a + SIZE_R;
    dat[k] = v;
    while (k >>= 1) dat[k] = F(dat[k*2], dat[k*2+1]);
  }

  /* get {min-value, min-index}, a and b are 0-indexed */
  T get(int a, int b) {
    T vleft = UNITY, vright = UNITY;
    for (int left = a + SIZE_R, right = b + SIZE_R; left < right; left >>= 1, right >>= 1) {
      if (left & 1) vleft = F(vleft, dat[left++]);
      if (right & 1) vright = F(dat[--right], vright);
    }
    return F(vleft, vright);
  }

  inline T operator [] (int a) { return dat[a + SIZE_R]; }

  /* debug */
  void print() {
    for (int i = 0; i < SIZE_R; ++i) {
      cout << (*this)[i];
      if (i != SIZE_R-1) cout << ",";
    }
    cout << endl;
  }
};

int main(int argc, char** argv) {
  ll N;
  int M;
  cin >> N >> M;
  vector<ll> p(M), pls;
  vector<double> a(M), b(M);
  rep(i, M) {
    cin >> p[i] >> a[i] >> b[i];
    --p[i];
    pls.push_back(p[i]);
  }
  sort(pls.begin(), pls.end());
  pls.erase(unique(pls.begin(), pls.end()), pls.end());
  int NN = (int)pls.size();

  SegTree< pair<double, double> > seg(
    NN,
    [](pair<double, double> a, pair<double, double> b) {
      return make_pair(a.first * b.first, a.second * b.first + b.second);  // (a, b), (c, d) -> (ac, bc + d)
    },
    make_pair(1.0, 0)
  );

  double Min = 1.0, Max = 1.0;
  rep(i, M) {
    int idx = lower_bound(pls.begin(), pls.end(), p[i]) - pls.begin();
    seg.update(idx, make_pair(a[i], b[i]));
    pair<double, double> res = seg.get(0, NN);
    Min = min(Min, res.first + res.second);
    Max = max(Max, res.first + res.second);
  }
  cout << fixed << setprecision(10) << Min << endl << Max << endl;
}
