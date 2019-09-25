#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <unordered_map>

using namespace std;

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

typedef long long ll;
typedef unsigned long long ull;

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
    posMap[c].push_back(i + s_len); // To check the cycle case.
  }
  rep(i, 26) {
    sort(all(posMap[i]));
  }

  int p = -1;
  ll ans = 0;
  int t_len = t.size();
  rep(i, t_len) {
    int c = t[i] - 'a';
    if (posMap[c].size() == 0) { // Impossible
      cout << -1 << endl;
      return 0;
    }

    p = *upper_bound(all(posMap[c]), p);
    if (p >= s_len) { // If p is larger than first s_len values in posMap[c], we have to cycle.
      p -= s_len;
      ans += s_len;
    }
  }
  ans += p;
  cout << ans + 1 << endl;
}
