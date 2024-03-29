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

// BIT (Fenwick Tree) with 0-indexed query
// https://youtu.be/lyHk98daDJo?t=7960
template<typename T>
struct BIT {
  int n;
  vector<T> d;
  BIT(int n=0) : n(n), d(n+1) {}
  void add(int i, T x=1) {
    i++; // 0-indexed to 1-indexed
    for (; i <= n; i += i&-i) {
      d[i] += x;
    }
  }
  // The sum of [0, i]
  T sum(int i) {
    i++; // 0-indexed to 1-indexed
    T x = 0;
    for (; i; i -= i&-i) {
      x += d[i];
    }
    return x;
  }
  // The sum of [l, r)
  T sum(int l, int r) {
    assert(l <= r);
    if (r == 0) { return 0; } // Here, l == 0 && r == 0
    if (l == 0) { return sum(r-1); }
    return sum(r-1) - sum(l-1);
  }
};

// int main(int argc, char** argv) {
//   int N;
//   cin >> N;
//   vector<int> v(N);
//   rep(i, N) {
//     cin >> v[i];
//   }
//
//   BIT<int> bit(N);
//   rep(i, N) {
//     bit.add(i, v[i]);
//   }
//
//   cout << bit.sum(4) << endl; // sum of [0,4]. 24
//   cout << bit.sum(9) << endl; // sum of [0,9]. 55
// }

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n, q;
  cin >> n >> q;
  vector<ll> c(n);
  rep(i,n) {
    cin >> c[i];
  }
  vector<ll> pos(n+1, -1); // pos[color] .. right most position of color.
  vector<vector<ll>> rmarks(n); // rmarks[i] .. idx of query at position i.
  vector<ll> l(q), r(q);
  rep(i,q) {
    cin >> l[i] >> r[i];
    --l[i]; --r[i]; // 0-indexed
    rmarks[r[i]].push_back(i);
  }

  vector<ll> ans(q);
  BIT<ll> bit(n+5);
  // Start scan.
  rep(i,n) {
    ll nc = c[i]; // current color
    if (pos[nc] >= 0) { // already inserted
      bit.add(pos[nc], -1); // erase
    }
    bit.add(i, 1);
    pos[nc] = i;

    for (ll qId : rmarks[i]) {
      ans[qId] = bit.sum(l[qId], i+1); // sum of [l[qId], i]
    }
  }

  rep(i,q) {
    cout << ans[i] << endl;
  }
}
