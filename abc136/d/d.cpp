#include <iostream>
#include <vector>

using namespace std;

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

int main(int argc, char** argv) {
  string s;
  cin >> s;

  int n = s.size();
  vector<int> diffs(n, 1);

  bool left_is_r = true;
  int the_most_left_r = 0;
  int the_most_left_l = -1;

  for (int i = 1; i < n; ++i) {
    if (left_is_r) {
      if (s[i] == 'R') {
        continue;
      } else { // s[i] == 'L'
        int diff = (i - the_most_left_r);
        for (int j = 0; j < diff; ++j) {
          diffs[i - (j + 1)] = j;
        }

        the_most_left_l = i;
        diffs[i] = - 1;
        left_is_r = false; // From now, left i L
      }
    } else { // left is L
      if (s[i] == 'R') {
        the_most_left_r = i;
        diffs[i] = 0;
        left_is_r = true;
      } else { // s[i] == 'L'
        diffs[i] = - (i - the_most_left_l) - 1;
      }
    }
  }

  // NOTE: Only for debug
  // cout << diffs[0];
  // for (int i = 1; i < n; ++i) {
  //   cout << " " << diffs[i];
  // }

  // ### input2
  // RRLLLLRLRRLL
  //
  // 1(R) 0(R) -1(L) -2(L) -3(L) -4(L) 0(R) -1(L) 1(R) 0(R) -1(L) -2(L)
  //
  // We calculate after the n.
  vector<int> cnts(n, 0);

  int trial = n + (n % 2); // If n is odd, + 1.

  for (int i = 0; i < n; ++i) {
    if (diffs[i] >= 0) { // R
      int idx = i + diffs[i];  // Base index
      if ((trial - diffs[i]) % 2 == 1) {
        cnts[idx + 1] += 1;
      } else {
        cnts[idx] += 1;
      }
    } else { // L
      int idx = i + diffs[i]; // Base index
      if ((trial + diffs[i]) % 2 == 1) {
        cnts[idx + 1] += 1;
      } else {
        cnts[idx] += 1;
      }
    }
  }

  cout << cnts[0];
  for (int i = 1; i < n; ++i) {
    cout << " " << cnts[i];
  }

  // vector<int> n_cnts(n, -1); // initialize with -1

  // int onemore = ((n % 2) == 1) ? 1 : 0;

  // for (int i = 0; i < n + onemore; ++i) {
  //   rep(j, n) { n_cnts[j] = cnts[j]; }  // Set

  //   rep(j, n) {
  //     if (s[j] == 'R') {
  //       n_cnts[j+1] += cnts[j];
  //       n_cnts[j] -= cnts[j];
  //     } else { // s[j] == 'L'
  //       n_cnts[j-1] += cnts[j];
  //       n_cnts[j] -= cnts[j];
  //     }
  //   }

  //   rep(j, n) { cnts[j] = n_cnts[j]; }  // Set
  // }

  // cout << cnts[0];
  // for (int i = 1; i < n; ++i) {
  //   cout << " " << cnts[i];
  // }
}
