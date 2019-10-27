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

const ll INF = 1e18;
const ll MOD = 1000000007;  // 1e9 + 7

ll N, K;
vector<ll> A;
vector<ll> F;

bool condition(ll limit) {
  // all A[i] * B[i] must be equal or lower than limit.
  ll summed = 0; // The necessary decreasing count.
  rep(i, N) {
    ll cnt = limit / F[i];
    // F[i] * cnt <= limit.
    if (cnt <= A[i]) { // A[i] is larger than cnt
      summed += (A[i] - cnt);
    }
  }
  return (summed <= K);
}

int main(int argc, char** argv) {
  cin >> N >> K;
  A.resize(N);
  F.resize(N);
  rep(i, N) {
    cin >> A[i];
  }
  sort(all(A)); // increasing order
  rep(i, N) {
    cin >> F[i];
  }
  sort(all(F));
  reverse(all(F)); // decreasing order

  // cout << "A: ";
  // rep(i, N) {
  //   cout << A[i] << " ";
  // }
  // cout << endl;
  // cout << "F: ";
  // rep(i, N) {
  //   cout << F[i] << " ";
  // }
  // cout << endl;
  // ll summed = 0;
  // rep(i, N) {
  //   summed += A[i] * F[i];
  // }

  // We use binary search.
  ll l = -1;
  ll r = INF;
  while (r - l > 1) {
    ll mid = (l + r)/2;
    if (condition(mid)) { // ok
      r = mid;
    } else { // ng
      l = mid;
    }
  }

  cout << r << endl;
}
