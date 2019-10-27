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

int main(int argc, char** argv) {
  double a, b, x;
  cin >> a >> b >> x;

  // atan2(h, x)
  // h = 2 * x / (a * b);
  double h = (double)x * 2 / a / b;

  // For Debug
  // cout << "h: " << h << endl;
  // cout << "b: " << b << endl;

  // double theta = atan2(h, b);
  // theta = theta * 180 / M_PI;
  // double ans = (double)90.0 - theta;
  if (h <= a) {
    double ans = atan2(b, h) * 180 / M_PI;
    cout << fixed << setprecision(10) << ans << endl;
    return 0;
  } else {
    double K = (double)x * 2 / a / a - b;
    double ans = atan2(b-K, a) * 180 / M_PI;
    cout << fixed << setprecision(10) << ans << endl;
    return 0;
  }
}
