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

const ll MAX_N = 105;
const ll MAX_W = 10005;
const ll MAX_C = 55;
// dp[i][j][k][c] .. using [0,i), j is weight, k is last selected position, c is count.
int dp[MAX_W][MAX_N][MAX_C];

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

  rep(i,N) {
    int w,v,ci;
    tie(ci,w,v) = ts[i];

    for (int j = W; j >= 0; --j) {
      rep(k,i+1)rep(c,C+1) {
        int nj = j+w;
        int nk = i+1; // 1-indexed
        int nc = c;
        if (k == 0 || ci != get<0>(ts[k-1])) { // different color
          ++nc;
        }
        if (nj > W) { continue; }
        if (nc > C) { continue; }
        // cout << "nj:" << nj << endl;
        // cout << "nk:" << nk << endl;
        // cout << "nc:" << nc << endl;
        // cout << "j:" << j << endl;
        // cout << "k:" << k << endl;
        // cout << "c:" << c << endl;
        // cout << "c:" << c << endl;
        chmax(dp[nj][nk][nc], dp[j][k][c] + v);
      }
    }
  }

  int ans = 0;
  rep(j,W+1)rep(k,N+1)rep(c,C+1) {
    chmax(ans, dp[j][k][c]);
  }
  cout << ans << endl;
}
