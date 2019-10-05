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

int main(int argc, char** argv) {
  int N;
  cin >> N;
  vector<int> A(N);
  rep(i, N) {
    cin >> A[i];
  }
  map<P, set<int>> mp; // (num, id) => cnt.

  rep(i, N) {
    for (int k = 2; k * k <= A[i]; ++k) {
      int j = 0; // id for same numbers.
      while ((A[i] % k) == 0) {
        P p(k, j);
        mp[p].insert(i); // insert the id of A.
        A[i] /= k;
        ++j;
      }
    }
    if (A[i] > 1) {
      P p(A[i], 0);
      mp[p].insert(i); // insert the id of A.
    }
  }

  int ans = 1;
  vector<int> candidates(N, 1);  // candidates[i] .. the take by i.
  for (auto x : mp) {
    P p = x.first;
    if (x.second.size() == N) {
      ans *= p.first;
    }
    if (x.second.size() == N-1) {
      rep(i, N) {
        if (x.second.find(i) == x.second.end()) { // i is not included
          candidates[i] *= p.first;
        }
      }
    }
  }
  int m = 1;
  rep(i, N) {
    m = max(m, candidates[i]);
  }
  cout << ans * m << endl;
}
