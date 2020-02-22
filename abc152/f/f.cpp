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
  int to;
  int id;
  Edge(int to, int id) : to(to), id(id) {}
};

vector<vector<Edge>> g(55);

vector<int> es;
bool dfs(int v, int tv, int p=-1) {
  if (v == tv) {
    es.clear();
    return true;
  }
  for (Edge e : g[v]) {
    if (e.to == p) { continue; } // skip parent
    if (dfs(e.to, tv, v)) {
      es.push_back(e.id);
      return true;
    }
  }
  return false;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n, m;
  cin >> n;
  rep(i, n-1) {
    int a, b;
    cin >> a >> b;
    --a; --b; // 0-indexed
    g[a].emplace_back(b, i);
    g[b].emplace_back(a, i);
  }

  cin >> m;
  vector<ll> eset(m); // The edge set for each condition
  rep(i, m) {
    int a, b;
    cin >> a >> b;
    --a; --b; // 0-indexed
    dfs(a, b);
    for (int e : es) {
      eset[i] |= 1ll << e;
    }
  }

  ll ans = 0;
  rep(i, 1<<m) {
    ll mask = 0; // represents the white edges.
    rep(j, m) {
      if (i>>j & 1) {
        mask |= eset[j];
      }
    }
    int white = __builtin_popcountll(mask);
    ll now = 1ll << (n-1-white);
    // Calculate the count by Exclusion principle.
    if (__builtin_popcountll(i) % 2 == 0) { // even. plus.
      ans += now;
    } else { // odd. minus.
      ans -= now;
    }
  }
  cout << ans << endl;
}
