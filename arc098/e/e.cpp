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

const ll INF = 1e12;
const ll MOD = 1000000007;  // 1e9 + 7

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n, k, q;
  cin >> n >> k >> q;
  vector<ll> a(n);
  rep(i, n) {
    cin >> a[i];
  }

  ll ans = INF;

  // Now, we try all values in a.
  rep(i, n) {
    ll x = a[i];
    vector<ll> c; // candidates. c[q-1] is the minimum maximium value.
    ll s = 0; // The start position.
    while (s < n) {
      // cout << "s: " << s << endl;

      while (a[s] < x && s < n) { ++s; } // skip a[s] < x
      // cout << "ns: " << s << endl;

      // Now, a[s] >= x
      ll j = s;

      vector<ll> d;
      while (a[j] >= x && j < n) {
        // cout << "j: " << j << endl;
        if (j == i) { ++j; continue; } // we must pick up j except for i.
        d.push_back(a[j]);
        ++j;
      }
      sort(all(d));

      cout << "x: " << x << endl;
      cout << "d: ";
      printvec(d);

      // Now, a[j] < x
      if (d.size() >= k) {
        for (int l = 0; l <= c.size()-k; ++l) { // if c.size()==k, we pick only 1
          c.push_back(d[l]);
        }
      }
      printvec(c);

      s = j; // set j as next s.
    }

    if (c.size() >= q) {
      sort(all(c));
      cout << "x: " << x << endl;
      cout << "c: " << c[q-1] << endl;
      chmin(ans, c[q-1] - x);
    }
  }

  cout << ans << endl;
}
