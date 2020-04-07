// ref. https://img.atcoder.jp/agc016/editorial.pdf

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
#define fr first
#define sc second
#define mp make_pair
#define pb push_back

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  vector<ll> a(n);
  rep(i, n) {
    cin >> a[i];
  }

  ll minA = INF;
  ll maxA = -INF;
  rep(i, n) {
    chmin(minA, a[i]);
    chmax(maxA, a[i]);
  }

  if (maxA - minA >= 2) { // invalid
    cout << "No" << endl;
  } else if (maxA - minA == 1) {
    ll total = maxA; // total number of types
    ll x = 0; // alone
    ll y = 0; // not alone
    rep(i, n) {
      if (a[i] == minA) { // a[i] is alone
        ++x;
      } else {
        ++y;
      }
    }
    if (x < total && 2*(total-x) <= y) {
      cout << "Yes" << endl;
    } else {
      cout << "No" << endl;
    }
  } else { // maxA == minA
    if (minA == n-1) { // all a is alone
      cout << "Yes" << endl;
    } else if (2*a[0] <= n) { // all a is not alone
      cout << "Yes" << endl;
    } else {
      cout << "No" << endl;
    }
  }
}
