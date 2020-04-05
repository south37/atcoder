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
  string s;
  cin >> s;
  string l = s.substr(0, n);
  string r = s.substr(n);
  reverse(all(r));
  // cout << "l: " << l << endl;
  // cout << "r: " << r << endl;

  // Here, we want to check all substring of l and r.
  unordered_map<string, ll> patterns; // pair of <pattern, count>
  rep(i, 1ll<<n) {
    string red, blue;
    rep(j, n) {
      if (i & 1ll<<j) {
        red += l[j];
      } else {
        blue += l[j];
      }
    }
    reverse(all(blue));

    string pattern = red + "$" + blue;
    ++patterns[pattern];
  }

  ll ans = 0;
  // Here, we want to find the pattern in right.
  rep(i, 1ll<<n) {
    string red, blue;
    rep(j, n) {
      if (i & 1ll<<j) {
        red += r[j];
      } else {
        blue += r[j];
      }
    }
    reverse(all(blue));

    string pattern = red + "$" + blue;
    if (patterns.find(pattern) != patterns.end()) {
      ans += patterns[pattern];
    }
  }

  cout << ans << endl;
}
