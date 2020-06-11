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

// Minimum-cost flow
// Primal-Dual
template<typename flow_t, typename cost_t>
struct PrimalDual {
  const cost_t INF;

  struct edge {
    int to;
    flow_t cap;
    cost_t cost;
    int rev;
    bool isrev;
  };
  vector<vector<edge>> graph;
  vector<cost_t> potential, min_cost;
  vector<int> prevv, preve;

  PrimalDual(int V) : graph(V), INF(numeric_limits< cost_t >::max()) {}

  void add_edge(int from, int to, flow_t cap, cost_t cost) {
    graph[from].emplace_back((edge) {to, cap, cost, (int) graph[to].size(), false});
    graph[to].emplace_back((edge) {from, 0, -cost, (int) graph[from].size() - 1, true});
  }

  cost_t min_cost_flow(int s, int t, flow_t f) {
    int V = (int) graph.size();
    cost_t ret = 0;
    using Pi = pair< cost_t, int >;
    priority_queue< Pi, vector< Pi >, greater< Pi > > que;
    potential.assign(V, 0);
    preve.assign(V, -1);
    prevv.assign(V, -1);

    while(f > 0) {
      min_cost.assign(V, INF);
      que.emplace(0, s);
      min_cost[s] = 0;
      while(!que.empty()) {
        Pi p = que.top();
        que.pop();
        if(min_cost[p.second] < p.first) continue;
        for(int i = 0; i < graph[p.second].size(); i++) {
          edge &e = graph[p.second][i];
          cost_t nextCost = min_cost[p.second] + e.cost + potential[p.second] - potential[e.to];
          if(e.cap > 0 && min_cost[e.to] > nextCost) {
            min_cost[e.to] = nextCost;
            prevv[e.to] = p.second, preve[e.to] = i;
            que.emplace(min_cost[e.to], e.to);
          }
        }
      }
      if(min_cost[t] == INF) return -1;
      for(int v = 0; v < V; v++) potential[v] += min_cost[v];
      flow_t addflow = f;
      for(int v = t; v != s; v = prevv[v]) {
        addflow = min(addflow, graph[prevv[v]][preve[v]].cap);
      }
      f -= addflow;
      ret += addflow * potential[t];
      for(int v = t; v != s; v = prevv[v]) {
        edge &e = graph[prevv[v]][preve[v]];
        e.cap -= addflow;
        graph[v][e.rev].cap += addflow;
      }
    }
    return ret;
  }

  void output() {
    for(int i = 0; i < graph.size(); i++) {
      for(auto &e : graph[i]) {
        if(e.isrev) continue;
        auto &rev_e = graph[e.to][e.rev];
        cout << i << "->" << e.to << " (flow: " << rev_e.cap << "/" << rev_e.cap + e.cap << ")" << endl;
      }
    }
  }
};

// int main(int argc, char** argv) {
//   cin.tie(NULL);
//   cout.tie(NULL);
//   ios_base::sync_with_stdio(false);
//   //cout << setprecision(10) << fixed;
//
//   ll n,m,f;
//   cin >> n >> m >> f;
//   PrimalDual<ll,ll> g(n);
//   while (m--) {
//     ll u,v,cap,cost;
//     cin >> u >> v >> cap >> cost;
//     g.add_edge(u,v,cap,cost);
//   }
//   // Min cost from 0 to n-1. Return -1 when we can not achieve f.
//   cout << g.min_cost_flow(0,n-1,f) << endl;
// }

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n,m;
  cin >> n >> m;
  vector<ll> a(n), b(n);
  rep(i,n) {
    cin >> a[i];
  }
  rep(i,n) {
    cin >> b[i];
  }
  vector<ll> r(3);
  cin >> r[0] >> r[1] >> r[2];

  PrimalDual<ll,ll> g(n+5);
  // s = n, rounds = (n+1,n+2,n+3), t = n+4
  ll s = n, t = n+4;
  vector<ll> rounds = { n+1, n+2, n+3 };

  // s to rounds
  rep(i,3) {
    g.add_edge(s,rounds[i],m,0);
  }
  // rounds to n vertices
  rep(i,3)rep(j,n) {
    ll w = (a[j]*b[j]) % r[i];
    rep(iter,i) {
      (w *= b[j]) %= r[i];
    }
    g.add_edge(rounds[i],j,1,-w);
  }
  // n vertices to t
  rep(j,n) {
    // penalties
    vector<ll> p(3);
    p[0] = a[j]*b[j];
    p[1] = a[j]*b[j]*b[j] - p[0];
    p[2] = a[j]*b[j]*b[j]*b[j] - p[0] - p[1];

    g.add_edge(j,t,1,p[0]);
    g.add_edge(j,t,1,p[1]);
    g.add_edge(j,t,1,p[2]);
  }

  ll ans = g.min_cost_flow(s,t,3*m);
  cout << -ans << endl;
}
