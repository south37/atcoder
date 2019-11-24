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

struct Edge {
  // Edge(ll i, ll e) : id(i), end(e) {}

  ll end;
  ll id;
};

vector< vector<Edge> > graph;
vector<ll> ans; // The ans of each edge. (edge id) => (color). default is -1.
ll degree; // Maximum degree of graph. This is color.

// Calculate the color of each edge
void dfs(ll v, ll parent, ll parent_edge) {
  ll color = 0; // We use color
  for (auto e : graph[v]) {
    if (e.end == parent) { continue; } // Skip parent
    // We paint color of each edge. We can select anything other than parent edge one.

    if (parent_edge == -1) { // root
      ans[e.id] = color;
      ++color;
    } else {
      if (color == ans[parent_edge]) { ++color; } // skip parent edge's color.
      ans[e.id] = color;
      ++color;
    }

    dfs(e.end, v, e.id);
  }
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  graph.resize(n);
  ans.assign(n-1, -1); // -1 is initial value.

  rep(i, n-1) {
    ll a; ll b;
    cin >> a >> b;
    --a; --b;
    graph[a].push_back({b, i});
    graph[b].push_back({a, i});
  }
  // cout << "graph: ";

  // First, we want to know the maximum degree
  rep(i, n) {
    chmax(degree, (ll)graph[i].size());
  }
  // cout << "degree: " << degree << endl;

  // Set ans by dfs
  dfs(0, -1, -1);

  cout << degree << endl;
  rep(i, ans.size()) {
    cout << ans[i] + 1 << endl;
  }
}
