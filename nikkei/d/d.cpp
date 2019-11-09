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

  ll n, m;
  cin >> n >> m;
  vector< vector<ll> > graph(m);
  vector<ll> s; // starts
  vector<ll> t; // goals

  vector<triple> ops;
  rep(i, m) {
    ll l, r, c;
    cin >> l >> r >> c;
    ops.emplace_back(l, c, r);
  }
  sort(all(ops));

  // Now, we check from s.
  // we manage only "right sighd".
  // [id, c] => the minimum cost under c.

  set<P> rs; // The set of [id, c]
  rep(i, m) {
    ll l, r, c;
    tie(l, c, r) = ops[i];
    if (i == 0 && l != 1) { // first c must contain start = 1.
      cout << -1 << endl;
      return 0;
    }

    // first we consider first case

    if (l == 1) { // l is start
      auto it = rs.upper_bound(mp(r, -1LL)); // Use dummy cost -1 to search all r
      if (it == rs.end()) { // *it > the last of rs
        rs.emplace(r, c);
      } else {
        if (r == (*it).fr) { // same with *it
          rs.erase(it);
          rs.emplace(r, c);
        } else {
          rs.emplace(r, c);
        }
      }
      continue;
    }

    // TODO(south37) consider other case
    auto it = rs.lower_bound(mp(l, -1)); // We search the next r of l.
    if (it == rs.end()) { // no r found
      // Invalid!
      cout << -1 << endl;
      return 0;
    } else {
      // r is found. we erase it if necessary.
      ll new_c = (*it).sc + c;

      auto rit = rs.upper_bound(mp(r, -1LL));
      if (rit == rs.end()) {
        rs.emplace(r, new_c);
      } else {
        if (r == (*rit).fr) { // same with *rit
          if (new_c < (*rit).sc) {
            rs.erase(rit);
            rs.emplace(r, new_c);
          }
        } else { // r < *rit
          if (new_c < (*rit).sc) {
            rs.emplace(r, new_c);
          }
        }
      }
    }
  }

  // Now, all distance is calculated.
  if (rs.size() > 0) {
    ll r, c;
    tie(r, c) = *(--rs.end());
    if (r == n) {
      cout << c << endl;
      return 0;
    } else { // r can't reach to N
      cout << -1 << endl;
      return 0;
    }
  }

  cout << -1 << endl;
  return 0;
}
