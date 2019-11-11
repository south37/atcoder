// base. https://atcoder.jp/contests/nikkei2019-2-qual/submissions/8368129

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
const ll MOD = 998244353;

// Mod int
// cf. https://www.youtube.com/watch?v=1Z6ofKN03_Y
struct mint {
  ll x;
  mint(ll x = 0) : x((x + MOD) % MOD) {}
  mint& operator+= (const mint a) {
    if ((x += a.x) >= MOD) x %= MOD;
    return *this;
  }
  mint operator+ (const mint a) const {
    mint res(*this);
    return res += a;
  }
  mint& operator-= (const mint a) {
    if ((x += MOD - a.x) >= MOD) x %= MOD;
    return *this;
  }
  mint operator- (const mint a) const {
    mint res(*this);
    return res -= a;
  }
  mint& operator*= (const mint a) {
    (x *= a.x) %= MOD;
    return *this;
  }
  mint operator* (const mint a) const {
    mint res(*this);
    return res *= a;
  }
  mint pow(ll t) const {
    if (!t) { return 1; }
    mint a = pow(t >> 1);
    a *= a;
    if (t & 1) a *= *this;
    return a;
  }

  // for prime mod
  mint inv() const {
    return pow(MOD-2);
  }
  mint& operator/= (const mint a) {
    return (*this) *= a.inv();
  }
  mint operator/ (const mint a) const {
    mint res(*this);
    return res /= a;
  }
};

// int main(int argc, char** argv) {
//   // int p;
//   // cin >> p;
//
//   MOD = 13;
//   mint p(10);
//   cout << (p + 15).x << endl;   // 12 (25 % 13)
//   cout << (p - 15).x << endl;   // 8  (-5 % 13)
//   cout << (p * 2).x << endl;    // 7  (20 % 13)
//   cout << (p.pow(3)).x << endl; // 12 (1000 % 13)
//   cout << (p / 3).x << endl;    // 12 (12 * 3 = 10 (36 % 13))
//
//   mint p2(-3);
//   cout << p2.x << endl; // 10 (-3 % 13)
// }

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

mint solve(vector< vector<int> >& g) {
  int n = g.size();
  if (n % 2 == 0) { // even
    // cout << "even" << endl;
    int rnk = 0;
    rep(i, n) {
      for (int j = i + 1; j < n; ++j) {
        if (g[i][j] == -1) { ++rnk; } // -1 is left when edge is '?'
      }
    }
    return mint(2).pow(rnk);
  }

  // Now, n is odd.
  // cout << "odd" << endl;

  int rnk = 0;
  vector<int> deg(n);
  UnionFind uf(n);
  rep(i, n) {
    for (int j = i + 1; j < n; ++j) {
      if (g[i][j] == -1) {
        ++rnk;
        uf.unite(i, j);
      } else {
        deg[i] ^= g[i][j]; // add and mod 2
        deg[j] ^= g[i][j]; // add and mod 2
      }
    }
  }

  vector< vector<int> > groups(n);
  rep(i, n) {
    groups[uf.root(i)].push_back(i);
  }

  for (auto g : groups) {
    int sm = 0;
    for (int v : g) {
      sm ^= deg[v]; // add and mod 2
    }
    if (g.size()) {
      rnk -= g.size() - 1; // g.size() - 1 is the length of minimum spanning tree. rnk is the diff.
    }
    if (sm) { // The degree of connected components "g" is odd.
      cout << 0 << endl;
      exit(0);
    }
  }

  return mint(2).pow(rnk);
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  int n;
  cin >> n;
  int ln = (n + 1) / 2, rn = n + 1 - ln;
  vector< vector<int> > g0(rn, vector<int>(rn, -1)); // The abs(i-j) is even. rn == ln or rn == ln+1
  vector< vector<int> > g1(ln, vector<int>(ln, -1)); // The abs(i-j) is odd.
  // Next, calculate abs(j - i) of each (i, j)
  for (int i = 1; i < n; ++i) {
    string s;
    cin >> s;
    for (int j = 1; j < n; ++j) {
      char c = s[j-1];
      if (c == '?') { continue; } // skip '?'
      int f = (c == 'o') ? 1 : 0; // o or x
      int d0 = abs(j - i); // e.g. (j = 3, i = 1) => (d0 = 2)
      int d1 = n - abs(j + i - n); // e.g. (j = 3, i = 1, n = 6) => (d1 = 4)

      // cout << "(i,j)=("<<i<<","<<j<<")"<< endl;
      // cout << "f=" << f << endl;
      // cout << "d0=" << d0 << endl;
      // cout << "d1=" << d1 << endl;

      // We treat 2 groups(even group and odd group) independently.
      if (d0 % 2 == 0) {
        d0 /= 2; d1 /= 2; // compress
        if (g0[d0][d1] == 1 - f) { // Inconsistent
          cout << 0 << endl;
          return 0;
        }
        g0[d0][d1] = g0[d1][d0] = f;
      } else {
        d0 /= 2; d1 /= 2; // compress
        if (g1[d0][d1] == 1 - f) {
          cout << 0 << endl;
          return 0;
        }
        g1[d0][d1] = g1[d1][d0] = f;
      }
    }
  }

  // cout << "g0: " << endl;
  // for (auto v : g0) {
  //   for (auto vv : v) {
  //     cout << vv << " ";
  //   }
  //   cout << endl;
  // }
  // cout << "g1: " << endl;
  // for (auto v : g1) {
  //   for (auto vv : v) {
  //     cout << vv << " ";
  //   }
  //   cout << endl;
  // }

  mint ans = solve(g0) * solve(g1);
  // cout << "solve(g0): " << solve(g0).x << endl;
  // cout << "solve(g1): " << solve(g1).x << endl;
  cout << ans.x << endl;
  return 0;
}
