// base. https://atcoder.jp/contests/nikkei2019-2-qual/submissions/8368129

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

template<class T> void printvec(const vector<T>& v) {
  for (auto x : v) { cout << x << " "; }
  cout << endl;
}
template<class T> void printtree(const vector< vector<T> >& tree) {
  for (long long i = 0; i < tree.size(); ++i) {
    cout << i + 1 << ": "; printvec(tree[i]);
  }
}
template<class T, class U> void printmap(const map<T, U>& mp) {
  for (auto x : mp) { cout << x.first << "=>" << x.second << endl; }
}

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }

#define rep(i, n) for(ll i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()
#define fr first
#define sc second
#define mp make_pair
#define pb push_back

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  int n;
  cin >> n;
  int ln = (n + 1) / 2, rn = n + 1 - ln;
  vector< vector<int> > g0(rn, vector<int>(rn, -1));
  vector< vector<int> > g1(rn, vector<int>(rn, -1));
  // Next, calculate abs(j - i) of each (i, j)
  for (int i = 1; i < n; ++i) {
    string s;
    cin >> s;
    for (int j = 1; j < n; ++j) {
      char c = s[j-1];
      if (c == '?') { continue; }
      int f = (c == 'o') ? 1 : 0; // o or x
      int d0 = abs(j - i); // e.g. (j = 3, i = 1) => (d0 = 2)
      int d1 = n - abs(j + i - n); // e.g. (j = 3, i = 1, n = 6) => (d1 = 4)

      // We treat 2 groups(even group and odd group) independently.
      if (d0 % 2 == 0) {
        d0 /= 2; d1 /= 2; // compress
        if (g0[d0][d1] == 1 - f) { // Inconsistent
          cout << 0 << endl;
          return 0;
        }
        g0[d0][d1] = g0[d1][d0] = f;
      } else {
        d0 /= 2; d1 /= 2; // compress
        if (g1[d0][d1] == 1 - f) {
          cout << 0 << endl;
          return 0;
        }
        g1[d0][d1] = g1[d1][d0] = f;
      }
    }
  }

  mint ans = solve(g0) * solve(g1);
  cout << ans.x << endl;
  return 0;
}
