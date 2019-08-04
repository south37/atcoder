#include <iostream>
#include <vector>

using namespace std;

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

int main(int argc, char** argv) {
  int n;
  cin >> n;

  int res = 0;

  if (n >= 1 && n <= 9) {
    cout << n;
  } else if (n >= 10 && n <= 99) {
    cout << 9;
  } else if (n >= 100 && n <= 999) {
    cout << 9 + (n - 99);
  } else if (n >= 1000 && n <= 9999) {
    cout << 9 + 900;
  } else if (n >= 10000 && n <= 99999) { // n >= 10000 && n <= 99999)
    cout << 9 + 900 + (n - 9999);
  } else { // 100000
    cout << 9 + 900 + 90000;
  }

  return 0;
}
