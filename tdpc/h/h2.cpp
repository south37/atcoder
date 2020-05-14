// ref. http://tutuz.hateblo.jp/entry/2019/01/04/000425
// ref. https://kagamiz.hatenablog.com/entry/2013/09/04/194121

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

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll N,W,C;
  cin >> N >> W >> C;
  vector<vector<P>> item(50, vector<P>());
  rep(i,N) {
    int w,v,c;
    cin >> w >> v >> c;
    --c;
    item[c].emplace_back(w,v);
  }

  // dp[l][j] .. number of colors is l or lower, number of weight is j. max value.
  vector<vector<int>> dp(C+1, vector<int>(W+1));
  rep(i,50) {
    vector<vector<int>> dp2 = dp; // copy
    for (int l = C-1; l >= 0; --l) {
      rep(j, item[i].size()) {
        int w,v;
        tie(w,v) = item[i][j];
        for (int k = W-w; k >= 0; --k) {
          chmax(dp2[l][k+w], dp2[l][k] + v);
        }
      }
    }

    rep(l,C) {
      rep(k,W+1) {
        chmax(dp[l+1][k], dp2[l][k]); // dp2 is using one more color. Represent it by l+1.
      }
    }
  }

  cout << dp[C][W] << endl;
}
