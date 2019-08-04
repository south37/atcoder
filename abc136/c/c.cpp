#include <iostream>
#include <vector>

using namespace std;

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

int main(int argc, char** argv) {
  int n;
  cin >> n;
  int a[n];
  rep(i, n) {
    cin >> a[i];
  }

  if (n == 1) { // Early return
    cout << "Yes";
    return 0;
  }

  int left = a[0];
  for (int i = 1; i < n; ++i) {
    if (a[i] == left) { // OK
      // Do nothing
    } else if (a[i] > left) { // OK
      a[i] -= 1;
      // Do nothing
    } else {
      cout << "No";
      return 0;
    }

    left = a[i];
  }

  // rep(i, n) {
  //   cout << "a[" << i << "]:" << a[i] << endl;
  // }

  cout << "Yes";
  return 0;
  // cout << n << endl;
  // cout << a[0] << endl;
  // cout << a[1] << endl;
}
