#include <iostream>

using namespace std;

int main(int argc, char** argv) {
  int n, d;
  cin >> n;
  cin >> d;

  int range = d * 2 + 1; // People can check this range.

  int r = n / range;
  if ((n % range) == 0) {
    // Do nothing
  } else {
    r += 1;
  }
  cout << r << endl;
}
