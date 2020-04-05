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
  ll maxA = 0;
  rep(i, k) {
    cin >> a[i];
    maxA = max(maxA, a[i]);
  }
  ll largest, smallest;

  // Here, we find the result in binary search.
  {
    ll l = 2, r = k * maxA + 3;
    // find the result in [l, r). find the boundary in [t, t, .., t, f, .. , f]
    while (r - l > 1) {
      ll m = (l + r)>>1;
      if (checkSmall(a, m)) {
        l = m;
      } else {
        r = m;
      }
    }
    largest = l;
  }

  {
    ll l = 1, r = k * maxA + 2;
    // find the result in (l, r]. find the boundary in [f, f, ..., f, t, .., t]
    while (r - l > 1) {
      ll m = (l + r)>>1;
      if (checkLarge(a, m)) {
        r = m;
      } else {
        l = m;
      }
    }
    smallest = r;
  }

  if (smallest <= largest) {
    cout << smallest << " " << largest << endl;
  } else { // invalid
    cout << -1 << endl;
  }
}
