// ref. https://www.youtube.com/watch?v=bHzohtVsG0Q&feature=youtu.be

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

const int MX = 2005;
bool d[3][3][MX]; // d[i][j][k] .. check (i,j) pair with k diff

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  vector<string> s(3);
  rep(i, 3) {
    cin >> s[i];
  }

  int ans = 3 * MX;
  sort(s.begin(), s.end());
  do {
    rep(i,3)rep(j,3)rep(k,s[i].size()) {
      if (i >= j) { continue; } // only check (i < j)

      // Check (i,j) pair with k difference.
      // check s[i][ni] and s[j][nj]. nj = ni-k.
      bool ok = true;
      for (int ni = k; ni < s[i].size(); ++ni) {
        int nj = ni-k;
        if (nj > s[j].size()) { break; }
        if (s[i][ni] == '?' || s[j][nj] == '?') { continue; }
        if (s[i][ni] != s[j][nj]) { ok = false; }
      }
      d[i][j][k] = ok;
    }

    auto f = [&](int i, int j, int k) {
      // If diff is larger thant the size of i, it is true.
      if (k >= s[i].size()) { return true; }
      return d[i][j][k];
    };

    rep(x,MX)rep(y,MX) {
      // diff x at (0,1), diff y at (1,2)
      if (!f(0,1,x)) { continue; }
      if (!f(1,2,y)) { continue; }
      if (!f(0,2,x+y)) { continue; }
      int now = 0;
      now = max<int>(now, s[0].size());
      now = max<int>(now, x+s[1].size());
      now = max<int>(now, x+y+s[2].size());
      ans = min(ans, now);
    }
  } while (next_permutation(s.begin(), s.end()));
  cout << ans << endl;
  return 0;
}
