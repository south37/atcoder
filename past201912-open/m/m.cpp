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

const ll INF = 5e5 + 5;
const ll MOD = 1000000007;  // 1e9 + 7

// Check if the sum of top 5 (b[i]-x*a[i]) is equal or lager than 0.
bool check(const vector<ll>& a, const vector<ll>& b, double x) {
  ll n = a.size();
  vector<double> v;
  rep(i,n) {
    double now = (double)b[i]-x*a[i];
    v.push_back(now);
  }
  sort(all(v));
  reverse(all(v));

  double s = 0;
  rep(i,5) {
    s += v[i];
  }
  return s >= 0;
}

double solve(const vector<ll>& a, const vector<ll>& b) {
  double l = 0, r = INF;
  // find the boundary. l is valid, r is invalid.
  rep(iter,50) {
    double m = (l+r)/2;
    if (check(a,b,m)) { // valid.
      l = m;
    } else {
      r = m;
    }
  }
  // l is valid
  return l;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  cout << setprecision(10) << fixed;

  ll n,m;
  cin >> n >> m;
  vector<ll> a(n);
  vector<ll> b(n);
  rep(i,n) {
    cin >> a[i] >> b[i];
  }

  double ans = solve(a,b);
  rep(i,m) {
    ll c,d;
    cin >> c >> d;
    a.push_back(c);
    b.push_back(d);
    chmax(ans, solve(a,b));
    a.pop_back();
    b.pop_back();
  }
  cout << ans << endl;
}
