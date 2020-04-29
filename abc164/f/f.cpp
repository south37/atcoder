// ref. https://www.youtube.com/watch?v=7n5ERSA5MaU

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

ll n;
vector<vector<int>> s(2);
vector<vector<ull>> u(2);
vector<vector<int>> d;
vector<vector<int>> val(2);

void flip() {
  rep(i,n)rep(j,i) {
    swap(d[i][j], d[j][i]);
  }
}

bool solve() {
  rep(i,n)rep(j,n) { d[i][j] = -1; }
  // First, set determinable values.
  rep(k,2) {
    rep(i,n) {
      int x = val[k][i];
      if (s[k][i] != x) { // e.g. s[k][i]=0(and), x=1, s[k][i]=1(or), x=0. Value is fixed.
        rep(j,n) {
          if (d[i][j] == !x) { return false; } // invalid
          d[i][j] = x;
        }
      }
    }
    flip(); // flip row<=>col
  }
  // Next, set rows with only one undetermined value.
  rep(_,2) {
    rep(k,2) {
      rep(i,n) {
        int x = val[k][i];
        if (s[k][i] == x) { // e.g. s[k][i]=0(and), x=0, s[k][i]=1(or), x=1. Value is undetermined.
          vector<int> p;
          bool ok = false;
          rep(j,n) {
            if (d[i][j] == -1) { p.push_back(j); } // add undetermined value
            if (d[i][j] == x) { ok = true; }
          }
          if (ok) { continue; } // already satisfied
          if (p.size() == 0) { return false; } // invalid
          if (p.size() == 1) {
            d[i][p[0]] = x;
          }
        }
      }
      flip();
    }
  }

  vector<int> is, js;
  rep(i,n) {
    bool filled = true;
    rep(j,n) {
      if (d[i][j] == -1) { filled = false; break; }
    }
    if (!filled) { is.push_back(i); }
  }
  rep(j,n) {
    bool filled = true;
    rep(i,n) {
      if (d[i][j] == -1) { filled = false; break; }
    }
    if (!filled) { js.push_back(j); }
  }
  rep(i,is.size())rep(j,js.size()) {
    d[is[i]][js[j]] = (i+j)%2;
  }
  return true;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  cin >> n;
  rep(i,2) {
    s[i] = vector<int>(n);
    rep(j,n) { cin >> s[i][j]; }
  }
  rep(i,2) {
    u[i] = vector<ull>(n);
    rep(j,n) { cin >> u[i][j]; }
  }

  vector<vector<ull>> ans(n, vector<ull>(n));
  rep(i,2) { val[i].resize(n); }
  d.assign(n, vector<int>(n));

  rep(b,64) {
    rep(i,2)rep(j,n) { val[i][j] = (u[i][j]>>b)&1; }
    if (!solve()) {
      cout << -1 << endl;
      return 0;
    }
    rep(i,n)rep(j,n) { ans[i][j] |= ull(d[i][j])<<b; }
  }
  rep(i,n) {
    rep(j,n) {
      cout << ans[i][j];
      if (j < n-1) {
        cout << ' ';
      }
    }
    cout << endl;
  }
}
