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
  int N, K;
  cin >> N >> K;
  int max_cnt = (N-1)*(N-2)/2;
  // Now, we can make (N-1)*(N-2)/2 pairs by connecting 1 and others.
  // By selecting (N-1)*(N-2)/2 - K pairs, we can decrease the count to K.
  if (K > max_cnt) {
    cout << -1 << endl;
    return 0;
  }

  cout << (N-1) + max_cnt - K << endl;
  for (int i = 2; i <= N; ++i) {
    cout << "1 " << i << endl;
  }
  int cnt = 0;
  for (int i = 2; i <= N; ++i) {
    for (int j = i + 1; j <= N; ++j) {
      if (cnt < max_cnt - K) {
        cout << i << " " << j << endl;
      }
      cnt += 1;
    }
  }
}
