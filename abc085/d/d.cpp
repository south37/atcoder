#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <unordered_map>

using namespace std;

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

typedef pair<uint64_t, uint64_t> P;

int main(int argc, char** argv) {
  uint64_t N, H;
  cin >> N >> H;
  vector<uint64_t> a(N), b(N);
  rep(i, N) {
    cin >> a[i] >> b[i];
  }

  // For Debug
  // rep(i, N) {
  //   cout << a[i] << endl;
  // }
  // rep(i, N) {
  //   cout << b[i] << endl;
  // }

  vector<P> pairs;
  rep(i, N) {
    pairs.push_back(P(a[i], 0));
    pairs.push_back(P(b[i], 1));
  }

  sort(all(pairs));
  reverse(all(pairs));

  // For Debug
  // rep(i, 2 * N) {
  //   cout << pairs[i].first << ", " << pairs[i].second << endl;
  // }
  vector<P> candidates;
  rep(i, 2 * N) {
    if (pairs[i].second == 0) { // pairs[i] is A[i]
      candidates.push_back(pairs[i]);
      break;
    }
    candidates.push_back(pairs[i]);
  }
  // Now, the last element of candidates is type-A.
  uint64_t cnt = 0;
  uint64_t sum = 0;
  rep(i, candidates.size() - 1) {
    sum += candidates[i].first;
    ++cnt;
    if (sum >= H) { break; }
  }
  if (sum >= H) { // Passed only by B.
    cout << cnt << endl;
    return 0;
  }

  // Now, we use candidates[-1] as repeatable A.
  uint64_t a_score = candidates[candidates.size() - 1].first;
  uint64_t rest = H - sum;
  if ((rest % a_score) == 0) {
    cnt += (rest / a_score);
  } else {
    cnt += (rest / a_score) + 1;
  }

  cout << cnt << endl;
}
