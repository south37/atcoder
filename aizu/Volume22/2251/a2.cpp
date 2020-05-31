// ref. https://simezi-tan.hatenadiary.org/entry/20101207/1291681751

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string.h>
#include <set>
#include <stack>

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

// const ll INF = 1e15;
const int INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

int n,m,l;
int d1[100][100];
int t[1000],pl[1000];
vector<vector<int>> g;

int p[2000];
bool used[2000];

bool rec(int v) {
  if (v < 0) { return true; }

  for (int u : g[v]) {
    if (!used[u]) {
      used[u] = true;
      if (rec(p[u])) {
        p[v] = u;
        p[u] = v;
        return true;
      }
    }
  }
  return false;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  while (true) {
    int n,m,l;
    cin >> n >> m >> l;
    if (n == 0) { break; }

    rep(i,n)rep(j,n) { d1[i][j] = INF; }
    while (m--) {
      int u,v,d;
      cin >> u >> v >> d;
      d1[u][v] = d;
      d1[v][u] = d;
    }
    // Warshall-Floyd
    rep(k,n) {
      rep(u,n)rep(v,n) {
        chmin(d1[u][v], d1[u][k] + d1[k][v]);
      }
    }
    // printtree(d1);

    rep(i,l) {
      cin >> pl[i] >> t[i];
    }

    // Calculate maximum matching.
    g.clear(); g.resize(2*l);
    rep(i,l)rep(j,l) {
      if (i==j) { continue; }
      if (t[i]+d1[pl[i]][pl[j]] <= t[j]) { // i->j is ok.
        g[i].push_back(l+j);
        g[l+j].push_back(i);
      }
    }

    int ans = l;
    rep(i,2*l)p[i]=-1;
    rep(i,l) {
      rep(i,2*l) { used[i] = false; } // reset
      if (rec(i)) {
        --ans;
      }
    }
    cout << ans << endl;
  }
}
