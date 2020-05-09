// ref. http://kurkur.hatenablog.com/entry/2018/02/08/022629

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

// g[i] .. vs connected with i.
vector<int> g[40];
bool ok1[1<<20],ok2[1<<20];
int ok3[1<<20],dp[1<<20];

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n,m;
  cin >> n >> m;
  rep(i,m) {
    int a,b;
    cin >> a >> b;
    --a; --b;
    g[a].push_back(b);
    g[b].push_back(a);
  }

  int n1=(n+1)/2, n2=n/2;
  fill(ok1, ok1+(1<<n1), true);
  rep(i,n1) {
    for (auto u : g[i]) {
      if (u < n1) {
        ok1[(1<<i)|(1<<u)] = false;
      }
    }
  }
  rep(i,1<<n1) {
    if (!ok1[i]) {
      rep(j,n1) {
        ok1[i|(1<<j)] = false;
      }
    }
  }

  fill(ok2, ok2+(1<<n2), true);
  for (int i = n1; i < n; ++i) {
    for (auto u : g[i]) {
      if (u >= n1) {
        ok2[(1<<(i-n1))|(1<<(u-n1))] = false;
      }
    }
  }
  rep(i,1<<n2) {
    if (!ok2[i]) {
      rep(j,n2) {
        ok2[i|(1<<j)] = false;
      }
    }
  }

  ok3[0] = (1<<n2)-1;
  rep(i,n1) {
    ok3[1<<i] = (1<<n2)-1;
    for (auto u : g[i]) { // loop for all u connected with i.
      if (u >= n1) {
        ok3[1<<i] ^= (1<<(u-n1));
      }
    }
  }
  rep(i,1<<n1) {
    rep(j,n1) {
      ok3[i|(1<<j)] = ok3[i]&ok3[1<<j];
    }
  }

  rep(i,1<<n2) {
    if (ok2[i]) {
      dp[i] = __builtin_popcountll(i);
    }
  }
  rep(i,1<<n2) {
    rep(j,n2) {
      chmax(dp[i|(1<<j)], dp[i]);
    }
  }

  int ans = 0;
  rep(i,1<<n1) {
    if (ok1[i]) {
      int cnt = __builtin_popcountll(i);
      chmax(ans, cnt + dp[ok3[i]]);
    }
  }
  cout << ans << endl;
}
