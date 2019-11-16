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

  ll n, t;
  cin >> n >> t;
  vector<ll> a(n); // cost
  vector<ll> b(n); // profit
  rep(i, n) {
    ll aa, bb;
    cin >> a[i] >> b[i];
  }
  // printvec(a);
  // printvec(b);

  vector<P> dishes;
  rep(i, n) {
    dishes.emplace_back(b[i], a[i]);
  }
  sort(all(dishes));
  reverse(all(dishes));
  // Now, dishes are sorted in decreasing order of profit. If profit is same, then higher t is in ftont.

  // cout << "dishes: " << endl;
  // rep(i, n) {
  //   cout << dishes[i].fr << ", " << dishes[i].sc << endl;
  // }

  ll ans = 0;
  rep(selected_i, 10) {
    if (selected_i >= n) { continue; }

    P p = dishes[selected_i];
    // Now, we use dished[1..-1] for napsack dp.

    // Limit is t-1.

    set<ll> selected;

    vector<ll> dp(t + 1, 0);
    // dp[i][j] .. the maximum profit by using item <= i and cost <= j.
    for (int i = 0; i < n; ++i) {
      if (i == selected_i) { continue; } // skip

      ll cost = dishes[i].sc; // cost
      ll profit = dishes[i].fr; // profit

      for (int j = t - 1; j >= 0; --j) { // reverse because only one in each item
        if ((j - cost) >= 0) {
          dp[j] = max(dp[j], dp[j - cost] + profit);
        }
      }
    }
    // cout << "dp: "; printvec(dp);
    // Here, dp[n-1][t] is the maximum profit.

    chmax(ans, dp[t-1] + p.fr);
  }
  cout << ans << endl;
}
