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

const ll INF = ll(1e18)+1;
const ll MOD = 1000000007;  // 1e9 + 7

// Check if "the count of the value which is lower than limit" is lower than k
bool check(vector<ll>& a, ll limit, ll k) {
  ll n = a.size();
  ll cnt = 0; // the count of pairs which are lower than m
  rep(i, n) {
    ll x = a[i];
    if (x > 0) { // positve
      int l = -1, r = n;
      // search in [l, r)
      while (r-l > 1) {
        int m = (l+r)/2;
        if (a[m]*x < limit) {
          l = m;
        } else {
          r = m;
        }
      }
      // Here, a[l]*x < limit, limit <= a[l+1]*x
      cnt += l + 1; // [0, l] is lower value
    } else if (x == 0) {
      if (limit > 0) {
        cnt += n;
      }
    } else { // negative
      int l = -1, r = n;
      // search in (l, r]
      while (r-l > 1) {
        int m = (l+r)/2;
        if (a[m]*x < limit) {
          r = m;
        } else {
          l = m;
        }
      }
      // Here, a[l]*x >= limit, limit > a[l+1]*x
      cnt += n - r; // [r, n) is lower value
    }
  }
  // minus self
  rep(i, n) {
    if (a[i] * a[i] < limit) { --cnt; }
  }
  cnt /= 2;

  return cnt < k;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n, k;
  cin >> n >> k;
  vector<ll> a(n);
  rep(i, n) {
    cin >> a[i];
  }
  sort(all(a));
  ll l = -INF;
  ll r = INF;
  // Search the result in [l, r)
  while (r - l > 1) {
    ll m = (r+l)/2;
    if (check(a, m, k)) { // ok
      l = m;
    } else {
      r = m;
    }
  }
  cout << l << endl;
}
