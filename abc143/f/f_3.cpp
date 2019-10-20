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
  ll N;
  cin >> N;
  vector<int> a(N);
  rep(i, N) {
    int x;
    cin >> x;
    ++a[x-1];
  }
  sort(all(a)); // a: frequencies in increasing order.

  vector<int> s(N+1); // s[i]: sum of [0, i). s[0] = 0.
  rep(i, N) {
    s[i+1] = s[i] + a[i];
  }

  ll ans = N;
  for (int k = 1; k <= N; ++k) {
    // We want to find the boundary of ok and ng.
    while (1) {
      bool ok = [&](int c) {
        int i = lower_bound(all(a), c) - a.begin();
        int sum = c*(N-i) + s[i]; // (N-1)-(i-1) = N-i
        return sum >= c*k;
      }(ans);
      if (ok) { break; }
      --ans;
    }
    cout << ans << endl;
  }
}
