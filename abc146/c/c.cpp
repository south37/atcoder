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

  // AN + B d(N) <= X
  // AN <= (X-d(N) B) <= (X-B)
  // N <= (X-B)/A
  ll a, b, x;
  cin >> a >> b >> x;

  // We use binary search
  ll l = 1;
  ll r = INF + 1; // 1e9 + 1

  // At first, we check 1.
  if ((a + b) > x) {
    cout << 0 << endl;
    return 0;
  }

  // [l, r)
  while (r - l > 1) {
    ll mid = (r + l)/2;

    ll digit;
    if        (mid >= 1000000000) {
      digit = 10;
    } else if (mid >= 100000000) {
      digit = 9;
    } else if (mid >= 10000000) {
      digit = 8;
    } else if (mid >= 1000000) {
      digit = 7;
    } else if (mid >= 100000) {
      digit = 6;
    } else if (mid >= 10000) {
      digit = 5;
    } else if (mid >= 1000) {
      digit = 4;
    } else if (mid >= 100) {
      digit = 3;
    } else if (mid >= 10) {
      digit = 2;
    } else {
      digit = 1;
    }

    if ((a * mid + b * digit) <= x) { // ok
      l = mid;
    } else {
      r = mid;
    }
  }

  cout << l << endl;
}
