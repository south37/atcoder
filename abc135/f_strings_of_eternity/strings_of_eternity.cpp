#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <unordered_map>

using namespace std;

#define rep(i, n) for (int i = 0; i < n; ++i)

void getZarr(string& str, int Z[]) {
  int n = str.length();
  int L, R, k;

  L = R = 0;
  for (int i = 1; i < n; ++i) {
    if (i > R) {
      L = R = i;
      while (R < n && str[R - L] == str[R]) {
        R++;
      }
      Z[i] = R - L;
      R--;
    } else {
      k = i - L;

      if (Z[k] < R - i + 1) {
        Z[i] = Z[k];
      } else {
        L = i;
        while (R < n && str[R - L] == str[R]) {
          R++;
        }
        Z[i] = R - L;
        R--;
      }
    }
  }
}


void search(string& text, string& pattern, vector<int> *result) {
  string s = pattern + "$" + text;
  int l = s.length();

  int Z[l];
  getZarr(s, Z);

  int p = pattern.length();

  vector<int> res;
  for (int i = 0; i < l; ++i) {
    if (Z[i] == p) {
      result->push_back(i - p - 1);
    }
  }
}

int sch(int i, int stop, const string& s, const string& t, vector<int>& vm) {
  // Early check of vm[i]. If vm[i] is larger than 0, its value is alreday
  // caluculated.
  if (vm[i] > 0) { return vm[i]; }

  int j = (i + t.size()) % s.size();  // The dst of next hop.
  if (j == stop) { return -1; }  // Loop exists

  if (vm[j] < 0) { // s[j..?] matches with t
    if (sch(j, stop, s, t, vm) < 0) {
      return -1;
    }
  }
  // By calling sch, now, the positive value is set to vm[j].

  vm[i] = vm[j] + 1;
  return vm[i];
}

int main(int argc, char** argv) {
  string s, t;
  cin >> s;
  cin >> t;

  int l = s.size();

  // repeat count
  int r = 1 + ((s.size() - 1 + t.size()) / s.size());
  string reps;
  reps.reserve(r * s.size());
  rep(i, r) {
    reps += s;
  }

  // For Debug
  // cout << reps << endl;

  vector<int> matches;
  search(reps, t, &matches);

  vector<int> vm(s.size());

  for (auto i : matches) {
    if (i >= s.size()) { break; }  // Treat only i <= s.size() - 1
    vm[i] = - 1;
  }

  int loopExists = false;
  int maxSize = 0;
  for (auto i : matches) {
    if (i >= s.size()) { break; }  // Treat only i <= s.size() - 1
    int x = sch(i, i, s, t, vm);
    if (x == -1) { // There is loop
      loopExists = true;
      break;
    }
    maxSize = max(maxSize, x);
  }

  if (loopExists) {
    cout << -1 << endl;
  } else {
    cout << maxSize << endl;
  }
}
