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
  ll N;
  cin >> N;
  vector<ll> A(N);
  rep(i, N) {
    cin >> A[i];
  }

  vector<ll> s(N+1); // s[i] .. sum of [0, i)
  rep(i, N) {
    s[i+1] = s[i] + A[i];
  }
  // For Debug
  // rep(i, N+1) {
  //   cout << s[i] << endl;
  // }

  vector<ll> l(N); // the left index of each middle i. the middle in [0, i].
  vector<ll> r(N); // the left index of each middle i. the middle in [i+1, N-1].
  ll left = 0;
  for (int i = 1; i < N-2; ++i) { // calculate l in [1, N-3]
    ll summed = s[i+1]; // The sum of [0, i]
    while ((left <= N) && abs(summed - s[left+1]*2) < abs(summed - s[left]*2)) {
      ++left;
    }
    // Here, left is the index of minimum. summed - s[left] is minimum.
    l[i] = left;
  }
  ll right = 0;
  for (int i = 1; i < N-2; ++i) { // calculate r in [1, N-3]
    if (right < i+1) { right = i+1; } // right must be equal or larger than i+1.
    while ((right <= N) && abs((s[N]-s[right+1]) - (s[right+1]-s[i+1])) < abs((s[N]-s[right]) - (s[right]-s[i+1]))) {
      ++right;
    }
    // Here, right is the index of minimum. s[N] - s[right] is minimum.
    r[i] = right;
  }

  ll ans = INF;
  for (int i = 1; i < N-2; ++i) {
    ll left = l[i];
    ll right = r[i];

    ll l1 = s[left];
    ll l2 = s[i+1] - s[left];
    ll r1 = s[right] - s[i+1];
    ll r2 = s[N] - s[right];
    // For Debug
    // cout << l1 << "," << l2 << "," << r1 << "," << r2 << endl;
    ll min_v = min(min(l1, l2), min(r1, r2));
    ll max_v = max(max(l1, l2), max(r1, r2));
    ans = min(ans, abs(max_v - min_v));
  }

  cout << ans << endl;
}
