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

vector<ll> build_z(const string& s) {
  ll n = s.size();
  vector<ll> z(n, 0);
  ll l = -1, r = -1;
  for (ll i = 1; i < n; ++i) {
    if (i <= r) {
      z[i] = min<ll>(r - i + 1, z[i - l]);
    }
    while (i + z[i] < n && s[i + z[i]] == s[z[i]]) {
      ++z[i];
    }
    if (i + z[i] - 1 > r) {
      r = i + z[i] - 1;
      l = i;
    }
  }
  return z;
}

// void search(const string& text, const string& pattern, vector<ll>& result) {
//   vector<ll> z = build_z(pattern + "$" + text);
//
//   ll p = pattern.length();
//   for (ll i = p + 1; i < z.size(); ++i) {
//     if (z[i] == p) {
//       result.push_back(i-p-1);
//     }
//   }
// }
//
// int main(int argc, char** argv) {
//   string s, t;
//   cin >> s;
//   cin >> t;
//
//   vector<ll> matches;
//   search(s, t, matches);
//
//   for (ll idx : matches) {
//     cout << idx << endl;
//   }
//
//   cout << s << endl;
//   cout << t << endl;
// }

vector<bool> ok;
vector<int> to;
// state[i] .. 0 .. pre, 1 .. intermediate, 2 .. visited.
vector<int> state;
vector<int> dp;

ll dfs(ll v) {
  if (state[v] == 1) { return -1; } // cycle found
  if (state[v] == 2) { return dp[v]; } // already visited
  if (to[v] < 0) { // last
    state[v] = 2;
    return dp[v] = 0;
  }

  state[v] = 1;
  ll ret;
  ll nex = dfs(to[v]);
  if (nex < 0) { // cycle
    ret = -1;
  } else {
    ret = nex+1;
  }
  state[v] = 2;
  return dp[v] = ret;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  string s;
  string t;
  cin >> s;
  cin >> t;
  ll n = s.size();
  ll m = t.size();

  string r = s;
  while (r.size() < n+m) {
    r += s;
  }
  // cout << "r:" << r << endl;

  vector<ll> z = build_z(t+"$"+r);
  // printvec(z);

  ok.resize(n);
  rep(i,n) {
    if (z[m+1+i] == m) {
      ok[i] = true;
    }
  }
  to.assign(n, -1);
  rep(i,n) {
    if (ok[i]) {
      to[i] = (i+m)%n;
    }
  }

  // printvec(ok);
  // printvec(to);

  state.resize(n);
  dp.resize(n);
  ll ans = 0;
  rep(i,n) {
    ll now = dfs(i);
    if (now == -1) { // cycle
      cout << -1 << endl;
      return 0;
    }
    chmax(ans, now);
  }
  cout << ans << endl;
}
