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

  vector<ll> C(N+1); // The count of each A. C[0] is dummy.
  rep(i, N) {
    ++C[A[i]];
  }
  vector<ll> D(N+1); // The count of each C.
  for (ll i = 1; i <= N; ++i) {
    ++D[C[i]];
  }
  // Here, the count of k is represented as D[k].

  // f(X) .. The maximam length of sequence when X sequences can be extracted.
  // We want to calculate the f(X) = sum(j=1,N) min(C[j], X) / X
  // f(X) = (sum(k=1,X) kD[k] + X*sum(k=X+1,N) D[k])
  vector<ll> ckD(N+1);
  for (ll k = 1; k <= N; ++k) {
    ckD[k] = ckD[k-1] + k * D[k];
  }
  vector<ll> cD(N+1);
  for (ll k = 1; k <= N; ++k) {
    cD[k] = cD[k-1] + D[k];
  }
  vector<ll> f(N+1);
  for (ll i = 1; i <= N; ++i) {
    f[i] = (ckD[i] + i*(cD[N] - cD[i])) / i;
  }

  // f(X) is decreasing order.
  // Here, the maximum X where K <= f(X) is the answer of each K.

  reverse(all(f));
  f.resize(N); // f[N] is thrown away.
  // Now, f is increasing order.
  for (int i = 1; i <= N; ++i) {
    auto it = lower_bound(all(f), i);
    if (it != f.end()) {
      int j = it - f.begin(); // index
      cout << (N - j) << endl;
    } else { // not found
      cout << 0 << endl;
    }
  }
}
