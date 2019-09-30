#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
  int n;
  cin >> n;
  int a[n];
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  int r[n];
  // for (int i = 0; i < n; ++i) {
  //   r[i] = -1;  // Sentinel
  // }

  for (int i = n - 1; i >= 0; --i) {
    int s = 0;
    // Check right
    int k = 2;
    while (((i + 1) * k - 1) < n) {
      s += r[((i + 1) * k - 1)];
      ++k;
    }
    if ((s % 2) == a[i]) {
      r[i] = 0;
    } else {
      r[i] = 1;
    }
  }

  // For debug
  // for (int i = 0; i < n; ++i) {
  //   cout << r[i] << endl;
  // }

  int cnt = 0;
  for (int i = 0; i < n; ++i) {
    if (r[i] == 1) {
      ++cnt;
    }
  }

  int acm = 0;
  cout << cnt << endl;
  if (cnt > 0) {
    for (int i = 0; i < n; ++i) {
      if (r[i] == 1) {
        cout << (i + 1);
        ++acm;

        if (cnt != acm) {
          cout << " ";
        }
      }
    }
    cout << endl;
  }
}
