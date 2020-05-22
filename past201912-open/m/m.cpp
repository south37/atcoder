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
  cout << setprecision(10) << fixed;

  ll n,m;
  cin >> n >> m;
  vector<double> vs(n+m);
  vector<double> ws(n+m);
  rep(i,n+m) {
    cin >> ws[i] >> vs[i];
  }

  // printvec(ws);
  // printvec(vs);

  double ans = 0;
  rep(iter,m+1) {
    vector<pair<double,double>> ps; // pair of <weight, value>
    rep(j,n) {
      ps.emplace_back(ws[j],vs[j]);
    }
    if (iter == m) { // with no special
      // Do nothing
    } else {
      ps.emplace_back(ws[n+iter],vs[n+iter]);
    }
    sort(all(ps));

    // rep(i,ps.size()) {
    //   cout << ps[i].first << "," << ps[i].second << endl;
    // }

    vector<double> dp(6,-1);
    vector<double> dpV(6);
    vector<double> dpW(6);
    dp[0] = 0;
    rep(i,ps.size()) {
      for (ll j = 4; j >= 0; --j) { // loop in [0,4]
        double wi = ps[i].first;
        double vi = ps[i].second;
        double now = (dpV[j]+vi)/(dpW[j]+wi);
        if (dp[j] >= 0 && dp[j+1] < now) {
          dp[j+1]  = now;
          dpV[j+1] = dpV[j] + vi;
          dpW[j+1] = dpW[j] + wi;
        }
      }
    }
    chmax(ans, dp[5]);
  }
  cout << ans << endl;
}
