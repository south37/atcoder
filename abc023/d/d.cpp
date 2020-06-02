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

bool ok(const vector<ll>& h, const vector<ll>& s, ll x) {
  ll n = h.size();

  vector<ll> t(n); // t[i] .. threshold to achieve x as max.
  rep(i,n) {
    t[i] = (x-h[i])/s[i];
  }
  sort(all(t));

  bool ret = true;
  rep(i,n) {
    ret &= (t[i] >= i);
  }
  return ret;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  vector<ll> h(n);
  vector<ll> s(n);
  rep(i,n) {
    cin >> h[i] >> s[i];
  }

  ll l = 0, r = INF;
  // find boundary in [f,..f,t,..,t]
  while (r-l > 1) {
    ll m = (r+l)/2;
    if (ok(h,s,m)) {
      r = m;
    } else {
      l = m;
    }
  }
  // Here, r is minimum ok
  cout << r << endl;
}
