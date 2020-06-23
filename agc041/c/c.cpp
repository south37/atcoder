// ref. https://atcoder.jp/contests/agc041/submissions/9180689

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
typedef vector<string> vs;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

vs s3 = {
  "aab",
  "c.b",
  "cdd"};
vs s4 = {
  "aacd",
  "bbcd",
  "efgg",
  "efhh"};
vs s5 = {
  "abc..",
  "abc..",
  "gghdd",
  "i.hee",
  "ijjff"};
vs s7 = {
  "abc....",
  "abc....",
  "...deff",
  "...degg",
  "kkl..hh",
  "m.lii..",
  "mnnjj.."};

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  if (n <= 2) {
    cout << -1 << endl;
    return 0;
  }
  vs ans(n,string(n,'.'));
  int ni = 0;
  auto add = [&](vs& s) {
    int m = sz(s);
    rep(i,m)rep(j,m) {
      ans[ni+i][ni+j] = s[i][j];
    }
    ni += m;
  };
  if (n%3 == 0) {
    while (ni<n) { add(s3); }
  } else if (n == 7) {
    add(s7);
  } else if (n == 11) {
    add(s7);
    add(s4);
  } else {
    int n5 = 0;
    while ((n-n5*5)%4) { ++n5; }
    rep(iter,n5) { add(s5); }
    while (ni<n) { add(s4); }
  }
  rep(i,n) {
    cout << ans[i] << endl;
  }
}
