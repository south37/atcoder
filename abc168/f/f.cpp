// ref. https://www.youtube.com/watch?v=MXOSqPzsiqo&feature=youtu.be

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

struct L {
  int a, b, c; // line of (a,c) and (b,c)
  L(int a=0, int b=0, int c=0) : a(a), b(b), c(c) {}
};

const int dx[] = { -1, 0, 1, 0 };
const int dy[] = { 0, -1, 0, 1 };

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n,m;
  cin >> n >> m;
  map<int,int> mpX, mpY; // { location => id }
  mpX[0] = 0; mpY[0] = 0; // (0,0)
  vector<L> lh, lv;

  rep(i,n) {
    int a,b,c;
    cin >> a >> b >> c;
    mpX[a] = 0;
    mpX[b] = 0;
    mpY[c] = 0;
    lh.emplace_back(a,b,c);
  }
  rep(i,m) {
    int a,b,c;
    cin >> c >> a >> b;
    mpY[a] = 0;
    mpY[b] = 0;
    mpX[c] = 0;
    lv.emplace_back(a,b,c);
  }

  vector<int> xs, ys; // { id => location }
  for (auto& p : mpX) {
    p.second = xs.size();
    xs.push_back(p.first);
  }
  for (auto& p : mpY) {
    p.second = ys.size();
    ys.push_back(p.first);
  }

  int h = xs.size()*2;
  int w = ys.size()*2;
  vector<vector<int>> d(h, vector<int>(w));
  rep(i,n) {
    int a = mpX[lh[i].a]*2;
    int b = mpX[lh[i].b]*2;
    int c = mpY[lh[i].c]*2;
    for (int x = a; x <= b; ++x) { d[x][c] = -1; }
  }
  rep(i,m) {
    int a = mpY[lv[i].a]*2;
    int b = mpY[lv[i].b]*2;
    int c = mpX[lv[i].c]*2;
    for (int y = a; y <= b; ++y) { d[c][y] = -1; }
  }

  // BFS
  queue<P> q;
  int sx = mpX[0]*2, sy = mpY[0]*2;
  d[sx][sy] = 1;
  q.emplace(sx,sy);
  while (!q.empty()) {
    int x = q.front().first;
    int y = q.front().second;
    q.pop();
    rep(v,4) {
      int nx = x+dx[v], ny = y+dy[v];
      if (nx < 0 || nx >= h || ny < 0 || ny >= w) { continue; }
      if (d[nx][ny] != 0) { continue; }
      d[nx][ny] = 1;
      q.emplace(nx,ny);
    }
  }

  ll ans = 0;
  rep(x,h)rep(y,w) {
    if (d[x][y] != 1) { continue; }
    if (x == 0 || x == h-1 || y == 0 || y == w-1) {
      cout << "INF" << endl;
      return 0;
    }
    if (x%2 == 0 || y%2 == 0) { continue; } // if even, this is wall.
    ll ex = xs[x/2+1]-xs[x/2];
    ll ey = ys[y/2+1]-ys[y/2];
    ans += ex*ey;
  }
  cout << ans << endl;
}
