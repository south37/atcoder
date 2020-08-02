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

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

// URDL = 0123

ll g(vector<P> a) {
  sort(all(a));
  ll res = INF;
  rep(i, a.size()-1) {
    if (a[i].second == 0 && a[i+1].second != 0) {
      chmin(res, a[i+1].first-a[i].first);
    }
  }
  return res;
}

ll f(map<ll,vector<P>>& mp) {
  ll res = INF;
  for (auto& p : mp) {
    chmin(res, g(p.second));
  }
  return res;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  vector<ll> x(n), y(n), dir(n);
  rep(i,n) {
    char c;
    cin >> x[i] >> y[i] >> c;
    if (c == 'U') dir[i] = 0;
    if (c == 'R') dir[i] = 1;
    if (c == 'D') dir[i] = 2;
    if (c == 'L') dir[i] = 3;
  }

  ll ans = INF;
  rep(ri,4) {
    { // UD
      map<ll,vector<P>> mp;
      rep(i,n) {
        if (dir[i] != 0 && dir[i] != 2) { continue; }
        // Here, dir[i] == 0 || dir[i] == 2
        mp[x[i]].emplace_back(y[i],dir[i]);
      }
      chmin(ans, f(mp)*5);
    }
    { // UR
      map<ll,vector<P>> mp;
      rep(i,n) {
        if (dir[i] != 0 && dir[i] != 1) { continue; }
        // Here, dir[i] == 0 || dir[i] == 1
        mp[x[i]+y[i]].emplace_back(y[i],dir[i]);
      }
      chmin(ans, f(mp)*10);
    }
    // rotate 90 deg. clockwise.
    rep(i,n) {
      ll px = x[i], py = y[i];
      x[i] = py;
      y[i] = -px;
      dir[i] = (dir[i]+1)%4;
    }
  }

  if (ans == INF) { // not hit
    cout << "SAFE" << endl;
  } else {
    cout << ans << endl;
  }
}
