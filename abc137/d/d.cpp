#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

int main(int argc, char** argv) {
  int N, M;
  cin >> N; // Num
  cin >> M; // Capacity
  vector<int> A(N), B(N);
  rep(i, N) {
    cin >> A[i];
    cin >> B[i];
  }

  vector< pair<int, int> > pairs;
  rep(i, N) {
    pairs.emplace_back(A[i], B[i]);
  }
  sort(all(pairs));

  // For Debug
  // rep(i, N) {
  //   cout << pairs[i].first << ", " << pairs[i].second << endl;
  // }

  priority_queue<int> q;

  int res = 0;

  int pair_i = 0;
  for (int i = 1; i <= M; ++i) {
    while (pairs[pair_i].first <= i && pair_i < N) {
      q.push(pairs[pair_i].second); // NOTE: Push only value.
      ++pair_i;
    }
    if (!q.empty()) {
      int v = q.top();
      res += v;
      q.pop();
    }
  }

  cout << res << endl;

  return 0;
}
