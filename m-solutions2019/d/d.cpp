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

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

vector<ll> c;
vector<ll> d;
vector<vector<ll>> g;
int k;

void dfs(int v, int p=-1) {
  d[v] = c[k++];
  for (ll u : g[v]) {
    if (u == p) { continue; }
    dfs(u,v);
  }
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  c.resize(n);
  d.resize(n);
  g.resize(n);

  vector<ll> deg(n);
  rep(i,n-1) {
    ll a,b;
    cin >> a >> b;
    --a; --b;
    g[a].push_back(b);
    g[b].push_back(a);
    ++deg[a];
    ++deg[b];
  }

  rep(i,n) {
    cin >> c[i];
  }
  sort(all(c));
  reverse(all(c));

  int maxD = 0;
  int root = 0;
  rep(i,n) {
    if (maxD < deg[i]) {
      maxD = deg[i];
      root = i;
    }
  }

  // printvec(c);

  dfs(root);

  ll m = 0;
  for (int i = 1; i < n; ++i) {
    m += c[i];
  }
  cout << m << endl;
  rep(i,n) {
    cout << d[i];
    if (i < n-1) {
      cout << " ";
    }
  }
  cout << endl;
}
