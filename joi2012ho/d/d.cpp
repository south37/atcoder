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

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  int n,m;
  cin >> n >> m;
  vector<vector<int>> a(n+5, vector<int>(n+5));
  vector<vector<int>> b(n+5, vector<int>(n+5));
  while (m--) {
    int ai,bi,xi;
    cin >> ai >> bi >> xi;
    --ai; --bi; // 0-indexed
    // (ai,bi),(ai+xi,bi),(ai+xi,bi+xi)

    ++a[ai][bi];
    --a[ai+xi+1][bi+xi+1];

    --b[ai+xi+1][bi];
    ++b[ai+xi+1][bi+xi+1];
  }

  rep(i,n+5) {
    // Here, start from (i,0)
    rep(d,n+5) {
      if (i+d+1 < n+5) {
        a[i+d+1][d+1] += a[i+d][d];
      }
    }
  }

  rep(r,n+5) {
    rep(c,n+5) {
      b[r][c+1] += b[r][c];
    }
  }

  vector<vector<int>> d(n+5, vector<int>(n+5));
  rep(r,n+5)rep(c,n+5) {
    d[r][c] = a[r][c] + b[r][c];
  }

  rep(c,n+5) {
    rep(r,n+4) {
      d[r+1][c] += d[r][c];
    }
  }

  // For Debug
  // printtree(d);

  int ans = 0;
  rep(r,n)rep(c,r+1) {
    if (d[r][c] > 0) {
      ++ans;
    }
  }
  cout << ans << endl;
}
