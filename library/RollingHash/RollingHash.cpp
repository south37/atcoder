// base: http://drken1215.hatenablog.com/entry/2019/09/16/014600
// abc141/e

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>
#include <string.h>

using namespace std;

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

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

  // get hash of S[left:right]
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

int main(int argc, char** argv) {
  string S("abcabc");

  RollingHash rh(S);

  cout << (rh.get(0, 2) == rh.get(3, 5)) << endl; // abc == abc: true
  cout << (rh.get(0, 2) == rh.get(3, 4)) << endl; // abc == ab: false

  cout << rh.getLCP(0, 3) << endl; // abc, abc: 3
  cout << rh.getLCP(1, 4) << endl; // bc, bc: 2
  cout << rh.getLCP(0, 4) << endl; // abc, bc: 0
}
