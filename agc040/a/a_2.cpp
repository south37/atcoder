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
  vector<ll> a(N, -1);

  if (s[0] == '<') { a[0] = 0; }
  if (s[N-2] == '>') { a[N-1] = 0; }

  // Set 0 to > <
  for (int i = 1; i < N-1; ++i) {
    if (s[i-1] == '>' && s[i] == '<') {
      a[i] = 0;
    }
  }
  // Set number from left
  for (int i = 1; i <= N-2; ++i) {
    if (s[i-1] == '<' && s[i] == '<') {
      a[i] = a[i-1] + 1;
    }
  }
  // Set number from right
  for (int i = N-2; i >= 1; --i) {
    if (s[i-1] == '>' && s[i] == '>') {
      a[i] = a[i+1] + 1;
    }
  }
  // Set to < >
  for (int i = 1; i < N-1; ++i) {
    if (s[i-1] == '<' && s[i] == '>') {
      a[i] = max(a[i-1], a[i+1]) + 1;
    }
  }
  if (s[0] == '>') { a[0] = a[1] + 1; }
  if (s[N-2] == '<') { a[N-1] = a[N-2] + 1; }

  ll ans = 0;
  rep(i, N) {
    ans += a[i];
  }

  cout << ans << endl;
}
