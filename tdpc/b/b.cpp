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

// dp[i][j] .. first-second.
const ll N = 1005;
ll dp[N][N];

ll A, B;
vector<ll> a;
vector<ll> b;

ll rec(ll i, ll j) {
  if (i == A && j == B) { // reached to last
    return 0;
  }
  if (dp[i][j] != INF) { return dp[i][j]; }

  if ((i+j)%2 == 0) { // first. get max
    ll res = -INF;
    if (i < A) {
      chmax(res, rec(i+1,j) + a[i]);
    }
    if (j < B) {
      chmax(res, rec(i,j+1) + b[j]);
    }
    return dp[i][j] = res;
  } else { // second. get min
    ll res = INF;
    if (i < A) {
      chmin(res, rec(i+1,j) - a[i]);
    }
    if (j < B) {
      chmin(res, rec(i,j+1) - b[j]);
    }
    return dp[i][j] = res;
  }
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  rep(i,N)rep(j,N) { dp[i][j] = INF; }

  cin >> A >> B;
  ll total = 0; // x+y
  a.resize(A);
  b.resize(B);
  rep(i,A) {
    cin >> a[i];
    total += a[i];
  }
  rep(i,B) {
    cin >> b[i];
    total += b[i];
  }

  ll diff = rec(0,0); // x-y
  cout << (total+diff)/2 << endl;
}
