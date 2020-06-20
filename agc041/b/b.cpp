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

  ll n,m,v,p;
  cin >> n >> m >> v >> p;
  vector<ll> a(n);
  rep(i,n) {
    cin >> a[i];
  }
  sort(all(a));
  reverse(all(a));
  // printvec(a);

  auto check = [&](ll x) {
    if (a[x]+m < a[p-1]) { // Here, a[x] can't exceed a[p-1]
      return false;
    }
    assert(a[x]+m >= a[p-1]);
    if (x <= p-1) { // Here, x is already in top p
      return true;
    }
    assert(x >= p);

    ll tot = 0; // We can select tot
    // Select m in x. [x,x]
    tot += m;
    // Select m in top p-1. [0,p-1)
    for (int i = 0; i < p-1; ++i) {
      tot += m;
    }
    // Select m in bottom. (x, n)
    for (int i = x+1; i < n; ++i) {
      tot += m;
    }
    // Select available in [p-1,x)
    for (int i = p-1; i < x; ++i) {
      tot += a[x]+m - a[i]; // a[i] must not exceed a[x]+m
    }
    // cout << "x:" << x << endl;
    // cout << "tot:" << tot << endl;
    // cout << "m*v:" << m*v << endl;
    return tot >= m*v; // tot must exceed m*v
  };

  ll l = -1;
  ll r = n;
  // Here, find boundary of [t,f]
  while (r-l > 1) {
    ll m = (l+r)/2;
    if (check(m)) {
      l = m;
    } else {
      r = m;
    }
  }
  // Here, [1,l] is ok.
  cout << l+1 << endl;
}
