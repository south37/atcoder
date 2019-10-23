#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string.h>
#include <set>

using namespace std;

#define COUT(x) cout << #x << " = " << (x) << " (L" << __LINE__ << ")" << endl

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

int main(int argc, char** argv) {
  string s;
  cin >> s;
  const int n = s.size();
  s = "." + s; // 1-indexed

  if (s[1] == '0') { // s[1] must be 1
    cout << -1 << endl;
    return 0;
  }
  if (s[n] == '1') { // s[n] must be 0
    cout << -1 << endl;
    return 0;
  }
  for (int i = 1; i < n; ++i) {
    if (s[i] != s[n-i]) { // s[i] must be same with s[n-i]
      cout << -1 << endl;
      return 0;
    }
  }

  // Here, s is valid. We make a tree called Caterpillar.
  queue<int> ones; // A container which contains the indices where s[i] == '1'
  for (int i = 1; i < n; ++i) {
    if (s[i] == '1') {
      ones.push(i);
    }
  }
  ones.push(n); // We treat n as the member of ones. This is the root.

  for (int i = 1; i < n; ++i) {
    if (i == ones.front()) { // i is in ones
      ones.pop();
    }
    cout << i << " " << ones.front() << endl;
  }
}
