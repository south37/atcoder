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
  // We fix b and c, then search a.
  // c < a + b <=> c-b < a

  ll ans = 0;
  for (int i = 1; i < N; ++i) {
    for (int j = i + 1; j < N; ++j) {
      int b = L[i];
      int c = L[j];
      auto it = upper_bound(all(L), c - b);
      int iter = it - L.begin();
      if (iter < i) { // a exists.
        ans += i - iter;
      }
    }
  }

  cout << ans << endl;
}
