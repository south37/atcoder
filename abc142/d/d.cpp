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

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

ll powmod(ll x, ll n) { // like pow(x, n)
  ll r = 1;
  while (n) {
    if (n & 1) {
      r = r * x % MOD;
    }
    x = x * x % MOD;
    n >>= 1;
  }
  return r;
}

int gcd(int a, int b) {
  if (a < b) { swap(a, b); }
  if (b == 0) { return a; }
  return gcd(b, a % b);
}

int main(int argc, char** argv) {
  int A, B;
  cin >> A >> B;

  set<ll> a_candidates;
  a_candidates.insert(1);
  for (ll i = 2; i * i <= A; ++i) { // i is the divisor
    while ((A % i) == 0) {
      a_candidates.insert(i);
      A /= i;
    }
  }
  if (A > 1) {
    a_candidates.insert(A);
  }
  // cout << "a_candidates: " << endl;
  // for (auto x : a_candidates) {
  //   cout << x << endl;
  // }
  set<ll> b_candidates;
  b_candidates.insert(1);
  for (ll i = 2; i * i <= B; ++i) { // i is the divisor
    while ((B % i) == 0) {
      b_candidates.insert(i);
      B /= i;
    }
  }
  if (B > 1) {
    b_candidates.insert(B);
  }
  // cout << "b_candidates: " << endl;
  // for (auto x : b_candidates) {
  //   cout << x << endl;
  // }

  set<ll> candidates;
  for (auto x : a_candidates) {
    if (b_candidates.find(x) != b_candidates.end()) {
      candidates.insert(x);
    }
  }
  // cout << "candidates: " << endl;
  // for (auto x : candidates) {
  //   cout << x << endl;
  // }

  cout << candidates.size() << endl;
}
