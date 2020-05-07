// ref. https://algo-logic.info/combinatorial-games/
// ref. http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=4258159#1

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

const ll N = 105;
// dp[w][b] .. grundy number at (w,b)
vector<vector<ll>> dp;

ll grundy(ll w, ll b) {
  if (dp[w][b] >= 0) { return dp[w][b]; }

  set<ll> st;
  if (w>=1) { st.insert(grundy(w-1,b)); } // (a)
  for (ll c = 1; c <= min(w,b); ++c) { // (b)
    st.insert(grundy(w,b-c));
  }
  if (b>=1) { st.insert(grundy(w+1,b-1)); }

  ll g = 0;
  while (st.find(g)!=st.end()) { ++g; }
  return dp[w][b] = g;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  dp.assign(205, vector<ll>(105, -1));
  dp[0][0] = 0;

  ll n;
  cin >> n;
  ll ans = 0;
  rep(iter,n) {
    ll w,b;
    cin >> w >> b;
    ans ^= grundy(w,b);
  }
  if (ans > 0) { // first wins
    cout << 0 << endl;
  } else {
    cout << 1 << endl;
  }
}
