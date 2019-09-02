#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

int dx[] = { 1, -1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };

typedef pair<int, int> P;
typedef tuple<int, int, int> triple;

int gcd(int a, int b) {
  if (a < b) { swap(a, b); }
  if (b == 0) { return a; }
  return gcd(b, a % b);
}

bool prime(int n) {
  for (int i = 2; i <= sqrt(n); i++) {
    if (n % i == 0) { return false; }
  }
  return n != 1;
}

int main(int argc, char** argv) {
  int N;
  cin >> N;
  vector<P> box(N);
  rep(i, N) {
    cin >> box[i].first >> box[i].second;
  }
  sort(all(box), [](P x, P y) {
    if (x.second == y.second) {
      return x.first > y.first; // Decreasing order
    }
    return x.second < y.second; // Increasing order
  });

  // For Debug
  // rep(i, N) {
  //   cout << "w, h: " << box[i].first << ", " << box[i].second << endl;
  // }

  vector<int> sorted;
  rep(i, N) {
    auto it = lower_bound(all(sorted), box[i].first);
    if (it == sorted.end()) {
      sorted.push_back(box[i].first);
    } else {
      *it = box[i].first;
    }
  }

  cout << sorted.size() << endl;
}
