#include <iostream>

using namespace std;

#define rep(i, n) for (int i = 0; i < n; ++i)

void getZarr(string& str, int Z[]) {
  int n = str.length();
  int L, R, k;

  L = R = 0;
  for (int i = 1; i < n; ++i) {
    if (i > R) {
      L = R = i;
      while (R < n && str[R - L] == str[R]) {
        R++;
      }
      Z[i] = R - L;
      R--;
    } else {
      k = i - L;

      if (Z[k] < R - i + 1) {
        Z[i] = Z[k];
      } else {
        L = i;
        while (R < n && str[R - L] == str[R]) {
          R++;
        }
        Z[i] = R - L;
        R--;
      }
    }
  }
}


void search(string& text, string& pattern) {
  string s = pattern + "$" + text;
  int l = s.length();

  int Z[l];
  getZarr(s, Z);

  int p = pattern.length();

  for (int i = 0; i < l; ++i) {
    if (Z[i] == p) {
      cout << "Pattern found at index " << i - p - 1 << endl;
    }
  }
}

int main(int argc, char** argv) {
  string s, t;
  cin >> s;
  cin >> t;

  search(s, t);

  cout << s << endl;
  cout << t << endl;
}
