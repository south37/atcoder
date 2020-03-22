// ref. https://img.atcoder.jp/agc043/editorial.pdf
// ref. https://atcoder.jp/contests/agc043/submissions/11047912

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
  string s;
  cin >> s;
  vector<ll> a(n);
  vector<ll> e(n); // the odd or even of a. 0 or 1.
  bool has1 = false;
  rep(i, n) {
    a[i] = (s[i] - '0') - 1; // 0,1,2
    if (a[i] == 1) { has1 = true; }
    e[i] = a[i] % 2;
  }
  // Here, calculate the answer
  {
    int ans = 0;
    rep(i, n) {
      // We want to known the contribution of (n-1)C(i) using Lucas's theorem.
      // The bit representatio of n-1 must have all bits in i. (n-1)C(i) mod 2 == 1 if ((n-1)&i) == i, else 0.
      if (((n-1)&i) != i) { continue; }
      ans ^= e[i];
    }
    if (ans == 1) { // odd case
      cout << ans << endl;
      return 0;
    }
  }

  // Here, ans is 0 or 2
  if (has1) { // 1 is in a, so ans is not 2.
    cout << 0 << endl;
    return 0;
  }

  // Here, ans is 0 or 2. a includes only 0 or 2. divide whole a by 2 and calculate same value.
  rep(i, n) {
    // 0 => 0, 2 => 1
    a[i] /= 2;
  }
  // Here, calculate the answer
  {
    int ans = 0;
    rep(i, n) {
      // We want to known the contribution of (n-1)C(i) using Lucas's theorem.
      // The bit representatio of n-1 must have all bits in i. (n-1)C(i) mod 2 == 1 if ((n-1)&i) == i, else 0.
      if (((n-1)&i) != i) { continue; }
      ans ^= e[i];
    }
    cout << ans*2 << endl;
  }
}
