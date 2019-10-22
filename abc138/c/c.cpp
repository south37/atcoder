#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <unordered_map>

using namespace std;

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

int main(int argc, char** argv) {
  int n;
  cin >> n;
  vector<int> v(n);
  rep(i, n) {
    cin >> v[i];
  }

  priority_queue<double, vector<double>, greater<double> > q; // increasing order
  rep(i, n) {
    q.push(v[i]);
  }

  while (q.size() > 1) {
    // NOTE: fetch minimum two elements.
    double v1 = q.top(); q.pop();
    double v2 = q.top(); q.pop();

    double newV = (v1 + v2) / 2.0;  // calculate new.
    q.push(newV);
  }

  double res = q.top(); q.pop();

  cout << res << endl;

  // For Debug
  // cout << n << endl;
  // rep(i, n) {
  //   cout << v[i] << endl;
  // }
}
