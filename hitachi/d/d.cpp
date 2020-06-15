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

const ll INF = 1e15;
const ll MOD = 1000000007;  // 1e9 + 7

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n,T;
  cin >> n >> T;
  vector<ll> zeros; // b with a = 0
  vector<P> ps;
  rep(i,n) {
    ll a,b;
    cin >> a >> b;
    if (a == 0) {
      zeros.push_back(b);
    } else {
      ps.emplace_back(a,b);
    }
  }
  sort(all(ps), [&](const P& p1, const P& p2) {
    // p1.first/(p1.second+1) > p2.first/(p2.second+1)
    return p1.first * (p2.second+1) > p2.first * (p1.second+1);
  });
  sort(all(zeros));

  // For Debug
  // for (auto& p : ps) {
  //   cout << "a,b:" << p.first << "," << p.second << endl;
  //   cout << (double)p.first/(p.second+1) << endl;
  // }

  // Here, start DP in ps.
  // dp[i][j] .. using [0,i), count is j. min cost.
  ll m = ps.size();
  // vector<vector<ll>> dp(m+1, vector<ll>(31, INF));
  vector<ll> dp(31, INF);
  dp[0] = 0;
  rep(i,m) {
    for (ll j = 30; j > 0; --j) {
      ll t = dp[j-1]; // j > 0
      if (t == INF) { continue; } // j-1 is invalid.
      ll ai = ps[i].first;
      ll bi = ps[i].second;
      ll now = (ai+1)*t + (ai+bi+1); // cost for achieve j+1
      if (now > T) { continue; } // t must be equal or lower than T.
      chmin(dp[j], now);
    }
  }

  // printvec(dp);

  ll ans = 0;
  rep(i,31) {
    if (dp[i] <= T) {
      ll now = i; // current value.

      // Here, add b in greedy way.
      ll t = dp[i];
      for (ll b : zeros) {
        ll nt = t + b + 1; // next t
        if (nt <= T) {
          t = nt;
          ++now;
        }
      }
      chmax(ans,now);
    }
  }

  cout << ans << endl;
}
