#include <iostream>
#include <vector>

using namespace std;

#define rep(i, n) for (int i = 0; i < n; ++i)

vector<int> Zalgo(const string &S) {
  int N = (int)S.size();
  vector<int> res(N);
  res[0] = N;
  int i = 1, j = 0;
  while (i < N) {
    while (i+j < N && S[j] == S[i+j]) ++j;
    res[i] = j;
    if (j == 0) {++i; continue;}
    int k = 1;
    while (i+k < N && k+res[k] < j) res[i+k] = res[k], ++k;
    i += k, j -= k;
  }
  return res;
}

void search(string& text, string& pattern, vector<int>& result) {
  string s = pattern + "$" + text;
  int p = pattern.length();

  vector<int> Z = Zalgo(s);
  for (int i = p + 1; i < Z.size(); ++i) {
    if (Z[i] == p) {
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
