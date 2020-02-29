// ref. https://codeforces.com/contest/1313/submission/71676206

#include <iostream>
#include <vector>

using namespace std;

#define rep(i, n) for (int i = 0; i < n; ++i)

vector<int> build_z(const string& s) {
  int n = s.size();
  vector<int> z(n, 0);
  int l = -1, r = -1;
  for (int i = 1; i < n; ++i) {
    if (i <= r) {
      z[i] = min<int>(r - i + 1, z[i - l]);
    }
    while (i + z[i] < n && s[i + z[i]] == s[z[i]]) {
      ++z[i];
    }
    if (i + z[i] - 1 > r) {
      r = i + z[i] - 1;
      l = i;
    }
  }
  return z;
}

void search(const string& text, const string& pattern, vector<int>& result) {
  vector<int> z = build_z(pattern + "$" + text);

  int p = pattern.length();
  for (int i = p + 1; i < z.size(); ++i) {
    if (z[i] == p) {
      result.push_back(i-p-1);
    }
  }
}

int main(int argc, char** argv) {
  string s, t;
  cin >> s;
  cin >> t;

  vector<int> matches;
  search(s, t, matches);

  for (auto e : matches) {
    cout << e << endl;
  }

  cout << s << endl;
  cout << t << endl;
}
