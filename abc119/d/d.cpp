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

const ll INF = 1e12; // larger than the longuest distance of s and t.
const ll MOD = 1000000007;  // 1e9 + 7

// Returns the nearest position in left and right.
// The format is (left, right). left < x <= right.
tuple<ll, ll> nearest_pair(vector<ll>& t, ll x) {
  auto it = lower_bound(all(t), x);
  ll left, right;

  if (it == t.end()) {
    right = INF;
    --it;
    left = *it;
  } else if (it == t.begin()) {
    right = *it;
    left = -INF;
  } else {
    right = *it;
    --it;
    left = *it;
  }

  return make_tuple(left, right);
}

ll nearest(vector<ll>& t, ll x) {
  ll left, right;
  tie(left, right) = nearest_pair(t, x);
  if (abs(left - x) < abs(right - x)) {
    return left;
  } else {
    return right;
  }
}

int main(int argc, char** argv) {
  ll A, B, Q;
  cin >> A >> B >> Q;
  vector<ll> s(A);
  vector<ll> t(B);
  rep(i, A) {
    cin >> s[i];
  }
  rep(i, B) {
    cin >> t[i];
  }
  rep(i, Q) {
    ll x;
    cin >> x;

    // Try s->t case.
    ll sl, sr;
    tie(sl, sr) = nearest_pair(s, x);
    ll c1 = abs(x - sl) + abs(sl - nearest(t, sl));
    ll c2 = abs(x - sr) + abs(sr - nearest(t, sr));

    // Try t->s case.
    ll tl, tr;
    tie(tl, tr) = nearest_pair(t, x);
    ll c3 = abs(x - tl) + abs(tl - nearest(s, tl));
    ll c4 = abs(x - tr) + abs(tr - nearest(s, tr));

    cout << min(min(c1, c2), min(c3, c4)) << endl;
  }
}
