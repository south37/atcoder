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
  ll N;
  cin >> N;
  vector<ll> P(N);
  rep(i, N) {
    cin >> P[i];
  }
  // printvec(P);

  map<ll, ll> mp; // number => count
  rep(i, N) {
    ll x = P[i];

    if (mp.count(x) > 0) {
      ll cnt = mp[P[i]];
      mp.erase(x);
      mp[x+1] = cnt+1;
    } else {
      mp[x+1] = 1;
    }
  }

  // cout << "mp: " << endl;
  // printmap(mp);

  ll ma = 0;
  for (auto x : mp) {
    if (ma < x.second) {
      ma = x.second;
    }
  }

  cout << N - ma << endl;
}
