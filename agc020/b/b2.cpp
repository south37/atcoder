// ref. https://img.atcoder.jp/agc020/editorial.pdf

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

ll f(ll x, ll a) {
  return x - (x%a);
}

// return true if n can be result in 2 or smaller.
bool checkSmall(vector<ll>& a, ll n) {
  ll now = n;
  rep(i, a.size()) {
    now = f(now, a[i]);
  }
  return now <= 2;
}

// return true if n can be result in 2 or larger.
bool checkLarge(vector<ll>& a, ll n) {
  ll now = n;
  rep(i, a.size()) {
    now = f(now, a[i]);
  }
  return now >= 2;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll k;
  cin >> k;
  vector<ll> a(k);
  rep(i, k) {
    cin >> a[i];
  }

  // l[i] = [ l[i+1]/a[i] ] * a[i]
  // r[i] = [ r[i+1]/a[i] ] * a[i] + a[i] - 1.

  // l[i]/a[i] = [ l[i+1]/a[i] ]
  // r[i]/a[i] = [ r[i+1]/a[i] ]
  vector<ll> l(k+1); // l[i+1] .. minimum possible number after i.
  vector<ll> r(k+1); // r[i+1] .. maximum possible number after i.
  l[k] = 2;
  r[k] = 2;
  for (int i = k-1; i >= 0; --i) {
    l[i] = ((l[i+1]+a[i]-1) / a[i]) * a[i];
    r[i] = (r[i+1] / a[i]) * a[i] + a[i] - 1;
  }
  // cout << "l: "; printvec(l);
  // cout << "r: "; printvec(r);

  if (l[0] > r[0]) { // invalid
    cout << -1 << endl;
  } else {
    cout << l[0] << " " << r[0] << endl;
  }
}
