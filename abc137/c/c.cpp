#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>

using namespace std;

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

int main(int argc, char** argv) {
  int N;
  cin >> N;
  vector<string> s(N);
  rep(i, N) {
    cin >> s[i];
  }

  map< vector<int> , int64_t> cnts_map;

  rep(i, N) {
    vector<int> cnts(27, 0);

    for (int j = 0; j < 10; ++j) {
      cnts[(s[i][j] - 'a')] += 1;
    }

    // For Debug
    // rep(j, 27) {
    //   cout << cnts[j];
    // }
    // cout << endl;

    auto it = cnts_map.find(cnts);
    if (it != cnts_map.end()) {
      it->second++;
    } else {
      cnts_map[cnts] = 1;
    }
  }

  // For Debug
  // cout << cnts_map.size();

  int64_t r = 0;
  for (auto it : cnts_map) {
    int64_t cnt = it.second;
    if (cnt > 1) {
      r += cnt * (cnt -1) / 2;
    }
  }
  cout << r << endl;

  // For debug
  // cout << N << endl;
  // rep(i, N) {
  //   cout << s[i];
  // }
}
