#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <unordered_map>

using namespace std;

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

int main() {
  int n;
  cin >> n;

  bool odd = false, even = false;
  vector< pair<int64_t, int64_t> > a(n);
  rep(i, n) {
    int64_t x, y;
    cin >> x >> y;

    // For Debug
    // cout << "x: " << x << ", y: " << y << endl;
    if ((x+y) & 1) {
      odd = true;
      // cout << "odd" << endl;
    } else {
      even = true;
      // cout << "even" << endl;
    }
    a[i].first = x;
    a[i].second = y;
  }
  if (odd && even) {
    cout << -1 << endl;
    return 0;
  }

  int m = 31;
  // int m = 3;
  cout << (even ? m+1 : m) << endl;

  vector<int64_t> d(m);
  rep(i, m) {
    d[i] = 1ll << i;
  }
  reverse(all(d));
  for (auto& x : d) {
    cout << x << ' ';
  }
  if (even) {
    cout << 1 << endl;
  } else {
    cout << endl;
  }

  for (auto& p : a) {
    int64_t x, y;
    tie(x, y) = p;
    if (even) { --x; }
    string res;
    rep(i, m) {
      bool u = x+y>0, v = x-y>0;
      if (u  && v)  { res += "R", x -= d[i]; continue; }
      if (!u && v)  { res += "D", y += d[i]; continue; }
      if (u  && !v) { res += "U", y -= d[i]; continue; }
      if (!u && !v) { res += "L", x += d[i]; continue; }
    }
    assert(x == 0 && y == 0);
    if (even) { res += "R"; };
    cout << res << endl;
  }
}
