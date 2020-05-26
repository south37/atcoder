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

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n,m;
  cin >> n >> m;
  vector<ll> p(m);
  rep(i,m) {
    cin >> p[i];
    --p[i];
  }
  vector<ll> a(n-1);
  vector<ll> b(n-1);
  vector<ll> c(n-1);
  rep(i,n-1) {
    cin >> a[i] >> b[i] >> c[i];
  }

  // First, calculate the count of each path.
  vector<ll> s(n+1);
  rep(i,m-1) {
    ll l = p[i];
    ll r = p[i+1];
    if (l>r) { swap(l,r); }
    // Here, l <= r. add 1 to [l,r)
    ++s[l];
    --s[r];
  }
  rep(i,n) {
    s[i+1] += s[i];
  }
  // Here, s[i] indicates the usage between (i,i+1)

  // printvec(a);
  // printvec(b);
  // printvec(c);
  // printvec(s);

  vector<bool> use(n-1); // use[i] .. use b at i.
  vector<ll> costs(n-1); // costs[i] .. cost between (i,i+1)
  rep(i,n-1) {
    if ((c[i] + s[i]*b[i]) < s[i]*a[i]) {
      costs[i] = b[i];
      use[i] = true;
    } else {
      costs[i] = a[i];
    }
  }

  // printvec(use);
  // printvec(costs);

  // costSum[i] .. sum of costs in [0,i)
  vector<ll> costSum(n);
  rep(i,n-1) {
    costSum[i+1] = costSum[i] + costs[i];
  }

  ll ans = 0;
  rep(i,n) {
    if (use[i]) {
      ans += c[i];
    }
  }
  // cout << ans << endl;
  rep(i,m-1) {
    ll pre = p[i];
    ll now = p[i+1];
    ans += abs(costSum[now]-costSum[pre]);
  }
  cout << ans << endl;
}
