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

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

int main(int argc, char** argv) {
  ll N, Q;
  cin >> N >> Q;
  vector<triple> a;
  rep(i, N) {
    ll S, T, X;
    cin >> S >> T >> X;
    a.emplace_back(X, S, T);
  }
  sort(all(a)); // Sorted by X.

  set<P> D; // The set of pairs. The pair is (Di, i).
  rep(i, Q) {
    ll d;
    cin >> d;
    P p(d, i);
    D.emplace(p);
  }

  vector<ll> ans(Q, -1);

  // Here, D is sorted. We want to know the position of Si-0.5-Xi and Ti-0.5-X in D.
  // We check [S-X, T-X) by lower_bound (S-X <= Q[i..j] < T-X).
  rep(i, N) {
    ll S, T, X;
    tie(X, S, T) = a[i];

    P sp(S-X, 0); // the second is dummy.
    auto sit = D.lower_bound(sp);
    P tp(T-X, 0); // the second is dummy.
    auto tit = D.lower_bound(tp);

    for (auto it = sit; it != tit; ++it) {
      ans[(*it).second] = X; // Set distance
    }
    D.erase(sit, tit);
  }

  rep(i, Q) {
    cout << ans[i] << endl;
  }
}
