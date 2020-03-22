// ref. https://img.atcoder.jp/agc043/editorial.pdf
// ref. https://atcoder.jp/contests/agc043/submissions/11046589

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
#include <time.h>       /* time */

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
  string a;
  cin >> a;
  vector<ll> d(n);
  rep(i, n) {
    d[i] = (a[i] - '0') - 1;
  }

  vector<ll> e(n); // even, odd of d
  rep(i, n) {
    e[i] = d[i] % 2;
  }
  ll oddEven = 0;
  rep(i, n) {
    int j = (n-1) - i;
    if ((i^j) == (i+j)) {
      oddEven += e[i];
      oddEven %= 2;
    }
  }
  // Here, if oddEven.x == 1, then ans is odd. So, ans is 1.
  if (oddEven == 1) {
    cout << 1 << endl;
    return 0;
  }

  // Here, ans is 0 or 2
  bool has1 = false;
  rep(i, n) {
    if (d[i] == 1) {
      has1 = true;
    }
  }
  if (has1) {
    cout << 0 << endl;
  } else {
    cout << 2 << endl;
  }
}
