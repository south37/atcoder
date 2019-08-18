#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <unordered_map>

using namespace std;

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

vector<int> posMap[26];

int main(int argc, char** argv) {
  string s, t;
  cin >> s;
  cin >> t;

  // For Debug
  // cout << s << endl;
  // cout << t << endl;
  int s_len = s.size();
  rep(i, s_len) {
    int c = s[i] - 'a';
    posMap[c].push_back(i);
  }

  // For Debug
  // rep(i, 26) {
  //   cout << (char)('a' + i) << ": ";
  //   for (auto e : posMap[i]) {
  //     cout << e << " ";
  //   }
  //   cout << endl;
  // }

  bool impossible = false;
  int last_index = -1; // -1 is the sentinel.
  uint64_t cycle_cnt = 0;  // The count of cycle.
  int t_len = t.size();
  rep(i, t_len) {
    int c = t[i] - 'a';
    if (posMap[c].size() == 0) {
      impossible = true;
      break;
    }

    auto it = upper_bound(all(posMap[c]), last_index); // posMap[c] is sorted.

    // If last_index is lower than any element in posMap[c], we use the next value of posMap[c].
    // If last_index is larger than all value of posMap[c], we have to cycle.
    if (it == posMap[c].end()) { // last_index is equal or the largest if incidex
      cycle_cnt += 1;
      last_index = posMap[c][0];
    } else {
      last_index = *it;
    }
  }


  if (impossible) {
    cout << -1 << endl;
  } else {
    uint64_t res = (s_len * cycle_cnt) + last_index + 1;
    cout << res << endl;
  }
}
