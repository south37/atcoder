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

vector<ll> dp;
vector<ll> p;

ll dfs(ll v) {
  if (dp[v] >= 0) { return dp[v]; }
  dp[v] = dfs(p[v]);
  return dp[v];
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n,q;
  cin >> n >> q;
  p.assign(2*n,-1);
  // [0,n) .. table, [n,2*n] .. container
  rep(i,n) {
    p[i+n] = i;
  }

  vector<ll> top(n); // top of each table
  rep(i,n) {
    top[i] = i+n;
  }

  // printvec(p);
  // printvec(top);

  rep(iter,q) {
    ll from,to,x;
    cin >> from >> to >> x;
    --from;--to;--x;
    x += n; // offset
    // move container x from f to t.
    ll prevTop = top[from];

    ll newTop = p[x]; // newTop in from.
    top[from] = newTop;

    // set.
    p[x] = top[to];
    top[to] = prevTop;
  }

  // printvec(p);

  // Here, p has all information
  dp.assign(2*n,-1);
  rep(i,n) { dp[i] = i; } // table
  rep(i,n) {
    dfs(i+n);
  }

  rep(i,n) {
    cout << dp[i+n]+1 << endl;
  }
}
