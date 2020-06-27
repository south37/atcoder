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

  ll n,m,k;
  cin >> n >> m >> k;
  vector<ll> a(n), b(m);
  rep(i,n) {
    cin >> a[i];
  }
  rep(i,m) {
    cin >> b[i];
  }

  vector<ll> s(n+1);
  rep(i,n) {
    s[i+1] = s[i] + a[i];
  }
  vector<ll> sb(m+1);
  rep(i,m) {
    sb[i+1] = sb[i] + b[i];
  }

  ll ans = 0;
  // Here, calculate max for each a
  rep(i,n+1) {
    ll now = i; // read i.

    ll remain = k - s[i];
    if (remain < 0) { break; } // too small
    // Here, remain >= 0

    // prev of upper_bound
    auto it = upper_bound(all(sb), remain);
    if (it == sb.begin()) { // invalid
      continue;
    } else {
      ll idx = prev(it) - sb.begin(); // idx of sb. sb[idx] <= remain
      now += idx;
      chmax(ans, now);
    }
  }

  cout << ans << endl;
}
