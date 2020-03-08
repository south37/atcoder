// ref. https://img.atcoder.jp/hitachi2020/editorial.pdf

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

vector<vector<ll>> tree;
vector<ll> colors; // color.

void dfs(int v, int pre, int color) {
  colors[v] = color;
  for (int nv : tree[v]) {
    if (nv == pre) { continue; } // skip pre
    dfs(nv, v, !color);
  }
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  tree.resize(n);
  colors.resize(n, -1);
  ll one_cnt = (n+2)/3;
  ll two_cnt = n/3;
  if (n%3 == 2) {
    two_cnt += 1;
  }
  ll zero_cnt = n - one_cnt - two_cnt;

  rep(i, n-1) {
    ll a, b;
    cin >> a >> b;
    --a; --b; // 0-indexed
    tree[a].push_back(b);
    tree[b].push_back(a);
  }

  // paint red(0) or black(1).
  dfs(0, -1, 0);

  // Here, all nodes are painted
  ll red_cnt = 0;
  ll black_cnt = 0;
  rep(i, n) {
    if (colors[i] == 0) { // red
      ++red_cnt;
    } else {
      ++black_cnt;
    }
  }

  vector<ll> ans(n);
  if (red_cnt > n/3 && black_cnt > n/3) {
    // Here, we use 1 for red and 2 for black
    rep(i, n) {
      if (colors[i] == 0 && one_cnt > 0) {
        ans[i] = 1;
        --one_cnt;
      } else if (colors[i] == 1 && two_cnt > 0) {
        ans[i] = 2;
        --two_cnt;
      } else {
        ans[i] = 0;
      }
    }
  } else {
    ll target_color;
    if (red_cnt <= n/3) {
      // Here, we use 0 for red
      target_color = 0; // red
    } else { // black_cnt <= n/3
      // Here, we use 0 for black
      target_color = 1;
    }

    rep(i, n) {
      if (colors[i] == target_color) {
        ans[i] = 0;
        --zero_cnt;
      } else {
        if (one_cnt) {
          ans[i] = 1;
          --one_cnt;
        } else if (two_cnt) {
          ans[i] = 2;
          --two_cnt;
        } else {
          ans[i] = 0;
        }
      }
    }
  }

  ll ones = 0;
  ll twos = 0;
  ll zeros = 1;
  rep(i, n) {
    if (ans[i] == 0) {
      ans[i] = 3*zeros;
      ++zeros;
    } else if (ans[i] == 1) {
      ans[i] = 3*ones + 1;
      ++ones;
    } else { // a[i] == 2;
      ans[i] = 3*twos + 2;
      ++twos;
    }
  }

  rep(i, n) {
    cout << ans[i];
    if (i < n-1) {
      cout << " ";
    }
  }
  cout << endl;
}
