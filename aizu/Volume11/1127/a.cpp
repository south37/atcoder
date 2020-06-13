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

class UnionFind {
public:
  UnionFind(ll n) : par(n, -1), rnk(n, 0), cnt(n, 1), _size(n) {}

  bool same(ll x, ll y) {
    return root(x) == root(y);
  }
  void unite(ll x, ll y) {
    x = root(x); y = root(y);
    if (x == y) return;

    --_size;

    if (rnk[x] < rnk[y]) { swap(x, y); }
    par[y] = x;
    cnt[x] += cnt[y];
    if (rnk[x] == rnk[y]) { ++rnk[x]; }
  }
  ll root(ll x) {
    if (par[x] < 0) {
      return x;
    } else {
      return par[x] = root(par[x]);
    }
  }
  ll count(ll x) {
    return cnt[root(x)];
  }
  ll size() {
    return _size;
  }

private:
  vector<ll> par;
  vector<ll> rnk;
  vector<ll> cnt; // The number of vertices in each connected components.
  ll _size; // The number of connected components. Decreases by unite.
};

// int main(int argc, char** argv) {
//   ll N, M;
//   cin >> N >> M;
//   UnionFind tree(N);
//   rep(i, M) {
//     ll p, a, b;
//     cin >> p >> a >> b;
//     if (p == 0) { // Connect
//       tree.unite(a, b);
//     } else { // Judge
//       if (tree.same(a, b)) {
//         cout << "Yes" << endl;
//         cout << "size: " << tree.size() << endl;
//         cout << "count(" << a << "): " << tree.count(a) << endl;
//         cout << "count(" << b << "): " << tree.count(b) << endl;
//       } else {
//         cout << "No" << endl;
//         cout << "size: " << tree.size() << endl;
//         cout << "count(" << a << "): " << tree.count(a) << endl;
//         cout << "count(" << b << "): " << tree.count(b) << endl;
//       }
//     }
//   }
// }

const double eps = 1e-10;

void solve(ll n) {
  vector<double> x(n),y(n),z(n),r(n);
  rep(i,n) {
    cin >> x[i] >> y[i] >> z[i] >> r[i];
  }
  vector<vector<double>> d(n,vector<double>(n, INF));
  rep(i,n)rep(j,n) {
    double dist = 0;
    dist += (x[i]-x[j])*(x[i]-x[j]);
    dist += (y[i]-y[j])*(y[i]-y[j]);
    dist += (z[i]-z[j])*(z[i]-z[j]);
    dist = sqrt(dist);
    dist -= r[i]+r[j];
    d[i][j] = dist;
  }

  UnionFind uf(n);
  rep(i,n)rep(j,i) {
    if (d[i][j] < eps) { // minus
      uf.unite(i,j);
    }
  }

  // d2 .. distance between connected components
  vector<vector<double>> d2(n,vector<double>(n, INF));
  vector<ll> roots;
  rep(i,n) {
    ll r = uf.root(i);
    d2[r][r] = 0; // same
    roots.push_back(r);
  }
  sort(all(roots));
  roots.erase(unique(all(roots)), roots.end());

  rep(i,n)rep(j,i) {
    ll r1 = uf.root(i);
    ll r2 = uf.root(j);
    if (r1 == r2) { continue; } // already connected
    chmin(d2[r1][r2], d[i][j]);
    chmin(d2[r2][r1], d[i][j]);
  }

  // Here, calculate the minimum spanning tree
  vector<tuple<double,ll,ll>> edges;
  rep(i,roots.size())rep(j,i) {
    ll r1 = roots[i];
    ll r2 = roots[j];
    edges.emplace_back(d2[r1][r2],i,j);
  }

  double ans = 0;
  UnionFind uf2(roots.size());
  sort(all(edges));
  for (auto& edge : edges) {
    double cost;
    ll i,j;
    tie(cost,i,j) = edge;
    if (!uf2.same(i,j)) {
      ans += cost;
      uf2.unite(i,j);
    }
  }

  cout << ans << endl;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  cout << setprecision(3) << fixed;

  while (true) {
    ll n;
    cin >> n;
    if (n == 0) { break; }
    solve(n);
  }
}
