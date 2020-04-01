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

const ll INF = 1e10;
const ll MOD = 1000000007;  // 1e9 + 7

struct D {
  vector<double> l; // left-most values
  vector<double> r; // right-most values

  D() : l(3, INF), r(3, -INF) {}

  void add(double x, ll dir) {
    ++dir; // [-1,1] => [0,2]
    chmin(l[dir], x);
    chmax(r[dir], x);
  }

  // NOTE: Use double for t because i*t should be double.
  double get(double t) {
    double nl = INF;
    double nr = -INF;
    rep(i, 3) {
      chmin(nl, l[i]+i*t);
      chmax(nr, r[i]+i*t);
    }
    return nr-nl;
  }

  vector<double> events() {
    vector<double> ts;
    rep(i,3) rep(j, i) {
      {
        double t = (l[j]-l[i])/(i-j);
        if (t > 0) { ts.push_back(t); }
      }
      {
        double t = (r[j]-r[i])/(i-j);
        if (t > 0) { ts.push_back(t); }
      }
    }
    return ts;
  }
};

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  D xd, yd;
  rep(i, n) {
    ll x, y;
    char d;
    cin >> x >> y >> d;
    if (d == 'L') { xd.add(x, -1); yd.add(y, 0); }
    if (d == 'R') { xd.add(x, 1);  yd.add(y, 0); }
    if (d == 'U') { xd.add(x, 0);  yd.add(y, 1); }
    if (d == 'D') { xd.add(x, 0);  yd.add(y, -1); }
  }

  vector<double> ts; // changing events
  ts.push_back(0);
  ts.push_back(INF);
  {
    auto nts = xd.events();
    // cout << "xd.events:"; printvec(nts);
    ts.insert(ts.end(), all(nts));
  }
  {
    auto nts = yd.events();
    // cout << "yd.events:"; printvec(nts);
    ts.insert(ts.end(), all(nts));
  }
  sort(all(ts));
  double ans = 1e18;
  for (double t : ts) {
    double now = xd.get(t) * yd.get(t);
    ans = min(ans, now);
  }
  cout << ans << endl;
}
