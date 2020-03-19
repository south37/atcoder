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

ll gcd(ll a, ll b) {
  if (a < b) { swap(a, b); }
  if (b == 0) { return a; }
  return gcd(b, a % b);
}
ll lcm(ll a, ll b) {
  return (a * b) / gcd(a, b);
}

// int main(int argc, char** argv) {
//   int n, m;
//   cin >> n >> m;
//
//   cout << gcd(n, m) << endl;
// }

// The number of 2 in x.
int f(int x) {
  int res = 0;
  while (x%2 == 0) {
    x /= 2;
    ++res;
  }
  return res;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n, m;
  cin >> n >> m;
  vector<ll> a(n);
  rep(i, n) {
    cin >> a[i];
  }
  rep(i, n) {
    a[i] /= 2;
  }

  int t = f(a[0]);
  rep(i, n) {
    if (f(a[i]) != t) {
      cout << 0 << endl;
      return 0;
    }
    a[i] >>= t; // a[i] /= 2^t
  }
  m >>= t;

  ll l = 1;
  rep(i, n) {
    l = lcm(l, a[i]);
    if (l > m) {
      cout << 0 << endl;
      return 0;
    }
  }

  m /= l;
  ll ans = (m+1)/2; // the count of odd numbers in [1, m].
  cout << ans << endl;
}
