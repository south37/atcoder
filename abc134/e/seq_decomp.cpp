#include <iostream>
#include <vector>

using namespace std;

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

int main(int argc, char** argv) {
  int n;
  cin >> n;
  uint64_t a[n];
  rep(i, n) cin >> a[i];

  vector<int> sorted; // contains max values. sorted.

  rep(i, n) {
    auto it = lower_bound(all(sorted), a[i]);

    if (it == sorted.begin()) {  // The lowest
      sorted.insert(sorted.begin(), a[i]);  // Push front
    } else {
      --it;
      *it = a[i];
    }
  }

  cout << sorted.size() << endl;

  // NOTE: OLD
  // uint64_t len[n];
  // rep(i, n) len[i] = 0;

  // int visited[n];
  // rep(i, n) visited[i] = 0;

  // rep(i, n) {
  //   if (visited[i] > 0) {
  //     continue; // Already visited
  //   }
  //   uint64_t current = a[i];
  //   len[i] = 1;
  //   visited[i] = 1;
  //   for (int k = i+1; k < n; ++k) {
  //     if (visited[k] > 0) {
  //       continue; // Already visited
  //     }
  //     if (a[k] > current) {
  //       current = a[k];
  //       len[i] += 1;
  //       visited[k] = 1;
  //     }
  //   }

  //   // For debug
  //   // cout << "i: " << i << endl;
  //   // cout << "current: " << current << endl;
  //   // cout << "visited: ";
  //   // for (int i = 0; i < n; ++i) {
  //   //   cout << visited[i] << " ";
  //   // }
  //   // cout << endl;
  // }

  // // For debug
  // // for (int i = 0; i < n; ++i) {
  // //   cout << len[i] << " ";
  // // }

  // int cnt = 0;
  // rep(i, n) {
  //   if (len[i] > 0) {
  //     ++cnt;
  //   }
  // }
  // cout << cnt << endl;
}
