// base. https://atcoder.jp/contests/nikkei2019-2-qual/submissions/8355827

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

  ll n, k;
  cin >> n >> k;

  vector<P> a(n); // At first, we consider only first 2N. They are compared with N later.
  rep(i, n) {
    a[i].fr = k; ++k;
  }
  for (int i = n/2; i < n; ++i) {
    a[i].sc = k; ++k;
  }
  for (int i = 0; i < n/2; ++i) {
    a[i].sc = k; ++k;
  }

  // Now, first 2N are used. I want to calculate the sum.
  vector<triple> s;
  rep(i, n) {
    s.emplace_back(a[i].fr + a[i].sc, a[i].fr, a[i].sc);
  }
  sort(all(s));

  // s is sorted. We check s with last N.
  rep(i, n) {
    ll c, fr, sc;
    tie(c, fr, sc) = s[i];
    if (c > k + i) {
      cout << -1 << endl;
      return 0;
    }
  }

  rep(i, n) {
    ll c, fr, sc;
    tie(c, fr, sc) = s[i];
    cout << fr << " " << sc << " " << k+i << endl;
  }
}
