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

  ll n, K;
  cin >> n >> K;
  vector<vector<vector<ll>>> mats(2, vector<vector<ll>>(K, vector<ll>(K)));
  auto& black = mats[0]; // counts only black.
  auto& white = mats[1]; // counts only white.
  rep(i, n) {
    ll x, y;
    char c;
    cin >> x >> y >> c;
    int color = (c == 'B') ? 1 : 0; // 1 .. black, 0 .. white
    x %= 2*K;
    y %= 2*K;
    if (x >= K) {
      x -= K;
      color ^= 1;
    }
    if (y >= K) {
      y -= K;
      color ^= 1;
    }

    if (color == 1) { // black
      ++black[x][y];
    } else { // white
      ++white[x][y];
    }
  }
  // printtree(black);
  // printtree(white);

  vector<ll> sums(2);
  vector<vector<vector<ll>>> lefts(2, vector<vector<ll>>(K, vector<ll>(K))); // sum of bottom-left
  vector<vector<vector<ll>>> rights(2, vector<vector<ll>>(K, vector<ll>(K))); // sum of top-right
  rep(k, 2) {
    auto& mat = mats[k];

    auto& sum = sums[k];
    rep(x, K) rep(y, K) {
      sum += mat[x][y];
    }

    auto& left = lefts[k];
    auto& right = rights[k];

    rep(x, K) rep(y, K) {
      if (x == 0 && y == 0) {
        left[x][y] = mat[x][y];
      } else if (x == 0) {
        left[x][y] = left[x][y-1] + mat[x][y];
      } else if (y == 0) {
        left[x][y] = left[x-1][y] + mat[x][y];
      } else { // x > 0 && y > 0
        left[x][y] = left[x][y-1] + left[x-1][y] - left[x-1][y-1] + mat[x][y];
      }
    }

    for (int x = K-1; x >= 0; --x) for (int y = K-1; y >= 0; --y) {
      if (x == K-1 && y == K-1) {
        right[x][y] = mat[x][y];
      } else if (x == K-1) {
        right[x][y] = right[x][y+1] + mat[x][y];
      } else if (y == K-1) {
        right[x][y] = right[x+1][y] + mat[x][y];
      } else { // x < K-1 && y < K-1
        right[x][y] = right[x][y+1] + right[x+1][y] - right[x+1][y+1] + mat[x][y];
      }
    }
  }
  // printtree(lefts[0]);
  // printtree(rights[0]);
  // printtree(lefts[1]);
  // printtree(rights[1]);

  // k=0 .. black, k=1 .. white
  ll white_sum = sums[1];
  auto& white_left = lefts[1];
  auto& white_right = rights[1];
  auto& black_left = lefts[0];
  auto& black_right = rights[0];

  ll ans = max(sums[0], sums[1]);
  // check all case of boundary
  rep(x, K+1) rep(y, K+1) {
    ll now = white_sum;
    if (x > 0 && y > 0) {
      now -= white_left[x-1][y-1];
      now += black_left[x-1][y-1];
    }
    if (x < K && y < K) {
      now -= white_right[x][y];
      now += black_right[x][y];
    }
    ans = max(ans, now);
  }
  cout << ans << endl;
}
