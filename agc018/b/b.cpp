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

  ll n, m;
  cin >> n >> m;
  vector<vector<ll>> a(n, vector<ll>(m));
  rep(i, n) {
    rep(j, m) {
      cin >> a[i][j];
      --a[i][j]; // 0-indexed
    }
  }
  // cout << "a:" << endl;
  // printtree(a);

  set<ll> hidden;
  ll ans = INF;
  rep(iter, m) { // loop for the number of sports
    // Here, we calculate the most populate one.
    vector<ll> cnts(m);
    rep(i, n) {
      // cout << i << ": ";
      rep(j, m) {
        if (hidden.find(a[i][j]) == hidden.end()) { // not in hidden
          ++cnts[a[i][j]];
          // cout << a[i][j] << endl;
          break;
        }
      }
    }
    // cout << "cnts: "; printvec(cnts);

    // Here, we want to know the maximum count
    ll maxCnt = 0;
    ll popularSport;
    rep(i, m) {
      if (maxCnt < cnts[i]) {
        maxCnt = cnts[i];
        popularSport = i;
      }
    }

    ans = min(ans, maxCnt); // update by current maxCnt
    hidden.insert(popularSport);
  }

  cout << ans << endl;
}
