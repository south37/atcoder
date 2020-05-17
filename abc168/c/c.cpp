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
#define sz(x) (ll)(x).size()
#define fr first
#define sc second
#define mp make_pair
#define pb push_back
#define eb emplace_back

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;
typedef vector<ll> vl;
typedef vector<P> vp;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  cout << setprecision(15) << fixed;

  double a, b, h,m;
  cin >> a >> b >> h >> m;
  double mD = m/60        * M_PI * 2;
  double hD = (h+m/60)/12 * M_PI * 2;

  // cout << "mD:" << mD / (2*M_PI) << endl;
  // cout << "hD:" << hD / (2*M_PI) << endl;

  double deg = abs(hD - mD);
  // if (deg > M_PI) {
  //   deg -= M_PI;
  // }
  // cout << "deg/(2PI):" << deg / (2*M_PI) << endl;
  // cout << "deg/(PI):" << deg / (M_PI) << endl;
  // cout << "deg:" << deg << endl;
  // // cout << "2PI/6:" << (2*M_PI) / 6.0  << endl;

  // // Here, deg is smaller degree.

  // cout << "cos(60/180): " << cos(60/180 * M_PI) << endl;
  // cout << "cos(deg): " << cos(deg) << endl;
  // cout << "a: " << a << endl;
  // cout << "b: " << b << endl;

  double c2 = (double)(a*a) + (double)(b*b) - (double)2*a*b* cos(deg);
  // cout << "c2:" << c2 << endl;
  double ans = sqrt(c2);
  cout << ans << endl;
}
