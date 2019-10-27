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

const ll INF = 1e12;
const ll MOD = 1000000007;  // 1e9 + 7

int main(int argc, char** argv) {
  ll N;
  cin >> N;
  ll i = 1;
  vector<ll> candidates;
  while (i * i <= N) {
    if ((N % i) == 0) {
      candidates.push_back(i);
    }
    ++i;
  }

  // For Debug
  // for (auto x : candidates) {
  //   cout << x << endl;
  // }
  ll ans = INF;
  for (auto i : candidates) {
    ll cand = 0;
    cand += i-1;
    cand += (N/i) - 1;
    if (cand < ans) {
      ans = cand;
    }
  }

  cout << ans << endl;
}
