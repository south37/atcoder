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
typedef tuple<ll, ll, ll> triple;
typedef double D;

struct P {
  double x;
  double y;
};

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

ll n;
vector<P> p;

double dist(P a, P b) {
  double dx = a.x-b.x;
  double dy = a.y-b.y;
  return sqrt(dx*dx + dy*dy);
}

double f(double x, double y) {
  double res = 0;
  rep(i, n) {
    res = max(res, dist((P){x, y}, p[i]));
  }
  return res;
}

double g(double x) {
  double l = 0, r = 1000;
  rep(i, 80) {
    double c1 = (l*2+r)/3;
    double c2 = (l+r*2)/3;
    if (f(x,c1) > f(x,c2)) {
      l = c1;
    } else {
      r = c2;
    }
  }
  return f(x,l);
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  cout << setprecision(10) << fixed;

  cin >> n;
  p.resize(n);
  rep(i, n) {
    cin >> p[i].x >> p[i].y;
  }

  double l = 0, r = 1000;
  rep(i, 80) {
    double c1 = (l*2+r)/3;
    double c2 = (l+r*2)/3;
    if (g(c1) > g(c2)) {
      l = c1;
    } else {
      r = c2;
    }
  }

  double ans = g(l);
  cout << ans << endl;
}
