#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string.h>
#include <set>
#include <stack>

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
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  vector<ll> a(n);
  rep(i,n) {
    cin >> a[i];
  }

  vector<ll> b(3);
  b[0] = a[0];
  b[1] = a[1];
  if (n > 2) {
    ll now = 0;
    for (int i = 2; i < n; ++i) {
      now ^= a[i];
    }
    b[2] = now;
  }

  ll S = b[0]+b[1];
  ll X = b[2];

  // Find (i,j) where..
  //   i+j == i^j + 2*(i&j)
  //   S == X + 2*D
  //   i+j == S
  //   i^j == X
  //   i&j == D
  if (S < X) {
    cout << -1 << endl;
    return 0;
  }
  if ((S-X)%2 == 1) {
    cout << -1 << endl;
    return 0;
  }
  ll D = (S-X)/2;

  rep(i,50) {
    if (((X>>i)&1ll) && ((D>>i)&1ll)) { // both is 1. invalid.
      cout << -1 << endl;
      return 0;
    }
  }
  // Here, D is valid.
  // (i,j) is (D+Y,D+Z) where Y^Z == X && Y&Z == 0

  ll c = D; // target. "a[0] - c" is diff.
  if (c > a[0]) { // too large
    cout << -1 << endl;
    return 0;
  }
  // Here, i <= a[0]
  for (ll i = 50; i >= 0; --i) {
    if ((X>>i)&1ll) { // i bit exists in X
      ll now = c+(1ll<<i);
      if (now <= a[0]) {
        c = now;
      }
    }
  }

  if (c == 0) { // invalid
    cout << -1 << endl;
  } else {
    cout << a[0]-c << endl;
  }
}
