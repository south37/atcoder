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

// RollingHash with mod(2**64)
struct RollingHash {
  // Mod is 2**64 (max of ull + 1)
  static const ull base1 = 1000000007;
  vector<ull> _hash, _power;

  RollingHash(const string& S) { init(S); }
  void init(const string& S) {
    int n = S.size();
    _hash.resize(n+1);
    _power.assign(n+1, 1);
    rep(i, n) {
      _hash[i+1] = _hash[i] * base1 + S[i];
      _power[i+1] = _power[i] * base1;
    }
  }

  // get hash of S[l,r)
  inline ull get(int l, int r) const {
    ull res1 = _hash[r] - _hash[l] * _power[r-l];
    return res1;
  }

  // get lcp of S[a:] and T[b:]
  inline int getLCP(int a, int b) const {
    int len = min((int)_hash.size()-a, (int)_hash.size()-b);
    int low = 0, high = len;
    while (high - low > 1) {
      int mid = (low + high) >> 1;
      if (get(a, a+mid) != get(b, b+mid)) high = mid;
      else low = mid;
    }
    return low;
  }
};

// int main(int argc, char** argv) {
//   string S("abcabc");
//
//   RollingHash rh(S);
//
//   cout << (rh.get(0, 3) == rh.get(3, 6)) << endl; // abc == abc: true
//   cout << (rh.get(0, 3) == rh.get(3, 5)) << endl; // abc == ab: false
//
//   cout << rh.getLCP(0, 3) << endl; // abc, abc: 3
//   cout << rh.getLCP(1, 4) << endl; // bc, bc: 2
//   cout << rh.getLCP(0, 4) << endl; // abc, bc: 0
// }

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  string S;
  cin >> S;
  RollingHash rh(S);

  ll ans = 0;
  rep(l,n) {
    for (ll r = l+1; r < n; ++r) {
      ll lcp = rh.getLCP(l,r);
      lcp = min(lcp, r-l); // NOTE: overlap is not allowed
      chmax(ans, lcp);
    }
  }
  cout << ans << endl;
}
