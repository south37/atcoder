#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <unordered_map>

using namespace std;

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

struct edge {
  int from;
  int to;
};

// I want "to -> from"
// vector<int> from_of_to(

vector<int> from_of_to[223456];
vector<uint64_t> scores(223456, 0);
vector<uint64_t> memo(223456, 0); // This is the score of vertex i.

// void calculate(int i) {
//   if (memo[i] >= 0) { return; } // memo[i] is already calculated.
//
//   memo[i] = 0;
//   for (auto e : from_of_to[i]) {
//     if (memo[e] < 0) { // memo[e] is not calculated.
//       calculate(e);
//     }
//     // Now, memo[e] is calculated
//     memo[i] += memo[e];
//   }
//   memo[i] += scores[i];
// }

int main(int argc, char** argv) {
  int N, Q;
  cin >> N >> Q;
  // vector<edge> edges(N);
  rep(i, N - 1) {
    edge e;
    cin >> e.from >> e.to;
    e.from--;  // For index
    e.to--;    // For index
    // edges.push_back(e);

    from_of_to[e.to].push_back(e.from);
    // // For Debug
    // cout << e.from << ", " << e.to << endl;
  }

  rep(i, Q) {
    int p, x;
    cin >> p >> x;
    p--;  // For index
    scores[p] += x;
  }

  // For Debug
  // rep(i, N) {
  //   cout << "scores[" << i << "]: " << scores[i] << endl;
  // }

  rep(i, N) {
    for (auto e : from_of_to[i]) { // e is smaller than i. so it is alreday calculated.
      memo[i] += memo[e];
    }
    memo[i] += scores[i];
  }

  rep(i, N) {
    cout << memo[i];
    if (i != (N-1)) {
      cout << " ";
    }
  }
  cout << endl;
}
