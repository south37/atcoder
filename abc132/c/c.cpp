#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

int main(int argc, char** argv) {
  int n;
  cin >> n;
  int d[n];
  rep(i, n) {
    cin >> d[i];
  }

  sort(d, d + n);
  int left = d[(n/2) - 1];
  int right = d[(n/2)];

  cout << right - left;
}
