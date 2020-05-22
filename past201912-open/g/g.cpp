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

const ll INF = 1e15;
const ll MOD = 1000000007;  // 1e9 + 7

ll n;
ll ans = -INF;
vector<vector<ll>> a;

void solve(vector<ll>& v) {
  vector<set<ll>> g(3);
  rep(i,n) {
    g[v[i]].insert(i);
  }
  ll now = 0;
  rep(i,3) {
    for (ll j : g[i]) for (ll k : g[i]) {
      if (j == k) { continue; }
      now += a[j][k];
    }
  }
  now /= 2; // (j,k) is duplicated
  if (now > ans) {
    chmax(ans,now);
  }
}

void backtrack(ll i, vector<ll>& v) {
  if (i == n) { // reached to last
    // calculate here
    solve(v);
    return;
  }
  rep(j,3) {
    v[i] = j;
    backtrack(i+1,v);
  }
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  cin >> n;
  a.assign(n,vector<ll>(n));
  rep(i,n) {
    for (ll j = i+1; j < n; ++j) {
      cin >> a[i][j];
      a[j][i] = a[i][j];
    }
  }
  // printtree(a);

  vector<ll> v(n);
  backtrack(0,v);
  cout << ans << endl;
}
