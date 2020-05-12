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

vector<ll> build_z(const vector<ll>& s) {
  ll n = s.size();
  vector<ll> z(n, 0);
  ll l = -1, r = -1;
  for (ll i = 1; i < n; ++i) {
    if (i <= r) {
      z[i] = min<ll>(r - i + 1, z[i - l]);
    }
    while (i + z[i] < n && s[i + z[i]] == s[z[i]]) {
      ++z[i];
    }
    if (i + z[i] - 1 > r) {
      r = i + z[i] - 1;
      l = i;
    }
  }
  return z;
}


vector<ll> f(const vector<ll>& x) {
  ll n = x.size();
  vector<ll> res(n);
  rep(i,n) {
    res[i] = x[i]^x[(i+1)%n];
  }
  return res;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  vector<ll> a(n);
  vector<ll> b(n);
  rep(i,n) {
    cin >> a[i];
  }
  rep(i,n) {
    cin >> b[i];
  }
  vector<ll> xa = f(a);
  vector<ll> xb = f(b);

  vector<ll> t = xb;
  t.push_back(-1);
  t.insert(t.end(), all(xa));
  t.insert(t.end(), all(xa));
  // printvec(t);

  vector<ll> z = build_z(t);
  rep(k,n) {
    if (z[n+1+k] == n) { // ok
      ll x = a[k]^b[0];
      cout << k << " " << x << endl;
    }
  }
}
