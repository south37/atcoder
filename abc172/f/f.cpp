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

  ll n;
  cin >> n;
  vector<ll> a(n);
  rep(i,n) {
    cin >> a[i];
  }

  vector<ll> b(3);
  b[0] = a[0];
  b[1] = a[1];
  if (n > 2) {
    ll now = 0;
    for (int i = 2; i < n; ++i) {
      now ^= a[i];
    }
    b[2] = now;
  }

  // printvec(b);

  ll k = 0;
  // Here, check bit
  rep(i,50) { // check 50 bit
    ll bit0 = (b[0]>>i)&1ll;
    ll bit1 = (b[1]>>i)&1ll;
    ll bit2 = (b[2]>>i)&1ll;

    cout << "i:" << i << endl;
    cout << "bit0:" << bit0 << endl;
    cout << "bit1:" << bit1 << endl;
    cout << "bit2:" << bit2 << endl;

    if (bit0 == bit1) {
      if (bit2 == 1) { // invalid
        cout << -1 << endl;
        return 0;
      }
      // Here, bit2 == 0. valid.
      if (bit1 == 1) { // bit0 == 1
        k += (1ll<<i);
      }
    } else { // bit0 != bit1
      if (bit2 == 0) { // invalid
        cout << -1 << endl;
        return 0;
      }
      // Here, bit2 == 1. valid.
    }
  }

  cout << k << endl;

  // For Debug
  // --a[0];
  // ++a[1];
  // ll ans = 0;
  // rep(i,n) {
  //   ans ^= a[i];
  // }
  // cout << ans << endl;
}
