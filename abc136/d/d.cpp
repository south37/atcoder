#include <iostream>
#include <vector>

using namespace std;

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

int main(int argc, char** argv) {
  string s;
  cin >> s;

  int n = s.size();
  vector<int> cnts(n, 1);
  vector<int> n_cnts(n, -1); // initialize with -1

  int onemore = ((n % 2) == 1) ? 1 : 0;

  for (int i = 0; i < n + onemore; ++i) {
    rep(j, n) { n_cnts[j] = cnts[j]; }  // Set

    rep(j, n) {
      if (s[j] == 'R') {
        n_cnts[j+1] += cnts[j];
        n_cnts[j] -= cnts[j];
      } else { // s[j] == 'L'
        n_cnts[j-1] += cnts[j];
        n_cnts[j] -= cnts[j];
      }
    }

    rep(j, n) { cnts[j] = n_cnts[j]; }  // Set
  }

  cout << cnts[0];
  for (int i = 1; i < n; ++i) {
    cout << " " << cnts[i];
  }
}
