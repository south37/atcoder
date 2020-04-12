// ref. https://atcoder.jp/contests/aising2019/submissions/3972256

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

ll n;
vector<ll> a;
vector<ll> s;
vector<ll> eSum; // even in 1-indexed
vector<ll> oSum; // odd  in 1-indexed

// aa is A n-[t/2], bb is A n-1.
// Return true when aa is near to x than bb.
bool lt(ll x, ll aa, ll bb) {
  if (bb < 0 || bb >= n) { return true; }
  if (aa < 0 || aa >= n) { return false; }
  ll d1 = abs(x-a[aa]);
  ll d2 = abs(x-a[bb]);
  if (d1 < d2) { return true; }
  if (d1 == d2) { return aa < bb; }
  return false;
}

// d .. 0 is even, 1 is odd
ll calc(ll r, ll d) {
  if (r < 0) { return 0; }
  if (d == 0) { return eSum[r+1]; }
  if (d == 1) { return oSum[r+1]; }
  return s[r+1];
}

// [l, r]
ll calc(ll l, ll r, ll d) {
  if (l > r) { return 0; }
  return calc(r, d) - calc(l-1, d);
}


ll solve(ll x) {
  ll l = 1, r = n+1;
  // Here, find the maximum value of f in [l, r). [f, ..., f, t, ..., t]
  while (r-l > 1) {
    ll mid = (l+r)>>1; // t
    ll a = mid/2;      // round up of t/2
    ll b = mid/2;      // round down of t/2
    if (a+b < mid) { ++a; } // mid is odd
    ll lo = n-mid; // A n-t
    ll hi = n-a-1; // A n-[t/2]
    // Here, take [lo, hi]
    if (lt(x, hi+1, lo)) { // hi is near to x then lo
      r = mid;
    } else {
      l = mid;
    }
  }
  // l cards: no conflict. l is valid t.
  ll a = (l+1)/2; // round up of l/2. Take his as takahaxhi. [n-a, n)
  ll d = n%2; // 0..even, 1..odd.
  ll ans = calc(0, n-l-1, d) + calc(n-l, n-a-1, -1);
  return s[n]-ans;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll q;
  cin >> n >> q;
  a.resize(n);
  s.resize(n+1);
  eSum.resize(n+1);
  oSum.resize(n+1);

  rep(i, n) {
    cin >> a[i];
  }
  rep(i, n) {
    s[i+1] = s[i] + a[i];
  }
  rep(i, n) {
    eSum[i+1] = eSum[i] + (i%2 == 0 ? a[i] : 0);
  }
  rep(i, n) {
    oSum[i+1] = oSum[i] + (i%2 == 1 ? a[i] : 0);
  }

  rep(i, q) {
    ll x;
    cin >> x;
    ll ans = solve(x);
    cout << ans << endl;
  }
}
