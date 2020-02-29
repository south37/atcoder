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

  ll n;
  cin >> n;
  vector<vector<P>> a(n);
  rep(i, n) {
    vector<P>& denotes = a[i];
    ll a_size;
    cin >> a_size;
    rep(j, a_size) {
      ll x, y;
      cin >> x >> y;
      --x; // 0-indexed
      denotes.emplace_back(x, y);
    }
  }

  ll ans = 0;
  // check all case. 2^15
  rep(i, 1ll<<n) {
    vector<int> states(n); // 0 is false, 1 is true
    rep(j, n) {
      if ((i>>j) & 1) { // consider j is true.
        states[j] = 1;
      }
    }
    // printvec(states);
    // cout << (ll)__builtin_popcount(i) << endl;

    bool is_ok = true;
    rep(j, n) {
      if ((i>>j) & 1) { // consider j is true.
        for (P& p : a[j]) {
          ll x = p.first;
          ll y = p.second;
          // cout << "j: " << j << endl;
          // cout << "x: " << x << endl;
          // cout << "y: " << y << endl;
          // cout << "states[x]: " << states[x] << endl;
          if (states[x] != y) { // invalid
            is_ok = false;
            break;
          }
        }
      }
    }
    // cout << "is_ok: " << is_ok << endl;
    if (is_ok) { // this condition is ok
      ans = max(ans, (ll)__builtin_popcount(i));
    }
  }
  cout << ans << endl;
}
