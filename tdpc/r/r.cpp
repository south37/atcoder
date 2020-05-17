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

// return vertices in topological sorted order.
vector<ll> tsort(const vector<vector<ll>>& g) {
  const ll n = g.size();
  vector<ll> in(n); // in-degree
  rep(i,n)rep(j,n) {
    if (g[i][j] == 1) {
      ++in[j];
    }
  }

  queue<ll> q; // start vertices
  rep(i,n) {
    if (in[i] == 0) {
      q.push(i);
    }
  }

  vector<ll> res;
  while(!q.empty()) {
    int v = q.front(); q.pop();
    res.push_back(v);
    rep(i,n) {
      if (g[v][i] == 1) { // path exist
        --in[i];
        if (in[i] == 0) { // reache to 0
          q.push(i);
        }
      }
    }
  }
  bool ok = true;
  rep(i,n) {
    ok &= (in[i] == 0);
  }
  if (!ok) { // topological sort failed. return blank vector.
    return {};
  }
  return res;
}

vector<vector<ll>> g;

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  g.assign(n,vector<ll>(n));
  rep(i,n)rep(j,n) {
    cin >> g[i][j];
  }
}
