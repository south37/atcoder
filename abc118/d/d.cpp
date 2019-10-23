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

int num2cost[10] = { 0, 2, 5, 5, 4, 5, 6, 3, 7, 6 };

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

// max: 99..9, 9*6=54
// min: 1, 1*2=2

// max digit: 11..1, 9*2=18

// e.g.1
// 3 7 8 4 -> 5 3 7 4
// - 3 * 5 + 5 = 20

// If all value are -1, return false.
bool valid(const vector<ll>& v) {
  for (auto x : v) {
    if (x != -1) { return true; }
  }
  return false;
}

bool larger(const vector<ll>& left, const vector<ll>& right) {
  if (!valid(left)) { return false; }
  if (!valid(right)) { return true; }
  // Here, left and right are valid.
  ll l_sum = 0;
  ll r_sum = 0;
  rep(i, 10) { if (left[i] >= 0) { l_sum += left[i]; } }
  rep(i, 10) { if (right[i] >= 0) { r_sum += right[i]; } }
  if (l_sum != r_sum) { return l_sum > r_sum; }
  // Here, l_sum and r_sum are equal.
  for (int i = 9; i >= 1; --i) {
    if (left[i] != right[i]) {
      return left[i] > right[i];
    }
  }
  return false; // same.
}

void print_vector(const vector<ll>& v) {
  for (int i = 9; i >= 1; --i) {
    if (v[i] >= 0) {
      rep(j, v[i]) {
        cout << i;
      }
    }
  }
  cout << endl;
}

int main(int argc, char** argv) {
  ll N, M;
  cin >> N >> M;
  vector<int> A(M);
  rep(i, M) {
    cin >> A[i];
  }
  sort(all(A));
  map<ll, ll> cost2num; // stores the max number for each cost.
  for (auto x : A) {
    cost2num[num2cost[x]] = x;
  }

  // For Debug
  // for (auto x : cost2num) {
  //   int cost = x.first;
  //   int num = x.second;
  //   cout << "cost: " << cost << ", num: " << num << endl;
  // }
  vector<ll> costs;
  for (auto x : cost2num) {
    costs.push_back(x.first);
  }
  ll K = costs.size(); // The size of costs.

  // dp[i] ... the maximum score when i match are used.
  // i: [0, N]
  // checked K times. [0..K-1] are checked.
  vector< vector<ll> > dp(N+1, vector<ll>(10, -1));
  dp[0] = vector<ll>(10, 0);
  rep(k, K) { // loop K times
    ll cost = costs[k];
    rep(i, N+1) {
      if ((i-cost >= 0) && valid(dp[i-cost])) {
        vector<ll> nex(dp[i-cost]); // copy
        if (nex[cost2num[cost]] >= 0) {
          ++nex[cost2num[cost]];
        } else {
          nex[cost2num[cost]] = 1;
        }
        if (larger(nex, dp[i])) { // dp[i-costs[k]] + cost2num[costs[k]] > dp[i]
          dp[i] = nex;
        }
      }
    }
  }

  if (valid(dp[N])) {
    print_vector(dp[N]);
  } else {
    // We must not reach here.
    cout << "error" << endl;
    return -1;
  }
}
