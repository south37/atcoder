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

ll n;
vector<vector<ll>> dist;
vector<vector<ll>> g;

void calcDist(int s) {
  // cout << "s: " << s << endl;

  // Here, calculate distance from v.
  queue<P> q;
  dist[s][s] = 0;
  q.emplace(s, 0);
  while(!q.empty()) {
    auto p = q.front(); q.pop();
    int v = p.first;
    int d = p.second;
    // cout << "(v,d):" << v << "," << d << endl;
    for (int nv : g[v]) {
      if (dist[s][nv] < INF) { continue; } // skip already calculated
      dist[s][nv] = d+1;
      q.emplace(nv, d+1);
    }
  }

  // Here, all dist[s][x] is calculated
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n, x, y;
  cin >> n >> x >> y;
  --x; --y;
  g.resize(n);
  dist = vector<vector<ll>>(n, vector<ll>(n, INF)); // min distance of (i, j)

  rep(i, n-1) {
    g[i].push_back(i+1);
    g[i+1].push_back(i);
  }
  g[x].push_back(y);
  g[y].push_back(x);

  // cout << "g:" << endl;
  // printtree(g);

  // Here, calculate the cont of each
  vector<ll> ans(n+1); // ans[i] .. ans for i. 1-indexied
  for (int i = 1; i <= n; ++i) {
    ans[i] = n-i;
  }
  // cout << "ans:" << endl;
  // printvec(ans);

  // Here, we calculate the min distance from each i to j.
  rep(s, n) {
    calcDist(s);
  }

  // cout << "dis:" << endl;
  // printtree(dist);

  rep(l, n) {
    for (int r = l + 1; r < n; ++r) {
      // Here, check (l, r) pair
      ll oldDist = r - l;
      ll newDist = dist[r][l];
      --ans[oldDist];
      ++ans[newDist];
    }
  }

  for (int i = 1; i < n; ++i) {
    cout << ans[i] << endl;
  }
}
