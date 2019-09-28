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

int main(int argc, char** argv) {
  int N, K;
  cin >> N >> K;
  vector<ll> A(N);
  rep(i, N) {
    cin >> A[i];
  }

  ll sum = 0;
  rep(i, N) { sum += A[i]; }
  set<ll> candidates;
  for (int i = 1; i * i <= sum; ++i) {
    if (sum % i == 0) {
      candidates.insert(i);
      candidates.insert(sum / i);
    }
  }
  ll ans = 1;
  for (ll x : candidates) {
    ll need; // required operations
    {
      vector<ll> r(N);
      rep(i, N) { r[i] = A[i] % x; }
      sort(all(r));
      ll B = 0;
      rep(i, N) { B += x - r[i]; }
      ll A = 0;
      need = 1e18;
      rep(i, N) {
        A += r[i];
        B -= x - r[i];
        need = min(need, max(A, B));
      }
    }
    if (need <= K) {
      ans = max(ans, x);
    }
  }
  cout << ans << endl;
}
