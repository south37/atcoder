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

  ll n, q;
  cin >> n >> q;
  vector<ll> c(n);
  rep(i,n) {
    cin >> c[i];
  }
  vector<triple> qs; // (l,r,idx)
  rep(i,q) {
    ll l,r;
    cin >> l >> r;
    --l; --r;
    qs.emplace_back(l,r,i);
  }
  sort(all(qs));
  vector<vector<ll>> lmarks(n);
  vector<vector<ll>> rmarks(n);
  for (auto& q : qs) {
    ll l,r,idx;
    tie(l,r,idx) = q;
    lmarks[l].push_back(idx);
    rmarks[r].push_back(idx);
  }

  vector<set<ll>> cs(q); // cs[i] .. colors in query i.

  set<ll> now; // current queries
  rep(i,n) {
    for (ll idx : lmarks[i]) {
      now.insert(idx);
    }

    // Here, now is valid. Update cs.
    for (ll idx : now) {
      cs[idx].insert(c[i]);
    }

    for (ll idx : rmarks[i]) {
      now.erase(idx);
    }
  }

  rep(i,q) {
    cout << cs[i].size() << endl;
  }
}
