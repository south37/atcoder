// ref. https://phyllo-algo.hatenadiary.org/entry/20140813/1407932963
// ref. https://tenka1.klab.jp/2014/explain/quala_c.html

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string.h>
#include <set>
#include <stack>

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

const ll INF = 1e15;
const ll MOD = 1000000007;  // 1e9 + 7

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n,m;
  cin >> n >> m;
  vector<string> p(n);
  rep(i,n) {
    cin >> p[i];
  }

  vector<vector<bool>> can(n,vector<bool>(n)); // can[i][j] .. can be same
  rep(i,n)rep(j,n) {
    if (i == j) {
      can[i][j] = true;
    } else {
      bool ok = true;
      rep(l,m) {
        if (p[i][l] == '*') { continue; }
        if (p[j][l] == '*') { continue; }
        if (p[i][l] != p[j][l]) {
          ok = false;
          break;
        }
      }
      can[i][j] = ok;
      can[j][i] = ok;
    }
  }
  // printtree(can);

  vector<bool> dp(1<<n); // dp[i] .. i is bit representation.i is ok.
  rep(i,1<<n) {
    bool ok = true;
    rep(j,n)rep(k,n) {
      if ((i>>j&1) && (i>>k&1)) { // j and k is in i.
        if (!can[j][k]) {
          ok = false;
          break;
        }
      }
    }
    dp[i] = ok;
  }
  // printvec(dp);

  vector<ll> dp2(1<<n, INF); // dp2[i] .. min count to make i.
  dp2[0] = 0;
  rep(mask,1<<n) {
    for (int mask2 = mask; mask2 > 0; mask2=(mask2-1)&mask) {
      if (dp[mask2] && dp2[mask^mask2] != INF) { // mask2 is valid. dp2[mask^mask2] is ok.
        chmin(dp2[mask], dp2[mask^mask2] + 1);
      }
    }
  }
  cout << dp2[(1<<n)-1] << endl;
}
