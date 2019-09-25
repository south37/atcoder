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

struct V {
  double x, y;

  V(double x = 0, double y = 0) : x(x), y(y) {}
  V& operator+=(const V& v) {
    x += v.x; y += v.y;
    return *this;
  }
  V& operator+(const V& v) {
    return V(*this) += v;
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
  // For Debug
  rep(i, N) {
    cout << v[i];
  }
}
