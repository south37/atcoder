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

const ll INF = 1e13;
const ll MOD = 1000000007;  // 1e9 + 7

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  cout << setprecision(10) << fixed;

  ll xs, ys, xt, yt;
  cin >> xs >> ys >> xt >> yt;
  vector<triple> t; // <x,y,r>
  t.emplace_back(xs, ys, 0);
  t.emplace_back(xt, yt, 0);
  ll n;
  cin >> n;
  rep(i, n) {
    ll x, y, r;
    cin >> x >> y >> r;
    t.emplace_back(x, y, r);
  }

  // rep(i, n+2) {
  //   ll xi, yi, ri;
  //   tie(xi, yi, ri) = t[i];
  //   cout << xi << "," << yi << "," << ri << endl;
  // }

  // Here, calculate the distance.
  // dist[i][j] .. distance of i and j
  vector<vector<double>> dist(n+2, vector<double>(n+2));
  rep(i, n+2) rep(j, i) {
    ll xi, yi, ri;
    tie(xi, yi, ri) = t[i];
    ll xj, yj, rj;
    tie(xj, yj, rj) = t[j];
    double xdiff = abs(xi-xj);
    double ydiff = abs(yi-yj);
    double r = ri + rj;
    double d = sqrt(xdiff*xdiff + ydiff*ydiff) - r;
    // cout << "d: " << d << endl;
    chmax(dist[i][j], d);
    chmax(dist[j][i], d);
  }
  // printtree(dist);

  // Here, we do dijkstra
  vector<double> d(n+2, INF);
  d[0] = 0;
  priority_queue<pair<double, ll>, vector<pair<double, ll>>, greater<pair<double, ll>>> q; // <dist, index>
  q.push({ 0, 0 });
  while (!q.empty()) {
    auto p = q.top(); q.pop();
    double nd = p.first;
    ll v = p.second;
    if (nd > d[v]) { continue; } // already large
    rep(nv, n+2) {
      if (nv == v) { continue; } // skip same
      if (d[nv] > d[v] + dist[v][nv]) {
        d[nv] = d[v] + dist[v][nv];
        q.push(pair<double, ll>(d[nv], nv));
      }
    }
  }
  cout << d[1] << endl;
}
