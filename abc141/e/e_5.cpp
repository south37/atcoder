// base: http://drken1215.hatenablog.com/entry/2019/09/16/014600

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

ll powmod(ll x, ll y) {
  ll r = 1;
  while (y) {
    if (y & 1) {
      r = r * x % MOD;
    }
    x = x * x % MOD;
    y >>= 1;
  }
  return r;
}

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
};

int N;
RollingHash rh("");

bool check(int d) {
  map<ull, int> ma;
  for (int i = 0; i + d <= N; ++i) {
    ull p = rh.get(i, i + d);
    if (ma.count(p)) {
      if (i - ma[p] >= d) { // no overlap
        return true;
      }
    } else {
      ma[p] = i; // set first i.
    }
  }
  return false;
}

int main(int argc, char** argv) {
  cin >> N;
  string S;
  cin >> S;

  rh.init(S);

  // Find the largest left by binary search.
  int left = 0;
  int right = N/2 + 1;
  while (right - left > 1) {
    int mid = (left + right) / 2;
    if (check(mid)) {
      left = mid;
    } else {
      right = mid;
    }
  }

  cout << left << endl;
}
