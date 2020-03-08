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
vector<vector<ll>> threeTree;
vector<ll> deg;
ll zero_cnt = 0;
ll one_cnt = 0;
ll two_cnt = 0;
vector<ll> colors; // color at i. used as visited. initialized by -1.
vector<ll> states;

void threeDfs(int v, int nv, int step) {
  if (states[nv] == 1) { return; } // cycle
  states[nv] = 1;

  if (step == 3) {
    threeTree[v].push_back(nv);
    states[nv] = 0;
    return;
  }

  for (int nnv : tree[nv]) {
    threeDfs(v, nnv, step + 1);
  }
  states[nv] = 0;
}

// color = 1 or 2
void dfs(int v, int color, int pre) {
  if (colors[v] != -1) { return; } // skip already visited one.

  // At step 3, we paint.
  if (color == 1) {
    if (one_cnt == 0) { return; } // already 0
  } else {
    if (two_cnt == 0) { return; }
  }

  colors[v] = color;

  if (color == 1) {
    --one_cnt;
    color = 2;
    if (two_cnt == 0) { // two is already 0
      return;
    }
  } else { // color == 2;
    --two_cnt;
    color = 1;
    if (one_cnt == 0) { // two is already 0
      return;
    }
  }

  for (int nv : threeTree[v]) {
    if (nv == pre) { continue; } // skp parent
    dfs(nv, color, v);
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
  deg.resize(n);
  colors.assign(n, -1);
  states.assign(n, -1);

  threeTree.resize(n);

  one_cnt = (n+2)/3;
  two_cnt = n/3;
  if (n%3 == 2) {
    two_cnt += 1;
  }
  zero_cnt = n - one_cnt - two_cnt;

  // cout << "zero_cnt: " << zero_cnt << endl;
  // cout << "one_cnt: " << one_cnt << endl;
  // cout << "two_cnt: " << two_cnt << endl;

  rep(i, n-1) {
    ll a, b;
    cin >> a >> b;
    --a; --b; // 0-indexed
    tree[a].push_back(b);
    tree[b].push_back(a);
    ++deg[a];
    ++deg[b];
  }

  // We want tree with distance 3.
  rep(i, n) {
    threeDfs(i, i, 0);
  }
  vector<ll> threeDeg(n);
  vector<ll> threeLeaves;
  rep(i, n) {
    if (threeTree[i].size() == 1) {
      threeLeaves.push_back(i);
    }
  }

  //for (int v : threeLeaves) {
  rep(v, n) {
    ll color;
    if (one_cnt > two_cnt) {
      color = 1;
    } else {
      color = 2;
    }

    dfs(v, color, -1);
  }
  rep(i, n) {
    if (colors[i] == -1) {
      colors[i] = 0;
    }
  }

  // vector<ll> leaves;
  // rep(i, n) {
  //   if (deg[i] == 1) {
  //     leaves.push_back(i);
  //   }
  // }

  // for (int v : leaves) {
  //   ll color;
  //   if (one_cnt > two_cnt) {
  //     color = 1;
  //   } else {
  //     color = 2;
  //   }

  //   dfs(v, 0, color);
  // }
  // rep(i, n) {
  //   if (colors[i] == -1) {
  //     colors[i] = 0;
  //   }
  // }

  // Here, 1 and 2 are painted.
  vector<ll> ans(n);
  ll zeros = 1;
  ll ones = 0;
  ll twos = 0;
  rep(i, n) {
    if (colors[i] == 0) {
      ans[i] = zeros * 3;
      ++zeros;
    } else if (colors[i] == 1) {
      ans[i] = ones * 3 + 1;
      ++ones;
    } else { // 2
      ans[i] = twos * 3 + 2;
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
