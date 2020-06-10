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

ll dx[6] = { 1, -1, 0, 0, 1, -1 };
ll dy[6] = { 0, 0, 1, -1, 1, 1 };

const ll MAX_D = 410;
const ll offset = 205;

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n,X,Y;
  cin >> n >> X >> Y;
  vector<vector<bool>> isObs(MAX_D, vector<bool>(MAX_D));
  rep(i,n) {
    ll x,y;
    cin >> x >> y;
    isObs[x+offset][y+offset] = true;
  }
  // rep(i,MAX_D) {
  //   printvec(isObs[i]);
  // }

  vector<vector<ll>> d(MAX_D, vector<ll>(MAX_D,INF));
  d[offset][offset] = 0; // (0,0). with offset.
  queue<P> q; // <x,y>
  q.push(P(offset,offset));
  while (!q.empty()) {
    auto p = q.front(); q.pop();
    ll x = p.first; // with offset
    ll y = p.second; // with offset
    if (x-offset == X && y-offset == Y) { // found
      cout << d[x][y] << endl;
      return 0;
    }
    rep(i,6) {
      ll nx = x + dx[i];
      ll ny = y + dy[i];
      if (nx < 0 || nx >= MAX_D || ny < 0 || ny >= MAX_D) { continue; }
      if (isObs[nx][ny]) { continue; } // is obj
      if (d[nx][ny] != INF) { continue; } // already visited
      d[nx][ny] = d[x][y]+1;
      // cout << "(x,y)" << x-offset << "," << y-offset << endl;
      // cout << "(nx,ny)" << nx-offset << "," << ny-offset << endl;
      // cout << "d[nx][ny]" << d[nx][ny] << endl;
      q.push(P(nx,ny));
    }
  }
  cout << -1 << endl;
}
