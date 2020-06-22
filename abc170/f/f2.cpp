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

ll dr[4] = { 1, -1, 0, 0 };
ll dc[4] = { 0, 0, 1, -1 };

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll h,w,k;
  cin >> h >> w >> k;
  ll r1,c1,r2,c2;
  cin >> r1 >> c1 >> r2 >> c2;
  --r1; --c1; --r2; --c2;
  vector<string> mp(h);
  rep(r,h) {
    cin >> mp[r];
  }

  // For Debug
  // rep(r,h) {
  //   cout << mp[r] << endl;
  // }

  // BFS
  vector<vector<ll>> d(h, vector<ll>(w, INF));
  queue<P> q;
  q.emplace(r1,c1);
  d[r1][c1] = 0;
  while (!q.empty()) {
    P p = q.front(); q.pop();
    ll r = p.first;
    ll c = p.second;

    if (p.first == r2 && p.second == c2) { // found
      cout << d[r2][c2] << endl;
      return 0;
    }
    // Visit 4-directions
    rep(i,4) {
      for (ll j = 1; j <= k; ++j) {
        ll nr = r + dr[i]*j;
        ll nc = c + dc[i]*j;
        if (nr < 0 || nr >= h || nc < 0 || nc >= w) { break; } // invalid
        // cout << "(r,c): " << r << "," << c << endl;
        // cout << "(nr,nc): " << nr << "," << nc << endl;
        // cout << "mp[nr][nc]: " << mp[nr][nc] << endl;
        if (mp[nr][nc] == '@') { break; } // reached to leaf
        if (d[nr][nc] <= d[r][c]) { break; } // (nr,nc) is small. We don't check further
        // Here, "d[nr][nc] == INF" or "d[nr][nc] == d[r][c]+1"
        if (d[nr][nc] == INF) { // not visited
          d[nr][nc] = d[r][c] + 1;
          q.emplace(nr,nc);
        }
      }
    }
  }

  // rep(r,h) {
  //   printvec(d[r]);
  // }

  // Here, we can not reach to (r2,c2)
  cout << -1 << endl;
}
