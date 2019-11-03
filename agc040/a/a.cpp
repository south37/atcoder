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

string s;
ll N;
vector<ll> a;

ll calc(ll i) {
  if (a[i] > 0) { return a[i]; }

  if (i > 0 && i < N-1) {
    if (s[i-1] == '>' && s[i] == '<') {
      return a[i] = 0;
    } else if (s[i-1] == '<' && s[i] == '>') {
      ll m = max(calc(i-1), calc(i+1));
      return a[i] = m+1;
    } else if (s[i-1] == '<' && s[i] == '<') {
      return a[i] = calc(i-1) + 1;
    } else { // > >
      return a[i] = calc(i+1) + 1;
    }
  } else if (i == 0) {
    if (s[i] == '<') {
      return a[i] = 0;
    } else { // >
      return a[i] = calc(i+1) + 1;
    }
  } else { // i == N-1
    if (s[i-1] == '<') {
      return a[i] = calc(i-1) + 1;
    } else { // >
      return a[i] = 0;
    }
  }
}
int main(int argc, char** argv) {
  cin >> s;
  N = s.size() + 1;
  a.assign(N, -1);

  rep(i, N) {
    calc(i);
  }
  ll ans = 0;
  rep(i, N) {
    ans += a[i];
  }

  cout << ans << endl;
}
