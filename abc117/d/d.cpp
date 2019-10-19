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

#define rep(i, n) for(ll i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

// 2 ** 40 = 1024 ** 4 ~ 10 ** 12
// cnts[j] ... count of 1 in each bit of A. The bit is counted from left.
// e.g. 100 -> [1, 0, 0]
ll cnts[40];

// lower_bits[j] .. Represetns which should be in j bits.
ll lower_bits[40];

int main(int argc, char** argv) {
  ll N, K;
  cin >> N >> K;
  vector<ll> A(N);
  rep(i, N) {
    cin >> A[i];
  }

  // At first, we want to calculate the count of 1 in each bit.
  // Then, lefter bit should be the other bit. (e.g. If 1 is smaller in j bit, then the j bit of X should be 1.)
  rep(i, N) {
    rep(j, 40) {
      if ((A[i] >> (39 - j)) & 1) {
        ++cnts[j];
      }
    }
  }
  rep(j, 40) {
    if (cnts[j] > N / 2) { // The count of 1 is larger
      lower_bits[j] = 0;
    } else { // The count of 0 is larger
      lower_bits[j] = 1;
    }
  }

  // Here, if K is INF, the result is represented by lower_bits.
  // But, we have the limitation of X <= K, so check that "current X is equal or lower than K".
  ll X = 0;
  rep(j, 40) {
    ll d = lower_bits[j] << (39LL-j);
    if ((X + d) <= K) {
      X += d;
    }
  }

  // Now, f(X) is the answer.
  ll ans = 0;
  rep(i, N) {
    ans += X ^ A[i];
  }

  cout << ans << endl;
}
