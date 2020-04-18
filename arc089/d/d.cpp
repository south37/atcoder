// ref. https://atcoder.jp/contests/arc089/submissions/2001908

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

ll n, K;
vector<vector<ll>> mat;

// return the sum of [x, x2), [y, y2)
ll getSum(ll x, ll y, ll x2, ll y2) {
  return mat[x2][y2] + mat[x][y] - mat[x2][y] - mat[x][y2];
}

// (x,y) .. point of left-bottom
ll solve(ll x, ll y) {
  if (x <= K) {
    // left -> right
    return getSum(0, 0, x, y) + getSum(x, y, x+K, K) + getSum(x+K, 0, 2*K, y);
  } else {
    // right -> left
    return getSum(x, y, 2*K, K) + getSum(x-K, 0, x, y) + getSum(0, y, x-K, K);
  }
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  cin >> n >> K;
  mat.assign(2*K+1, vector<ll>(K+1));
  rep(i, n) {
    ll x, y;
    char c;
    cin >> x >> y >> c;
    if (c == 'W') {
      y += K; // covert to black
    }
    x %= 2*K;
    y %= 2*K;
    if (y >= K) {
      x += K;
      y -= K;
    }
    x %= 2*K;
    // Here, y < K
    ++mat[x+1][y+1];
  }
  // mat[x+1][y+1] .. the count of black at (x, y)

  // Here, we calculate the cummulative sum
  rep(x, 2*K) rep(y, K) {
    mat[x+1][y+1] += mat[x][y+1] + mat[x+1][y] - mat[x][y];
  }
  // mat[x][y] .. the cummulative sum of [0, x), [0, y) in x<K, y<K

  ll ans = 0;
  rep(x, 2*K) rep(y, K) {
    ans = max(ans, solve(x, y));
  }
  cout << ans << endl;
}
