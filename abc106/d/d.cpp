// ref. https://img.atcoder.jp/abc106/editorial.pdf

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

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n,m,q;
  cin >> n >> m >> q;

  // cnt[l][r] .. count of trains at (l,r).
  vector<vector<ll>> cnt(n,vector<ll>(n));
  rep(i,m) {
    ll l,r;
    cin >> l >> r;
    --l;--r;
    ++cnt[l][r];
  }

  // s[r][c] .. sum of cnt in [0,r)-[0,c)
  vector<vector<ll>> s(n+1,vector<ll>(n+1));
  rep(r,n) {
    vector<ll> now(n+1);
    rep(c,n) {
      now[c+1] += now[c] + cnt[r][c];
      s[r+1][c+1] = s[r][c+1] + now[c+1];
    }
  }

  // sum of [r1,r2)-[c1,c2)
  auto calc = [&](ll r1, ll c1, ll r2, ll c2) {
    return s[r2][c2] - s[r1][c2] - s[r2][c1] + s[r1][c1];
  };

  rep(iter,q) {
    ll p,q;
    cin >> p >> q;
    --p;--q;
    cout << calc(p,p,q+1,q+1) << endl;
  }
}
