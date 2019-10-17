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

// Search all cases. 4 ** N
// N is 8. So digit is 16.

int main(int argc, char** argv) {
  ll N, A, B, C;
  cin >> N >> A >> B >> C;
  vector<ll> l(N);
  rep(i, N) {
    cin >> l[i];
  }

  ll ans = INF;
  rep(i, 1LL << (2 * N)) { // Max is 1 << 16 ~ 6*10^4
    ll cost = 0;
    vector<ll> a, b, c;
    rep(j, N) {
      int s = 0;
      s += (i >> (j * 2)) & 1;
      s += (i >> (j * 2)) & 2;
      // 0: not used, 1: used in A, 2: used in B, 3: used in C
      if (s == 0) {
        continue;
      } else if (s == 1) {
        a.push_back(l[j]);
      } else if (s == 2) {
        b.push_back(l[j]);
      } else { // s == 3
        c.push_back(l[j]);
      }
    }
    if ((a.size() == 0) || (b.size() == 0) || (c.size() == 0)) { continue; }
    // Now, a, b, c has at least one.

    ll asum = 0;
    if (a.size() > 1) { cost += (a.size() - 1) * 10; }
    for (auto x : a) { asum += x; }
    cost += abs(asum - A);

    ll bsum = 0;
    if (b.size() > 1) { cost += (b.size() - 1) * 10; }
    for (auto x : b) { bsum += x; }
    cost += abs(bsum - B);

    ll csum = 0;
    if (c.size() > 1) { cost += (c.size() - 1) * 10; }
    for (auto x : c) { csum += x; }
    cost += abs(csum - C);

    if (cost < ans) {
      ans = cost;
    }
  }

  cout << ans << endl;
}
