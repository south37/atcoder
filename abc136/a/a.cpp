#include <iostream>
#include <vector>

using namespace std;

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

int main(int argc, char** argv) {
  int a, b, c;
  cin >> a;
  cin >> b;
  cin >> c;

  int cap = a - b;
  if (c > cap) {
    cout << c - cap << endl;
  } else {
    cout << 0 << endl;
  }
}
