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

// BIT (Fenwick Tree) with 0-indexed query
// https://youtu.be/lyHk98daDJo?t=7960
template<typename T>
struct BIT {
  int n;
  vector<T> d;
  BIT(int n=0) : n(n), d(n+1) {}
  void add(int i, T x=1) {
    i++; // 0-indexed to 1-indexed
    for (; i <= n; i += i&-i) {
      d[i] += x;
    }
  }
  // The sum of [0, i]
  T sum(int i) {
    i++; // 0-indexed to 1-indexed
    T x = 0;
    for (; i; i -= i&-i) {
      x += d[i];
    }
    return x;
  }
  // The sum of [l, r)
  T sum(int l, int r) {
    return sum(r-1) - sum(l-1);
  }
};

// int main(int argc, char** argv) {
//   int N;
//   cin >> N;
//   vector<int> v(N);
//   rep(i, N) {
//     cin >> v[i];
//   }
//
//   BIT<int> bit(N);
//   rep(i, N) {
//     bit.add(i, v[i]);
//   }
//
//   cout << bit.sum(4) << endl; // 24
//   cout << bit.sum(9) << endl; // 55
// }

vector<vector<ll>> g;
vector<ll> in;
vector<ll> out;
ll k;

void dfs(ll v, ll p = -1) {
  in[v] = k++;
  for (ll u : g[v]) {
    if (u == p) { continue; }
    dfs(u, v);
  }
  out[v] = k;
}

ll c2(ll n) { return n*(n+1)/2; } // nC2 + n = n*(n+1)/2

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  vector<ll> c(n);
  g.resize(n);
  in.resize(n);
  out.resize(n);

  rep(i, n) {
    cin >> c[i];
  }
  rep(i, n-1) {
    ll a, b;
    cin >> a >> b;
    --a; --b;
    g[a].push_back(b);
    g[b].push_back(a);
  }
  // printvec(c);
  // printtree(g);

  // Assign in and out
  dfs(0);
  vector<vector<ll>> vs(n); // vs[i] .. vertices at color i.
  rep(i, n) {
    vs[c[i]-1].push_back(i);
  }
  // printvec(in);
  // printvec(out);
  // printtree(vs);

  // Start calculation
  ll tot = c2(n);
  BIT<ll> d(n);
  rep(i, n) { d.add(i, 1); }
  rep(i, n) {
    ll ans = tot;
    vector<ll>& nvs = vs[i];
    sort(all(nvs), [&](ll a, ll b) {
      return in[a] > in[b];
    });
    vector<P> history; // used for reverting state
    for (ll v : nvs) {
      ll cnt = 1;
      for (ll u : g[v]) {
        if (in[u] < in[v]) { continue; } // skip ancestors. They are small.
        ll num = d.sum(in[u], out[u]);
        ans -= c2(num);
        cnt += num;
      }
      d.add(in[v], -cnt);
      history.emplace_back(in[v], cnt);
    }
    ans -= c2(d.sum(0, n));
    for (auto& p : history) { // revert state
      d.add(p.first, p.second);
    }
    cout << ans << endl;
  }
}
