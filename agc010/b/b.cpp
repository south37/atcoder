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

  ll unit = 0; // In each step, sum is decreased by unit. sum of [1, N]
  rep(i, N) {
    unit += i + 1;
  }
  ll s = 0;
  rep(i, N) {
    s += A[i];
  }
  if ((s % unit) != 0) {
    cout << "NO" << endl;
    return 0;
  }

  // Now, s is dividable by unit.
  ll cnt = s / unit;

  vector<ll> diff(N); // diff[i] = A[i] - A[i-1].
  rep(i, N) {
    diff[i] = A[i]-A[(i-1+N)%N];
  }
  // For Debug
  // cout << "diff:" << endl;
  // rep(i, N) {
  //   cout << diff[i] << " ";
  // }
  // cout << endl;

  // Now, diff[i] must be cnt + (-N)*k (k=0, 1, 2, ...)
  rep(i, N) {
    diff[i] -= cnt;
  }
  // cout << "diff:" << endl;
  // rep(i, N) {
  //   cout << diff[i] << " ";
  // }
  // cout << endl;

  // Now, diff[i] must be (-N)*k (k=0, 1, 2, ...)

  // Check if diff[i] is dividable by N.
  // Check if diff[i] <= 0.
  // Check if the summention of diff[i]/N is same with cnt.
  ll n_cnt = 0;
  rep(i, N) {
    if ((diff[i] % N) != 0) {
      cout << "NO" << endl;
      return 0;
    }
    if (diff[i] > 0) {
      cout << "NO" << endl;
      return 0;
    }
    n_cnt -= diff[i] / N; // diff[i] <= 0, so we use -=.
  }
  if (n_cnt != cnt) {
    cout << "NO" << endl;
    return 0;
  }

  cout << "YES" << endl;
  return 0;
}
