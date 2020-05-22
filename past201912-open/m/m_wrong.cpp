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
  // vector<double> vs(n);
  // vector<double> ws(n);
  // rep(i,n) {
  //   cin >> ws[i] >> vs[i];
  // }
  vector<pair<double,double>> ps(n); //pair of weight, value
  rep(i,n) {
    cin >> ps[i].first >> ps[i].second;
  }
  sort(all(ps)); // increasing order in weight

  vector<double> Vs(m); // for m
  vector<double> Ws(m);
  rep(i,m) {
    cin >> Ws[i] >> Vs[i];
  }

  vector<vector<double>> dp(n+1, vector<double>(6,-1));
  vector<vector<double>> dpV(n+1, vector<double>(6,-1));
  vector<vector<double>> dpW(n+1, vector<double>(6,-1));
  dp[0][0] = 0;
  dpV[0][0] = 0;
  dpW[0][0] = 0;

  rep(i,n) {
    double wi = ps[i].first;
    double vi = ps[i].second;
    for (ll j = 4; j >= 0; --j) { // loop in [0,4]
      rep(k,i+1) { // loop in [0,i]
        if (dpV[k][j] >= 0 && dpW[k][j] >= 0) {
          double now = (dpV[k][j]+vi)/(dpW[k][j]+wi);
          if (dp[i+1][j+1] < now) {
            dp[i+1][j+1]  = now;
            dpV[i+1][j+1] = dpV[k][j]+vi;
            dpW[i+1][j+1] = dpW[k][j]+wi;
          }
        }
      }
    }
  }

  double ans = dp[n][5];
  rep(i,m) { // try adding i
    double wi = Ws[i];
    double vi = Vs[i];
    rep(k,n+1) {
      if (dpV[k][4] >= 0 && dpW[k][4] >= 0) {
        double now = (dpV[k][4]+vi)/(dpW[k][4]+wi);
        chmax(ans, now);
      }
    }
  }
  cout << ans << endl;
}
