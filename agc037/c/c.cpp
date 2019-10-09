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

ll powmod(ll x, ll n) { // like pow(x, n)
  ll r = 1;
  while (n) {
    if (n & 1) {
      r = r * x % MOD;
    }
    x = x * x % MOD;
    n >>= 1;
  }
  return r;
}

int main(int argc, char** argv) {
  int N;
  cin >> N;
  vector<ll> A(N);
  rep(i, N) {
    cin >> A[i];
  }
  vector<ll> B(N);
  rep(i, N) {
    cin >> B[i];
  }

  // If B[i] > B[i-1] + B[i+1], then we update B[i] -> B[i] % (B[i-1] + B[i+1])
  priority_queue<P> q; // The queue of pairs. The pair is [B[i], i].

  ll cnt = 0; // The count of operation.
  rep(i, N) {
    ll b = B[i];
    ll a = B[(i-1+N)%N];
    ll c = B[(i+1)%N];
    if ((b > a + c) && b != A[i]) {
      q.emplace(b, i);
    }
  }
  while (!q.empty()) {
    P p = q.top(); q.pop();
    int i = p.second;

    ll b = B[i];
    ll a = B[(i-1+N)%N];
    ll c = B[(i+1)%N];
    if ((b > a + c) && b > A[i]) {
      ll diff = (b - A[i]) / (a + c);
      B[i] -= diff * (a + c);
      cnt += diff; // cnt is the count of "B[i] = B[i] - (a + c)".
      q.emplace(a, (i-1+N)%N);
      q.emplace(c, (i+1)%N);
    }
  }
  // For Debug
  // cout << "after:" << endl;
  // rep(i, N) {
  //   cout << B[i] << " ";
  // }
  // cout << endl;

  bool ans = true;
  rep(i, N) {
    if (A[i] != B[i]) {
      ans = false;
      break;
    }
  }
  if (ans) {
    cout << cnt << endl;
  } else {
    cout << -1 << endl;
  }
}
