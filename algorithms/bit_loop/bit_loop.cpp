#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <cassert>

using namespace std;

#define rep(i, n) for(int64_t i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

int main(int argc, char** argv) {
  int n;
  cin >> n;

  rep(bit, 1LL << n) {
    vector<int> s;
    rep(i, n) {
      if (bit & (1LL << i)) {
        s.push_back(i);
      }
    }

    cout << bit << ": { ";
    rep(i, s.size()) {
      cout << s[i] << " ";
    }
    cout << "}" << endl;
  }
}
