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
#define fr first
#define sc second
#define mp make_pair
#define pb push_back

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

// Vector, Circle
const double eps = 1e-9;
bool equal(double a, double b) { return abs(a-b) < eps; }

struct V {
  double x, y;
  V(double x=0, double y=0) : x(x), y(y) {}
  V operator+(const V& p) const { return V(x+p.x, y+p.y); }
  V operator-(const V& p) const { return V(x-p.x, y-p.y); }
  V operator*(double a) const { return V(x*a, y*a); }
  double sqrNorm() const { return x*x+y*y; }
  double norm() const { return sqrt(sqrNorm()); }
  V rotate90() const { return V(y, -x); } // rotate 90 degree clockwise
};

struct Circle {
  V o; // the position of center
  double r; // radius

  Circle (V o=V(), double r=0) : o(o), r(r) {}
  vector<V> xp(const Circle& c) {
    V v = c.o - o;
    double l = v.norm(); // the distance between `o` and `c.o`
    if (equal(l, 0)) return {}; // `o` and `c.o` are same
    if (equal(l+r+c.r, max({ l, r, c.r })*2)) { // this circle and c touches in a single point.
      if (c.r == max({ l, r, c.r })) {
        return { o - v*(r/l) };
      } else {
        return { o + v*(r/l) };
      }
    }
    if (l+r+c.r < max({ l, r, c.r })*2) { return {}; } // there is no touch point
    double x = -(c.r*c.r - l*l - r*r) / (2*l);
    double y = sqrt(r*r - x*x);
    V mid = o+v*(x/l);
    v = v.rotate90();
    return { mid + v*(y/l), mid - v*(y/l) };
  }
  bool isInside(const V& p) {
    return (p-o).norm() < r+eps;
  }
};

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  cout << setprecision(10) << fixed;

  ll n, k;
  cin >> n >> k;
  if (k == 1) {
    cout << 0 << endl;
    return 0;
  }
  vector<Circle> c(n);
  rep(i, n) {
    cin >> c[i].o.x >> c[i].o.y >> c[i].r;
  }
  double l = 0, r = 400000; // 2000 * sqrt(2) * 100 < 400,000
  // find the boundary in (l, r]. [f, ..., f, t, ..., t]
  // binary search in 100 step.
  rep(ti, 100) {
    double x = (l+r)/2;
    vector<V> ps; // the candidate positions
    // set center positions
    rep(i, n) ps.push_back(c[i].o);
    // set touch points
    rep(i, n) {
      rep(j, i) {
        Circle a = c[i];
        Circle b = c[j];
        a.r = x/a.r; // T/ci
        b.r = x/b.r; // T/ci
        auto tmp = a.xp(b); // the touch points of circle a and circle b
        ps.insert(ps.end(), tmp.begin(), tmp.end());
      }
    }
    bool ok = false;
    for (V& p : ps) {
      int cnt = 0;
      rep(ci, n) {
        Circle nc = c[ci];
        nc.r = x/nc.r; // T/ci
        if (nc.isInside(p)) { ++cnt; }
      }
      if (cnt >= k) ok = true;
    }
    if (ok) {
      r = x;
    } else {
      l = x;
    }
  }
  cout << r << endl;
}
