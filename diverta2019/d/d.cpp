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

  ll n;
  cin >> n;
  vector<ll> a(3);
  vector<ll> b(3);
  rep(i, 3) {
    cin >> a[i];
  }
  rep(i, 3) {
    cin >> b[i];
  }

  vector<pair<ll, ll>> ab; // diff of a->b. <cost, benefit>
  rep(i, 3) {
    if (b[i]-a[i] > 0) {
      ab.emplace_back(a[i], b[i] - a[i]);
    }
  }
  vector<pair<ll, ll>> ba; // diff of b->a. <cost, benefit>
  rep(i, 3) {
    if (a[i]-b[i] > 0) {
      ba.emplace_back(b[i], a[i] - b[i]);
    }
  }

  vector<vector<pair<ll, ll>>> trades;
  trades.push_back(ab);
  trades.push_back(ba);
  for (auto& trade : trades) {
    // Here, we do knapsack of trade
    if (trade.size() > 0) {
      // dp[w] .. maximum benefit when using [0,i) and cost is w.
      vector<ll> dp(n+1);
      rep(i, trade.size()) {
        ll cost    = trade[i].first;
        ll benefit = trade[i].second;

        // Here, we calculate dp[i+1]
        rep(w, n+1) { // loop in [0, n]
          if (w-cost >= 0) {
            chmax(dp[w], dp[w-cost] + benefit);
          }
        }
      }

      ll gain = 0;
      // Here, maximum value in dp is maximum gain
      rep(w, n+1) { // loop in [0, n]
        chmax(gain, dp[w]);
      }
      n += gain;
    }
  }

  cout << n << endl;
}
