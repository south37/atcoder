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

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll h,w,k;
  cin >> h >> w >> k;
  ll x1,y1,x2,y2;
  cin >> x1 >> y1 >> x2 >> y2;
  --x1; --y1; --x2; --y2;

  vector<string> mp(h);
  rep(r,h) {
    cin >> mp[r];
  }

  // printvec(mp);

  // evailable nodes of xs,ys
  vector<set<ll>> rs(h); // r => set of c
  vector<set<ll>> cs(w); // c => set or

  // leaf of xs,ys
  vector<set<ll>> lrs(h); // r => set of c with leaf
  vector<set<ll>> lcs(w); // c => set or r with leaf

  rep(r,h)rep(c,w) {
    if (mp[r][c] == '.') { // avilable
      rs[r].insert(c);
      cs[c].insert(r);
    } else {
      lrs[r].insert(c);
      lcs[c].insert(r);
    }
  }

  vector<vector<ll>> d(h,vector<ll>(w, INF));
  // Here, we do BFS.
  P s = P(x1,y1);
  d[x1][y1] = 0;
  rs[x1].erase(y1);
  cs[y1].erase(x1);
  queue<P> q;
  q.push(s);
  while(!q.empty()) {
    P p = q.front(); q.pop();
    if (p.first == x2 && p.second == y2) { // found
      cout << d[x2][y2] << endl;
      return 0;
    }

    ll r = p.first, c = p.second;
    // cout << "(r,c):" << r << "," << c << endl;
    // cout << "d(r,c):" << d[r][c] << endl;

    // Here, search from (r,c).
    {
      // First, search in left and right
      // [r-k,r+k]
      ll left = c-k, right = c+k;

      // cout << "c_left,c_right:" << left << "," << right << endl;
      auto it = lrs[r].upper_bound(c);
      // update left
      if (it != lrs[r].begin() && *prev(it) >= left) {
        chmax(left, *prev(it));
      }
      // update right
      if (it != lrs[r].end()) {
        chmin(right, *it);
      }
      // cout << "c_left2,c_right2:" << left << "," << right << endl;

      set<P> eraseTarget;
      auto it2 = rs[r].lower_bound(left);
      auto it3 = rs[r].upper_bound(right);
      for (auto nit = it2; nit != it3; ++nit) { // nit is current it
        ll nc = *nit;
        d[r][nc] = d[r][c] + 1;
        q.push(P(r,nc));

        // Erase (r,nc);
        eraseTarget.insert(P(r,nc));
      }

      for (auto p : eraseTarget) {
        rs[p.first].erase(p.second);
        cs[p.second].erase(p.first);
      }
    }

    {
      // Seond, search in top and bottom
      // [r-k,r+k]
      ll left = c-k, right = c+k;
      // cout << "r_left,r_right:" << left << "," << right << endl;
      auto it = lcs[c].upper_bound(r);
      // update left
      if (it != lcs[c].begin()) {
        chmax(left, *prev(it));
      }
      // update right
      if (it != lcs[c].end()) {
        chmin(right, *it);
      }
      // cout << "r_left2,r_right2:" << left << "," << right << endl;

      set<P> eraseTarget;
      auto it2 = cs[c].lower_bound(left);
      auto it3 = cs[c].upper_bound(right);
      for (auto nit = it2; nit != it3; ++nit) { // nit is current it
        ll nr = *nit;
        d[nr][c] = d[r][c] + 1;
        q.push(P(nr,c));

        // Erase (r,nc);
        eraseTarget.insert(P(nr,c));
      }

      for (auto p : eraseTarget) {
        rs[p.first].erase(p.second);
        cs[p.second].erase(p.first);
      }
    }
  }

  cout << -1 << endl;
}
