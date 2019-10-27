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
  ll N, K;
  cin >> N >> K;
  vector<ll> A(N);
  vector<ll> F(N);
  rep(i, N) {
    cin >> A[i];
  }
  sort(all(A)); // increasing order
  rep(i, N) {
    cin >> F[i];
  }
  sort(all(F));
  reverse(all(F)); // decreasing order

  cout << "A: ";
  rep(i, N) {
    cout << A[i] << " ";
  }
  cout << endl;
  cout << "F: ";
  rep(i, N) {
    cout << F[i] << " ";
  }
  cout << endl;
  ll summed = 0;
  rep(i, N) {
    summed += A[i] * F[i];
  }
  cout << "summed: " << summed << endl;

  vector<ll> s(N+1); // cumulated sum of A. s[i] .. sum of [0, i)
  rep(i, N) {
    s[i+1] = s[i] + A[i];
  }

  auto iter = upper_bound(all(s), K);
  if (iter == s.end()) { // The sum of all A is lower than K.
    cout << 0 << endl;
    return 0;
  } else {
    ll i = iter - s.begin(); // i is the lowest index where s[i] > K. s[i] = A[0] + .. + A[i-1].
    // Here, A[0], .. A[i-2] should be 0.
    // A[i-1] = s[i] - K
    for (int j = 0; j < i-1; ++j) { // j < i should be 0.
      A[j] = 0;
    }
    A[i-1] = s[i] - K;

    // For Debug
    cout << "After: " << endl;
    cout << "A: ";
    rep(i, N) {
      cout << A[i] << " ";
    }
    cout << endl;
    cout << "F: ";
    rep(i, N) {
      cout << F[i] << " ";
    }
    cout << endl;

    ll ans = 0;
    rep(j, N) {
      ans += A[j] * F[j];
    }
    cout << ans << endl;
    return 0;
  }
}
