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

struct state {
  ll room;
  ll te;
  ll x; // passed time.
  state(ll room, ll te, ll x) : room(room), te(te), x(x) {}
};

ll n, m, x;
vector<ll> d;

bool operator<(const state& a, const state& b) {
  return d[a.room*x + a.x] > d[b.room*x + b.x];
}

struct edge {
  ll from;
  ll to;
  ll cost;
  edge(ll from, ll to, ll cost) : from(from), to(to), cost(cost) {}
};
vector<vector<edge>> g;

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  cin >> n >> m >> x;
  g.resize(n);
  d.assign((n+1)*x*3, INF);
  vector<ll> t(n);

  rep(i,n) {
    cin >> t[i];
  }
  rep(iter,m) {
    ll a, b, cost;
    cin >> a >> b >> cost;
    --a;--b;
    g[a].push_back(edge(a,b,cost));
    g[b].push_back(edge(b,a,cost));
  }
  // printvec(t);
  // printtree(g);

  priority_queue<pair<ll,state>, vector<pair<ll,state>>, greater<pair<ll,state>>> q;
  d[0] = 0;
  q.push({ 0, state(0,0, 0) });
  while (!q.empty()) {
    auto p = q.top(); q.pop();
    ll dist = p.first;
    state s = p.second;
    if (dist > d[s.room*x*3 + s.x*3 + s.te]) { continue; } // too large
    for (edge& e : g[s.room]) {
      if (s.te == 0 && t[e.to] == 2 && (s.x+e.cost) < x) { continue; } // invalid
      if (s.te == 2 && t[e.to] == 0 && (s.x+e.cost) < x) { continue; } // invalid
      // Here, valid.
      state nextS = state(e.to, s.te, min(s.x+e.cost, x-1));
      if (s.te == 0) {
        if (t[e.to] == 2) { nextS.te = 2; nextS.x = 0; }
        if (t[e.to] == 0) { nextS.x = 0; }
      }
      if (s.te == 2) {
        if (t[e.to] == 0) { nextS.te = 0; nextS.x = 0; }
        if (t[e.to] == 2) { nextS.x = 0; }
      }
      if (d[nextS.room*x*3 + nextS.x*3 + nextS.te] > dist + e.cost) {
        d[nextS.room*x*3 + nextS.x*3 + nextS.te] = dist + e.cost;
        q.push({ dist + e.cost, nextS });
        // cout << "s(room,x): " << s.room << "," << s.x << endl;
        // cout << "d[s(room,x)]: " << dist << endl;
        // cout << "nextS(room,x): " << nextS.room << "," << nextS.x << endl;
        // cout << "d[nextS(room,x)]: " << dist + e.cost << endl;
      }
    }
  }
  ll ans = INF;
  rep(i,x+1) {
    rep(j,3) {
      chmin(ans, d[(n-1)*x*3 + i*3 + j]);
    }
  }
  cout << ans << endl;
}
