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

vector<vector<ll>> g;
vector<bool> visited;
ll v1;
ll v2;
deque<ll> p; // path. [v1, ..., v2]

// type: 0 .. front, 1 .. back
void dfs(ll v, ll type) {
  if (type == 0) {
    p.push_front(v);
  } else { // type == 1
    p.push_back(v);
  }

  for (int u : g[v]) {
    if (visited[u]) { continue; }
    // Here, path exist
    visited[u] = true;
    dfs(u, type);
    break; // Here, we need only one edge
  }
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n, m;
  cin >> n >> m;
  g.resize(n);
  visited.resize(n);

  rep(i, m) {
    ll a, b;
    cin >> a >> b;
    --a; --b; //0-indexed
    g[a].push_back(b);
    g[b].push_back(a);
  }

  // Here, we start path from 0.
  v1 = 0;
  visited[0] = true;
  v2 = g[0][0];
  visited[v2] = true;
  dfs(v1, 0);
  dfs(v2, 1);

  cout << p.size() << endl;
  rep(i, p.size()) {
    cout << p[i] + 1;
    if (i < p.size()-1) {
      cout << " ";
    }
  }
  cout << endl;
}
