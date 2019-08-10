#include <iostream>
#include <vector>

using namespace std;

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

int main(int argc, char** argv) {
  string s;
  cin >> s;

  vector<int> cnts(27, 0);
  int len = s.size();
  rep(i, len) {
    int idx = s[i] - 'A';
    cnts[idx] += 1;
  }

  // For Debug
  // rep(i, cnts.size()) {
  //   cout << (char)('A' + i) << ": " << cnts[i] << ", ";
  // }

  int cnts_len = cnts.size();
  rep(i, cnts_len) {
    if ((cnts[i] == 0) || cnts[i] == 2) { // OK
      continue;
    } else { // No
      cout << "No";
      return 0;
    }
  }

 cout << "Yes";
 return 0;
}
