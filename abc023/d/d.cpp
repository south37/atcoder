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

const ll INF = 1e17;
const ll MOD = 1000000007;  // 1e9 + 7

ll n;
vector<ll> h, s;

bool f(ll x) {
  vector<ll> t;
  rep(i,n) {
    if (h[i] > x) return false;
    t.pb((x-h[i])/s[i]);
  }
  sort(all(t));
  rep(i,sz(t)) if (t[i] < i) return false;
  return true;
}

int main() {
  cin >> n;
  h.resize(n);
  s.resize(n);
  rep(i,n) {
    cin >> h[i] >> s[i];
  }

  ll l = *max_element(all(h)), r = INF;
  while (r-l > 0) {
    ll m = (l+r) / 2;
    if (f(m)) {
      r = m;
    } else {
      l = m+1;
    }
  }
  cout << r << endl;
}
