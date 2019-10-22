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
  ll M, K;
  cin >> M >> K;
  // We can meke 0..(2**M-1).
  // So if K >= 2**M, it can't be made.
  if (K >= 1<<M) {
    cout << -1 << endl;
    return 0;
  }

  // Treat M=1
  if ((M == 1) && (K == 1)) {
    cout << -1 << endl;
    return 0;
  }
  if ((M == 1) && (K == 0)) {
    cout << "0 0 1 1" << endl;
    return 0;
  }

  vector<ll> tmp;
  rep(i, 1<<M) {
    if (i != K) {
      tmp.push_back(i);
    }
  }
  for (auto x : tmp) {
    cout << x << " ";
  }
  cout << K << " ";
  rep(i, (1<<M)-1) {
    cout << tmp[tmp.size() - 1 - i] << " ";
  }
  cout << K << endl;;
}
