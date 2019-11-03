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

const ll INF = 1e12;
const ll MOD = 1000000007;  // 1e9 + 7

int main(int argc, char** argv) {
  ll N;
  cin >> N;
  vector<P> lrs;
  rep(i, N) {
    ll L, R;
    cin >> L >> R;
    lrs.emplace_back(L, R);
  }
  sort(all(lrs));

  for (auto x : lrs) { cout << x.first << ", " << x.second << " " << endl; }

  vector<ll> min_r(N+1, INF); // min_r[i+1] .. min R[i] in [0, i]. min_r[0] = 0
  rep(i, N) {
    min_r[i+1] = min(min_r[i], lrs[i].second);
  }
  vector<ll> min_r2(N+1, INF); // min_r2[i-1] .. min R[i] in [i, N-1]. min_r[N-1] = 0
  for (int i = N; i > 0; --i) {
    min_r2[i-1] = min(min_r2[i], lrs[i-1].second);
  }
  vector<ll> max_l(N+1); // min_l[i-1] .. max L[i] in [i, N-1]. min_l[N-1] = 0
  for (int i = N; i > 0; --i) {
    max_l[i-1] = max(max_l[i], lrs[i-1].first);
  }
  cout << "min_r: ";
  printvec(min_r);
  cout << "min_r2: ";
  printvec(min_r2);
  cout << "max_l: ";
  printvec(max_l);

  ll ans = 0;

  // Try all splits.
  rep(i, N-1) { // Try N-1 times.
    ll L, R;
    tie(L, R) = lrs[i];

    ll left = min_r[i+1] - L + 1; // [0, i]
    ll right = min_r2[i] - max_l[i] + 1; // [i+1, N-1]
    ll c = left + right;

    cout << i << ": " << endl;
    cout << "left: " << left << "=" << "("<<L<<", "<<min_r[i+1]<<") "<< endl;
    cout << "right: " << right << "=" << "("<<max_l[i]<<", "<<min_r2[i]<<") "<< endl;
    cout << "c: " << c << endl;

    if (ans < c) {
      ans = c;
    }
  }

  cout << ans << endl;
}
