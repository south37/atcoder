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

  ll n;
  cin >> n;
  vector<vector<ll>> a(n,vector<ll>(n));
  rep(i,n)rep(j,n) {
    cin >> a[i][j];
  }

  vector<vector<ll>> d(n,vector<ll>(n, INF));
  rep(i,n) { d[i][i] = 0; }
  rep(r,n)rep(c,n) {
    if (r == c) { continue; }
    bool found = false;
    rep(k,n) {
      if (k == r || k == c) { continue; }

      if (a[r][c] > a[r][k] + a[k][c]) { // invalid. a[r][c] must be minimum.
        cout << -1 << endl;
        return 0;
      }
      if (a[r][c] == a[r][k] + a[k][c]) { // a[r][c] is representable by sum of r-k + k-c.
        found = true;
      }
    }
    // cout << "a[r][c]: " << a[r][c] << endl;
    // cout << "found: " << found << endl;
    if (!found) { // a[r][c] is min
      d[r][c] = a[r][c];
    }
  }
  // printtree(d);

  vector<vector<ll>> d2 = d; // copy
  rep(k,n)rep(v,n)rep(u,n) {
    chmin(d2[v][u], d2[v][k] + d2[k][u]);
  }

  // Check the equality of d2 and a.
  bool ok = true;
  rep(r,n)rep(c,n) {
    if (d2[r][c] != a[r][c]) {
      ok = false;
      break;
    }
  }
  if (!ok) { // not valid
    cout << -1 << endl;
    return 0;
  }

  ll ans = 0;
  rep(r,n)rep(c,r) {
    if (d[r][c] != INF) {
      ans += d[r][c];
    }
  }
  cout << ans << endl;
}
