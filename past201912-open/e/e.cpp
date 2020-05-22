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
template<class T> void printset(const set<T>& v) {
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

  ll n,q;
  cin >> n >> q;
  vector<set<ll>> g(n); // follow
  rep(iter,q) {
    ll t;
    cin >> t;
    if (t == 1) {
      // follow. a->b
      ll a,b;
      cin >> a >> b;
      --a; --b;
      g[a].insert(b);
    } else if (t == 2) {
      // follow back from a.
      ll a;
      cin >> a;
      --a;
      rep(i,n) {
        if (g[i].find(a) != g[i].end()) { // i following a
          g[a].insert(i);
        }
      }
    } else { // t == 3
      ll a;
      cin >> a;
      --a;

      set<ll> t; // follow target
      for (ll v : g[a]) {
        for (ll u : g[v]) {
          if (u == a) { continue; }
          t.insert(u);
        }
      }

      for (ll v : t) {
        g[a].insert(v);
      }
    }
  }

  // rep(i,n) {
  //   printset(g[i]);
  // }
  rep(i,n) {
    rep(j,n) {
      if (g[i].find(j) != g[i].end()) {
        cout << "Y";
      } else {
        cout << "N";
      }
    }
    cout << endl;
  }
}
