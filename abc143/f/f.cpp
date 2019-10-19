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
  int N;
  cin >> N;
  vector<int> A(N);
  rep(i, N) {
    cin >> A[i];
  }

  map<int, int> mp; // The count of each A.
  rep(i, N) {
    ++mp[A[i]];
  }

  vector<P> cnts;
  for (auto x : mp) {
    cnts.emplace_back(x.second, x.first);
  }
  sort(all(cnts));
  reverse(all(cnts));
  // Here, cnts has the <count, A> pair in decreasing order.

  for (int t = 1; t <= N; ++t) {
    if (mp.size() < t) {
      cout << 0 << endl;
      continue;
    }
  }
}
