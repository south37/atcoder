// ref. https://atcoder.jp/contests/abc033/submissions/631028

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

const double eps = 1e-10;

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  cout << setprecision(15) << fixed;

  ll n;
  cin >> n;
  vector<ll> x(n), y(n);
  rep(i,n) {
    cin >> x[i] >> y[i];
  }
  ll sum = n*(n-1)*(n-2)/6; // nC3
  ll cnt90 = 0, cntLarge = 0;
  rep(i,n) {
    vector<double> v;
    rep(j,n) {
      if (j!=i) {
        v.push_back(atan2(y[j]-y[i],x[j]-x[i]));
      }
    }
    sort(all(v));
    rep(j,n-1) { v.push_back(v[j]+2*M_PI); } // add angle+2*pi. By this, we can consider only +pi/2 and +pi.
    ll k = 0, l = 0;
    rep(j,n-1) {
      while (v[k] < v[j]+M_PI/2-eps) { ++k; }
      while (v[l] < v[j]+M_PI-eps) { ++l; }
      cntLarge += l-k;
      if (fabs(v[k]-v[j]-M_PI/2) < eps) { ++cnt90; --cntLarge; }
    }
  }
  cout << sum-cnt90-cntLarge << " " << cnt90 << " " << cntLarge << endl;
}
