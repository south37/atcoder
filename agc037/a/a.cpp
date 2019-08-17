#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <unordered_map>

using namespace std;

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

typedef pair<int, int> P;

int main(int argc, char** argv) {
  string s;
  cin >> s;

  // TODO(south37) Check the length of s;

  vector<string> results;
  string prv = s.substr(0, 1);
  results.push_back(prv);
  s = s.substr(1, s.size() - 1);

  while (s.size() != 0) {
    string cur = s.substr(0, 1);

    if (prv != cur) {
      prv = cur;
      s = s.substr(1, s.size() - 1);
      results.push_back(prv);
    } else { // Match
      // Take 2
      if (s.size() > 1) {
        prv = s.substr(0, 2);
        s = s.substr(2, s.size() - 2);
        results.push_back(prv);
      } else { // s.size() == 1
        break;  //
      }
    }
  }

  cout << results.size() << endl;
}
