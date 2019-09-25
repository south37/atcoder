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

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7
const double EPS = 1e-9;

// Vector Type for sorting points by polar angle.
struct V {
  double x, y;

  V(double x = 0, double y = 0) : x(x), y(y) {}

  V& operator+=(const V& v) { x += v.x; y += v.y; return *this; }
  V& operator+(const V& v) const { return V(*this) += v; }
  V& operator-=(const V& v) { x -= v.x; y -= v.y; return *this; }
  V& operator-(const V& v) const { return V(*this) -= v; }
  V& operator*=(double s) { x *= s; y *= s; return *this; }
  V& operator*(double s) const { return V(*this) *= s; }
  V& operator/=(double s) { x /= s; y /= s; return *this; }
  V& operator/(double s) const { return V(*this) /= s; }
  double dot(const V& v) const { return x*v.x + y*v.y; }
  double cross(const V& v) const { return x*v.y - y*v.x; }
  double norm() const { return sqrt(norm2()); }
  double norm2() const { return x*x + y*y; }
  int ort() const { // orchant
    if (abs(x) < EPS && abs(y) < EPS) { return 0; } // Check (0, 0)

    if (y > 0) {
      return (x > 0) ? 1 : 2;
    } else {
      return (x > 0) ? 4 : 3;
    }
  }
  bool operator<(const V& v) const {
    int o = ort();
    int vo = v.ort();
    if (o != vo) { return o < vo; }
    return cross(v) > 0;
  }
};

istream& operator>>(istream& i, V& v) {
  i >> v.x >> v.y;
  return i;
}
ostream& operator<<(ostream& o, const V& v) {
  o << "(" << v.x << ", " << v.y << ")";
  return o;
}

int main(int argc, char** argv) {
  int N;
  cin >> N;
  vector<V> v(N);
  rep(i, N) {
    cin >> v[i];
  }

  sort(all(v));
  double ans = 0;
  rep(i, N) {
    V now(0, 0); // Start from (0, 0)
    rep(j, N) {
      now += v[(i + j) % N];
      ans = max(ans, now.norm());
    }
  }
  cout << fixed << setprecision(10) << ans << endl;
}
