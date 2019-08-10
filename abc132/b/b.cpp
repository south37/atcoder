#include <iostream>
#include <vector>

using namespace std;

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

int main(int argc, char** argv) {
  int n;
  cin >> n;
  int p[n];
  rep(i, n) {
    cin >> p[i];
  }

  int res = 0;
  for (int i = 1; i < n-1; ++i) {
    int left = p[i-1];
    int mid = p[i];
    int right = p[i+1];

    if (p[i-1] < p[i] && p[i] < p[i+1]) { //OK
      ++res;
    } else if (p[i+1] < p[i] && p[i] < p[i-1]) {
      ++res;
    } else {
      // Do nothing
    }
  }

  cout << res << endl;
}
