// ref. https://kmjp.hatenablog.jp/entry/2013/03/23/0930

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

const ll INF = 1e15;
const ll MOD = 1000000007;  // 1e9 + 7

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  vector<ll> nim; // nim-K
  rep(i,n) {
    ll x, y, z;
    cin >> x >> y >> z;
    ll m;
    cin >> m;
    ll minX = INF, minY = INF, minZ = INF;
    ll maxX = 0, maxY = 0, maxZ = 0;
    rep(iter,m) {
      ll xx, yy, zz;
      cin >> xx >> yy >> zz;
      chmin(minX, xx); chmin(minY, yy); chmin(minZ, zz);
      chmax(maxX, xx); chmax(maxY, yy); chmax(maxZ, zz);
    }
    if (minX > 0) { nim.push_back(minX); }
    if (minY > 0) { nim.push_back(minY); }
    if (minZ > 0) { nim.push_back(minZ); }
    if (maxX < x-1) { nim.push_back(x-1-maxX); }
    if (maxY < y-1) { nim.push_back(y-1-maxY); }
    if (maxZ < z-1) { nim.push_back(z-1-maxZ); }
  }

  ll ans = 0;
  for (ll v : nim) { ans ^= v; }
  if (ans == 0) { // lose
    cout << "LOSE" << endl;
  } else {
    cout << "WIN" << endl;
  }
}
