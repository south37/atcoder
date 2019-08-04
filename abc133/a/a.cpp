#include <iostream>
#include <vector>

using namespace std;

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

int main(int argc, char** argv) {
  int n, a, b;
  cin >> n;
  cin >> a;
  cin >> b;

  if ((n * a) > b) {
    cout << b << endl;
  } else {
    cout << n * a;
  }
}
