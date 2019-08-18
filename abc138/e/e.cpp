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
    vector<int> indices = posMap[c];
    if (indices.size() == 0) {
      impossible = true;
      break;
    }

    auto it = lower_bound(all(indices), last_index); // indices is sorted.

    // If last_index is lower than any element in indices, we use the next value of indices.
    // If last_index is larger than all value of indices, we have to cycle.
    if ((it == indices.end()) || (it == --indices.end())) { // last_index is equal or the largest if incidex
      cycle_cnt += 1;
      last_index = indices[0];
    } else {
      last_index = *it;
    }

    bool found = false;
    // for (auto e : indices) {
    //   if (e > last_index) {  // e is larger than last_index. OK.
    //     last_index = e;
    //     found = true;
    //     break;
    //   }
    // }

    // if (!found) {
    //   cycle_cnt += 1;
    //   last_index = indices[0];
    // }
  }


  if (impossible) {
    cout << -1 << endl;
  } else {
    uint64_t res = (s_len * cycle_cnt) + last_index + 1;
    cout << res << endl;
  }
}
