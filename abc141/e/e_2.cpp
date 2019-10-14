// base: http://drken1215.hatenablog.com/entry/2019/09/16/014600

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>
#include <string.h>

using namespace std;

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

typedef long long ll;
typedef pair<int, int> P;
typedef tuple<int, int, int> triple;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

ll powmod(ll x, ll y) {
  ll r = 1;
  while (y) {
    if (y & 1) {
      r = r * x % MOD;
    }
    x = x * x % MOD;
    y >>= 1;
  }
  return r;
}

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

int main(int argc, char** argv) {
  int N;
  cin >> N;
  string S;
  cin >> S;

  int ans = 0;
  for (int i = 1; i < N; ++i) {
    string T = S.substr(i) + "$" + S.substr(0, i);
    vector<int> lcp = Zalgo(T);
    for (int j = N - i + 1; j <= N; ++j) {
      ans = max(ans, lcp[j]);
    }
  }

  cout << ans << endl;
}
