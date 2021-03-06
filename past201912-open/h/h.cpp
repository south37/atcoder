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

const ll INF = 1e12;
const ll MOD = 1000000007;  // 1e9 + 7

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  vector<ll> c(n);
  ll minV = INF; // minimum value in all
  ll minOdd = INF; // minimum value in odd
  rep(i,n) {
    cin >> c[i];
    chmin(minV, c[i]);
    if (i%2 == 0) { // odd
      chmin(minOdd, c[i]);
    }
  }
  ll total = 0;
  rep(i,n) { total += c[i]; }

  ll offsetAll = 0; // contribution from 2
  ll offsetOdd = 0; // contribution from 3

  ll q;
  cin >> q;
  rep(iter,q) {
    ll t;
    cin >> t;
    if (t == 1) {
      ll x,a;
      cin >> x >> a;
      --x;
      ll offset = offsetAll;
      if (x%2 == 0) { // odd
        offset += offsetOdd;
      }

      if (c[x]-offset >= a) {
        c[x] -= a;
        chmin(minV, c[x]-offset);
        if (x%2 == 0) { // odd
          chmin(minOdd, c[x]-offset);
        }
      }
    } else if (t == 2) {
      ll a;
      cin >> a;
      if (minOdd >= a) {
        offsetOdd += a;
        minOdd -= a;
        chmin(minV, minOdd);
      }
    } else { // t == 3
      ll a;
      cin >> a;
      if (minV >= a) {
        offsetAll += a;
        minV -= a;
        minOdd -= a;
      }
    }
  }

  ll remain = 0; // decrease count
  rep(i,n) {
    ll offset = offsetAll;
    if (i%2 == 0) { // odd
      offset += offsetOdd;
    }
    assert(c[i]-offset >= 0);
    remain += c[i]-offset;
  }
  cout << total-remain << endl;
}
