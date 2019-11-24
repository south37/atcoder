// editorial. https://img.atcoder.jp/abc146/editorial.pdf

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

  ll n, k;
  cin >> n >> k;
  vector<ll> a(n);
  rep(i, n) {
    cin >> a[i];
  }
  vector<ll> s(n+1); // s[i] .. The sum of a[j] in [0, i)
  rep(i, n) {
    s[i+1] = s[i] + a[i];
  }
  // cout << "s: "; printvec(s);

  vector<ll> d(n+1); // d[i] .. (s[i] - i)%k. d[0] = 0.
  rep(i, n) {
    d[i+1] = (s[i+1] - (i+1))%k;
  }
  // cout << "d: "; printvec(d);

  // we want to calculate the count of all pairs (i,j) where d[i] == d[j] and i<j and j-i<k.
  // (s[j]-s[i])%k == j-i <=> d[j] == d[i]

  ll ans = 0;
  map<ll, ll> cnts;
  rep(i, n+1) {
    if (i >= k) {
      --cnts[d[i-k]];
    }
    // Now, cnts contains d[i-k+1]..d[i-1]. k-2 elements.
    ans += cnts[d[i]];

    ++cnts[d[i]];
  }

  cout << ans << endl;
}
