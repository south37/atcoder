#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <cassert>

using namespace std;

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

int main(int argc, char** argv) {
  int64_t N, M;
  cin >> N >> M;
  vector<int64_t> P(N + 1, 0);
  rep(i, N) {
    cin >> P[i+1];
  }

  // For Debug
  // cout << N << endl;
  // cout << M << endl;
  // rep(i, N) {
  //   cout << P[i] << endl;
  // }

  // First, calculate all P[i] x P[j];
  vector<int64_t> d;
  rep(i, N + 1) {
    for(int j = i; j < N + 1; ++j) {
      if (P[i] + P[j] <= M) {
        d.push_back(P[i] + P[j]);
      }
    }
  }
  sort(all(d));

  // For Debug
  // cout << "d:" << endl;
  // rep(i, d.size()) {
  //   cout << d[i] << endl;
  // }

  int64_t r = 0;
  // Now, we want to calculate the max pair of d[i] + d[j] <= M. So d[j] <= (M - d[i]).
  rep(i, d.size()) {
    int64_t rest = M - d[i];
    auto it = upper_bound(all(d), rest);

    // For Debug
    // cout << "d[" << i << "]: " << d[i] << endl;
    // cout << "rest: " << rest << endl;
    // cout << *(it - 1) << endl;

    if (it == d.begin()) {
      r = max(r, d[i]);  // (it - 1) is out of range.
    } else {
      r = max(r, d[i] + *(it - 1));
    }
  }

  cout << r << endl;
}
