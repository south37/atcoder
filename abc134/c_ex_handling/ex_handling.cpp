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

  int fst = -1;
  int snd = -1;

  for (int i = 0; i < n; ++i) {
    if (fst < a[i]) {
      snd = fst;
      fst = a[i];
    } else if (snd < a[i]) {
      snd = a[i];
    }
  }

  for (int i = 0; i < n; ++i) {
    if (a[i] == fst) {
      cout << snd << endl;
    } else {
      cout << fst << endl;
    }
  }
}
