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

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

vector<vector<char>> ans(8,vector<char>(8,'.'));
vector<bool> rs(8);
vector<bool> cs(8);
vector<bool> ds(15); // diagnal. r-c+7
vector<bool> rds(15); // reverse. r+c

bool backtrack(ll r) {
  if (r == 8) { return true; } // reached to last

  if (rs[r]) { return backtrack(r+1); } // already fixed. skip.
  rep(c,8) {
    if (cs[c]) { continue; }
    if (ds[r-c+7]) { continue; }
    if (rds[r+c]) { continue; }

    // Here, (r,c) is valid
    rs[r] = true;
    cs[c] = true;
    ds[r-c+7] = true;
    rds[r+c] = true;
    ans[r][c] = 'Q';
    if (backtrack(r+1)) {
      return true;
    }
    // Here, revert state
    rs[r] = false;
    cs[c] = false;
    ds[r-c+7] = false;
    rds[r+c] = false;
    ans[r][c] = '.';
  }
  return false;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll k;
  cin >> k;
  rep(iter,k) {
    ll r,c;
    cin >> r >> c;
    rs[r] = true;
    cs[c] = true;
    ds[r-c+7] = true;
    rds[r+c] = true;
    ans[r][c] = 'Q';
  }
  backtrack(0);

  rep(r,8) {
    rep(c,8) {
      cout << ans[r][c];
    }
    cout << endl;
  }
}
