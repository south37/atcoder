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


int main(int argc, char** argv) {
  ll N;
  cin >> N;
  vector<ll> L(N);
  rep(i, N) {
    cin >> L[i];
  }
  sort(all(L)); // Now, L is sorted

  // a < b < c.
  // We fix a and b, then search c.
  // c < a + b

  ll ans = 0;
  rep(b, N) {
    int r = b + 1;
    rep(a, b) {
      // Here, a < b < c. a and b are fixed. We search the count of c.
      // c < a + b is required.
      while (r < N && L[r] < L[a] + L[b]) { ++r; }
      int l = b + 1;
      ans += r - l; // c is [l, r)
    }
  }

  cout << ans << endl;
}
