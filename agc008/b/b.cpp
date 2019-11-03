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
  ll N, K;
  cin >> N >> K;
  vector<ll> a(N);
  rep(i, N) {
    cin >> a[i];
  }
  // printvec(a);

  vector<ll> s(N+1);
  rep(i, N) {
    s[i+1] = s[i] + a[i];
  }

  vector<ll> p_s(N+1); // The summention of positive ones.
  rep(i, N) {
    p_s[i+1] = p_s[i] + (a[i] > 0 ? a[i] : 0);
  }

  ll ans = 0;
  for (int i = 0; i + K <= N; ++i) {
    ll k = s[i+K] - s[i]; // [i, i+K-1]
    ll rest = p_s[i] + (p_s[N]-p_s[i+K]); // [0, i-1] + [i+K, N-1]
    ll c = (k > 0 ? k : 0) + rest;

    if (ans < c) {
      ans = c;
    }
  }

  cout << ans << endl;
}
