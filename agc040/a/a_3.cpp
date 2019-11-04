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
  for (int i = 0; i < tree.size(); ++i) {
    cout << i + 1 << ": ";
    printvec(tree[i]);
  }
}
template<class T, class U> void printmap(const map<T, U>& mp) {
  for (auto x : mp) { cout << x.first << "=>" << x.second << endl; }
}

#define rep(i, n) for(ll i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

int main(int argc, char** argv) {
  string s;
  cin >> s;
  ll N = s.size() + 1;

  // Run Length Encoding
  // e.g. issii -> i1s2i2
  vector< pair<char, ll> > cnts;
  rep(i, N-1) {
    ll cnt = 1;
    while (i < N - 2 && s[i] == s[i+1]) {
      ++cnt;
      ++i;
    }
    cnts.emplace_back(s[i], cnt);
  }

  // For Debug
  // for (auto x : cnts) {
  //   cout << x.first << ", " << x.second << endl;
  // }

  vector<ll> a(N);
  ll i = 0;
  for (auto x : cnts) {
    if (x.first == '>') {
      for (ll j = 1; j <= x.second; ++j) {
        a[i+j] = x.second - j;
      }
      a[i] = max(i > 0 ? a[i-1] : 0, i < N-1 ? a[i+1] : 0) + 1;
      i += x.second;
    } else { // <
      a[i] = 0;
      for (ll j = 1; j <= x.second; ++j) {
        a[i+j] = j;
      }
      i += x.second;
    }
  }

  // For Debbug
  // printvec(a);

  ll ans = 0;
  rep(i, N) { ans += a[i]; }
  cout << ans << endl;
}
