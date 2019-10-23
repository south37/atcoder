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

int num2cost[10] = { 0, 2, 5, 5, 4, 5, 6, 3, 7, 6 }; // 0 is dummy.

// mapping: number => cost
// 1->2
// 2->5
// 3->5
// 4->4
// 5->5
// 6->6
// 7->3
// 8->7
// 9->6

int main(int argc, char** argv) {
  ll N, M;
  cin >> N >> M;
  vector<int> A(M);
  rep(i, M) {
    cin >> A[i];
  }
  sort(all(A));
  reverse(all(A));

  // Now, A is decreasing order.
  vector<ll> dp(N+1, -1);
  dp[0] = 0;
  rep(k, M) {
    ll num = A[k];
    ll cost = num2cost[num];
    rep(i, N+1) {
      if ((i-cost >= 0) && (dp[i-cost] >= 0)) {
        if (dp[i-cost]+1 > dp[i]) {
          dp[i] = dp[i-cost]+1;
        }
      }
    }
  }

  // Now, dp[N] is the max number of digits.

  string ans = "";
  ll match = N;
  while (match > 0) {
    rep(i, M) {
      ll num = A[i];
      ll cost = num2cost[num];
      if ((match-cost >= 0) && (dp[match] == dp[match-cost]+1)) {
        ans += (char)('0'+A[i]);
        match -= cost;
        break;
      }
    }
  }

  cout << ans << endl;
}
