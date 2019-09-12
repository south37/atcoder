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

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }

const int64_t INF = 1e18;

int main(int argc, char** argv) {
  int N;
  cin >> N;
  vector<int64_t> a(3 * N);
  rep(i, 3 * N) {
    cin >> a[i];
  }

  int64_t front_sum = 0;
  rep(i, N) {
    front_sum += a[i];
  }
  // front_max[i] is the maximum value by [0..i]. i is [N-1, 2*N-1] (the number of candidates is N+1). boundary is right.
  // [0...i] [i+1...]
  //       ^ boundary
  vector<int64_t> front_max(3 * N);
  front_max[N-1] = front_sum;

  // P-queue of front N. We want minimum element to increase sum.
  priority_queue<int64_t, vector<int64_t>, greater<int64_t> > front_q;
  rep(i, N) {
    front_q.push(a[i]);
  }
  for (int i = N; i < 2 * N; ++i) {
    int64_t top = front_q.top();
    if (a[i] > top) {
      // Use a[i] to increase sum.
      front_max[i] = front_max[i-1] - top + a[i];
      front_q.pop();
      front_q.push(a[i]);
    } else {
      front_max[i] = front_max[i-1];
    }
  }
  // For Debug
  // rep(i, 3 * N) {
  //   cout << front_max[i] << endl;
  // }

  int64_t last_sum = 0;
  for (int i = 2 * N; i < 3 * N; ++i) {
    last_sum += a[i];
  }
  // last_min[i] is the minimum value by [i..3*N-1]. i is [N, 2*N] (the number of candidates is N+1). boundary is left.
  // [...i-1] [i...3*N-1]
  //         ^ boundary
  vector<int64_t> last_min(3 * N);
  last_min[2*N] = last_sum;

  // P-queue of last N. We want maximum element to decrease sum.
  priority_queue<int64_t> last_q;
  for (int i = 2 * N; i < 3 * N; ++i) {
    last_q.push(a[i]);
  }
  for (int i = 2 * N - 1; i >= N; --i) {
    int64_t top = last_q.top();
    if (a[i] < top) {
      // Use a[i] to decrease sum.
      last_min[i] = last_min[i+1] - top + a[i];
      last_q.pop();
      last_q.push(a[i]);
    } else {
      last_min[i] = last_min[i+1];
    }
  }
  // For Debug
  // rep(i, 3 * N) {
  //   cout << last_min[i] << endl;
  // }

  int64_t res = - INF;
  // Check the each i with right boundary.
  for (int i = N-1; i < 2 * N; ++i) {
    res = max(res, front_max[i] - last_min[i+1]);
  }
  cout << res << endl;
}
