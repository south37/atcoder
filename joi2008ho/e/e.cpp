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

// dp[y][x] .. true if tape is on this.
vector<vector<bool>> dp;

// visited[y][x] .. visited flag.
vector<vector<bool>> visited;

ll dy[4] = { 1, -1, 0, 0 };
ll dx[4] = { 0, 0, 1, -1 };

// paint
void dfs(ll y, ll x, ll maxY, ll maxX) {
  if (y < 0 || y >= maxY || x < 0 || x >= maxX) { return; } // invalid range
  if (visited[y][x]) { return; } // already painted
  if (dp[y][x]) { return; } // on tape.

  visited[y][x] = true;
  rep(i,4) {
    dfs(y+dy[i], x+dx[i], maxY, maxX);
  }
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll w,h;
  cin >> w >> h;
  ll n;
  cin >> n;
  vector<ll> xs;
  vector<ll> ys;
  vector<tuple<ll,ll,ll,ll>> tapes;
  rep(i,n) {
    ll x1,y1,x2,y2;
    cin >> x1 >> y1 >> x2 >> y2;
    tapes.emplace_back(x1,y1,x2,y2);
    xs.push_back(x1);
    xs.push_back(x2);
    ys.push_back(y1);
    ys.push_back(y2);
  }
  sort(all(xs));
  sort(all(ys));

  xs.erase(unique(all(xs)), xs.end());
  ys.erase(unique(all(ys)), ys.end());
  // printvec(xs);
  // printvec(ys);

  map<ll,ll> mpX; // position => index
  map<ll,ll> mpY;
  ll nw, nh;
  {
    ll i = 0;
    if (xs[0] > 0) { i = 1; }
    for (ll x : xs) {
      mpX[x] = i;
      ++i;
    }
    nw = i;
    if (xs[xs.size()-1] < w) {
      ++nw;
    }
  }
  {
    ll i = 0;
    if (ys[0] > 0) { i = 1; }
    for (ll y : ys) {
      mpY[y] = i;
      ++i;
    }
    nh = i;
    if (ys[ys.size()-1] < h) {
      ++nh;
    }
  }
  dp.assign(nh-1, vector<bool>(nw-1));

  // For Debug
  // printtree(dp);
  // printmap(mpX);
  // cout << "nw: " << nw << endl;
  // printmap(mpY);
  // cout << "nh: " << nh << endl;

  rep(i,ys.size()-1) {
    ll minY = ys[i];
    ll maxY = ys[i+1];
    ll nowY = mpY[minY];

    vector<P> es; // pair of <x, type>. type=0 .. open, 1 .. close
    rep(i,n) {
      ll x1,y1,x2,y2;
      tie(x1,y1,x2,y2) = tapes[i];
      if (y1 <= minY && maxY <= y2) { // in this region
        es.emplace_back(x1,0);
        es.emplace_back(x2,1);
      }
    }
    sort(all(es));
    // cout << "minY: " << minY << endl;
    // cout << "maxY: " << maxY << endl;
    // for (auto& p : es) {
    //   cout << "(" << p.first << "," << p.second << ") ";
    // }
    // cout << endl;

    ll pre = 0;
    ll cnt = 0;
    for (auto& p : es) {
      ll x = p.first;
      ll type = p.second;
      if (type == 0) { // open
        if (cnt == 0) {
          pre = x;
        }
        ++cnt;
      } else { // close
        if (cnt == 1) {
          // Here, [pre,x) is covered by tape
          for (ll j = mpX[pre]; j < mpX[x]; ++j) {
            dp[nowY][j] = true;
          }
        }
        --cnt;
      }
    }
  }
  // printtree(dp);

  visited.assign(nh-1, vector<bool>(nw-1));
  // Here, dp is calculated. Do dfs using this.
  ll ans = 0;
  rep(y,nh-1)rep(x,nw-1) {
    if (dp[y][x]) { // on tape
      continue;
    }
    if (visited[y][x]) {
      continue;
    }

    ++ans;
    dfs(y,x,nh-1,nw-1); // paint
  }
  cout << ans << endl;
}
