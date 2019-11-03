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
  //printvec(P);

  vector<ll> Q(N);
  rep(i, N) {
    Q[P[i]-1] = i+1;
  }
  //printvec(Q);

  // We search the longuest continueous increasing seqneunces
  ll ans = 0;
  ll cnt = 1;
  for (int i = 0; i < N-1; ++i) {
    if (Q[i] < Q[i+1]) {
      ++cnt;
    } else {
      if (cnt > ans) {
        ans = cnt;
      }
      cnt = 1;
    }
  }

  cout << N - ans << endl;
}
