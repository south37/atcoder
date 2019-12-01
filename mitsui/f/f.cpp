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

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll t1; ll t2;
  cin >> t1 >> t2;
  ll a1; ll a2;
  ll b1; ll b2;
  cin >> a1 >> a2;
  cin >> b1 >> b2;

  ll diff1 = a1-b1;
  ll diff2 = a2-b2;

  // cout << "diff1: " << diff1 << endl;
  // cout << "diff2: " << diff2 << endl;

  if (diff1 > 0 && diff2 > 0) {
    cout << 0 << endl;
    return 0;
  }
  if (diff1 < 0 && diff2 < 0) {
    cout << 0 << endl;
    return 0;
  }

  // Now, the sign of diff1 and diff2 is different.

  if (diff1 > 0) {
    diff1 *= -1;
    diff2 *= -1;
  }
  // Here, diff1 < 0, diff2 > 0.

  // cout << "diff1: " << diff1 << endl;
  // cout << "diff2: " << diff2 << endl;

  ll dis1 = diff1 * t1; // diff after t1;
  ll dis2 = dis1 + diff2 * t2; // diff after t1 + t2.

  // cout << "dis1: " << dis1 << endl;
  // cout << "dis2: " << dis2 << endl;

  if (dis2 < 0) { // can't reach to 0
    cout << 0 << endl;
    return 0;
  }

  if (dis2 > 0) {
    ll ans = 1;
    if (abs(dis1) % dis2 == 0) { // Touch 1 at last.
      ans += 2 * (abs(dis1) / dis2);
      ans -= 1; // minus 1 for last touch.
    } else {
      ans += 2 * (abs(dis1) / dis2);
    }
    cout << ans << endl;
    return 0;
  } else { // dis2 == 0
    cout << "infinity" << endl;
    return 0;
  }
}
