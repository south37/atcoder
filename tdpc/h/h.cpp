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

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()
#define sz(x) (ll)(x).size()
#define fr first
#define sc second
#define mp make_pair
#define pb push_back
#define eb emplace_back

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;
typedef vector<ll> vl;
typedef vector<P> vp;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

const ll MAX_W = 10005;
const ll MAX_C = 55;
// dp[j][k][c] .. using [0,i), j is weight, k is last selected color, c is count of colors.
int dp[MAX_W][MAX_C][MAX_C];

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  int N,W,C;
  cin >> N >> W >> C;
  vector<triple> ts; // tuple of <color, weight, value>
  rep(i,N) {
    int w,v,c;
    cin >> w >> v >> c;
    ts.emplace_back(c,w,v);
  }
  sort(all(ts));

  // rep(i,N) {
  //   ll w,v,c;
  //   tie(c,w,v) = ts[i];
  //   cout << w << "," << v << "," << c << endl;
  // }

  rep(j,W+1)rep(c,C+1)rep(last_c,MAX_C) {
    dp[j][c][last_c] = -1;
  }
  dp[0][0][0] = 0;

  rep(i,N) {
    int w,v,ci;
    tie(ci,w,v) = ts[i];

    for (int j = W-w; j >= 0; --j) {
      for (int c = C; c >= 0; --c) {
        rep(last_c, ci+1) { // Here, we need to check only colors in [0,ci].
          int nj = j+w;
          int nc = c;
          if (last_c != ci) { // different color.
            ++nc;
          }
          if (nc > C) { continue; }
          if (dp[j][c][last_c] != -1) {
            chmax(dp[nj][nc][ci], dp[j][c][last_c] + v);
          }
        }
      }
    }
  }

  int ans = 0;
  rep(j,W+1)rep(c,C+1)rep(last_c,MAX_C) {
    chmax(ans, dp[j][c][last_c]);
  }
  cout << ans << endl;
}
