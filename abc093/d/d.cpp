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

const ll INF = (ll)1e9 + 5;
const ll MOD = 1000000007;  // 1e9 + 7

// return true when maxim number is equal or smaller than x.
bool check(ll a, ll b, ll x) {
  // Try 100 elements in [x/2-50, x/2+50]
  ll tmp = 0;
  for (ll i = max(x/2 - 50, 1ll); i <= min(x/2 + 50, x); ++i) {
    // pair i-th smallest(from a) and i-th greatest(from b)
    ll L = i;
    if (L >= a) { ++L; } // [1,...,a-1,a+1..L]
    ll R = x+1-i;
    if (i <= x-b+1) { ++R; } // [R,...,b-1, b+1, ..., x]
    tmp = max(tmp, L*R);
  }

  return tmp < a * b;
}

void solve() {
  ll a, b;
  cin >> a >> b;

  ll l = 0;
  ll r = INF;
  // find the boundary of [t, t, ..., t, f, ..., f]
  while (r-l > 1) {
    ll m = (r+l)>>1;
    if (check(a, b, m)) {
      l = m;
    } else {
      r = m;
    }
  }
  cout << l << endl;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll q;
  cin >> q;
  rep(iter, q) {
    solve();
  }
}
