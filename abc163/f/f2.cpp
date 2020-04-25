// ref. https://www.youtube.com/watch?v=HVuSp_IhNZA

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

vector<ll> c;
vector<vector<ll>> g;

vector<ll> t; // t[i] .. size of subtree with root i
vector<stack<ll>> st;
vector<ll> d; // d[i] .. temporary store.
vector<ll> remsz; // remsz[i] .. remaining size of color i
vector<ll> ans; // ans[i] .. result of color i

ll f(ll n) { return n*(n+1)/2; } // nC2 + n = n*(n+1)/2

ll tfs(ll v, ll p = -1) {
  t[v] = 1;
  for (int u : g[v]) {
    if (u == p) { continue; }
    t[v] += tfs(u, v);
  }
  return t[v];
}

void dfs(ll v, ll p = -1) {
  st[c[v]].push(v);
  for (ll u : g[v]) {
    if (u == p) { continue; }
    d[v] = t[u]; // store here temporarily
    dfs(u, v);
    ans[c[v]] -= f(d[v]);
  }
  st[c[v]].pop();
  if (st[c[v]].size() > 0) {
    d[st[c[v]].top()] -= t[v]; // decrease the contribution of this subtree
  } else {
    remsz[c[v]] -= t[v];
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
  g.resize(n);
  t.resize(n);
  st.resize(n);
  d.resize(n);
  remsz.resize(n);
  ans.resize(n);

  rep(i, n) {
    cin >> c[i];
    --c[i];
  }
  rep(i, n-1) {
    ll a, b;
    cin >> a >> b;
    --a; --b;
    g[a].push_back(b);
    g[b].push_back(a);
  }

  rep(i, n) { ans[i] = f(n); }
  rep(i, n) { remsz[i] = n; }
  tfs(0);
  dfs(0);
  rep(i, n) {
    ans[i] -= f(remsz[i]);
  }
  rep(i, n) {
    cout << ans[i] << endl;
  }
}
