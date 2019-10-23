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

int costs[10] = { 0, 2, 5, 5, 4, 5, 6, 3, 7, 6 };

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
    cost2num[costs[x]] = x;
  }

  // For Debug
  for (auto x : cost2num) {
    int cost = x.first;
    int num = x.second;
    cout << "cost: " << cost << ", num: " << num << endl;
  }
}
