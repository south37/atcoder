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
  int N2 = 1 << N;
  vector<ll> S(N2);
  rep(i, N2) {
    cin >> S[i];
  }
  sort(all(S));
  reverse(all(S));  // Elements in S are sorted in decreasing order.

  vector<ll> s;
  s.push_back(S[0]);
  S[0] = -1;

  // O(N * 2**N) ~ O(MlogM) in M = 2**N (< 10 ** 6)
  rep(iter, N) {
    vector<ll> p = s;
    sort(all(p));

    for (int j = 0; p.size() > 0 && j < N2; ++j) { // Search the largest remaining value from S.
      if (S[j] == -1) { continue; }
      if (S[j] < p.back()) {
        p.pop_back();
        s.push_back(S[j]);
        S[j] = -1;
      }
    }

    if (p.size() > 0) {  // Invalid if elmens are remaining in p.
      cout << "No" << endl;
      return 0;
    }
  }

  cout << "Yes" << endl;
}
