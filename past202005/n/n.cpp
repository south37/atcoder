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

  ll n,q;
  cin >> n >> q;
  vector<ll> a(n);
  rep(i,n) {
    a[i] = i+1;
  }

  set<ll> st; // swapped indices. i where a[i] > a[i+1].
  auto swapX = [&](ll x) {
    swap(a[x],a[x+1]);
    // Here, x-1,x,x+1 may be target
    vector<ll> tgt = { x-1, x, x+1 };
    for (ll v : tgt) {
      if (v < 0 || v >= n) { continue; } // invalid
      if (a[v] > a[v+1]) {
        st.insert(v);
      } else {
        st.erase(v);
      }
    }
  };

  while (q--) {
    ll t,x,y;
    cin >> t >> x >> y;
    --x; --y;
    if (t == 1) {
      swapX(x); // swap x<=>x+1
    } else { // t == 2
      while (true) {
        // Here, search target in [x,y)
        auto it = st.lower_bound(x);
        if (it == st.end()) { break; } // not found
        ll v = *it;
        if (v >= y) { break; } // v is too large
        swapX(v);
      }
    }
  }

  rep(i,n) {
    cout << a[i];
    if (i < n-1) {
      cout << " ";
    }
  }
  cout << endl;
}
