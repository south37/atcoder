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
  ll L;
  cin >> L;
  vector<ll> ones;
  ll i = 0;
  while ((L>>i) > 0) {
    if ((L>>i) & 1) {
      ones.push_back(i);
    }
    ++i;
  }
  reverse(all(ones)); // decreasing order

  // For Debug
  // for (auto x : ones) {
  //   cout << x << endl;
  // }

  ll N = ones[0]; // The length of vertices without root(0).
  vector<triple> edges;
  rep(i, N) {
    // i+1 is the target number.
    edges.emplace_back(i, i+1, 0);
    edges.emplace_back(i, i+1, 1LL << i);
  }
  // Now, N is the last indice.

  ll summed = 1<<N;
  rep(i, ones.size()) {
    if (i == 0) { continue; }
    ll M = ones[i]; // The offset. e.g. 2 for 1 of 100
    edges.emplace_back(M, N, summed); // there are 2**M paths in [0, M]
    // Do somethinbg
    summed += 1<<M;
  }

  cout << N+1 << " " << edges.size() << endl;
  for (auto x : edges) {
    int i, j, c;
    tie(i, j, c) = x;
    cout << i+1 << " " << j+1 << " " << c << endl; // 1-indexed
  }
}
