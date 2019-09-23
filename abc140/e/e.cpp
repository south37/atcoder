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
  int N;
  cin >> N;
  vector<P> sorted;
  rep(i, N) {
    ll p;
    cin >> p;
    sorted.emplace_back(p, i); // first is value, second is index
  }
  sort(all(sorted));
  reverse(all(sorted));

  set<ll> st; // Contains the indices of larger values in each step.
  st.insert(-2); st.insert(-1); // left guard
  st.insert(N); st.insert(N+1); // right guard

  ll ans = 0;
  for (auto e : sorted) {  // Check value and index order by decreasing.
    ll v = e.first;
    ll i = e.second;

    auto it = upper_bound(all(st), i);
    --it; --it;
    ll l2 = *(it++);
    ll l1 = *(it++);
    ll r1 = *(it++);
    ll r2 = *it;

    if (r1 < N) { // r1 must be in [0, N-1]
      ans += v * (i - l1) * (r2 - r1);
    }
    if (l1 >= 0) { // l1 must be in [0, N-1]
      ans += v * (l1 - l2) * (r1 - i);
    }
    st.insert(i);
  }

  cout << ans << endl;
}
