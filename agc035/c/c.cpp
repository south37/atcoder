#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string.h>

using namespace std;

#define COUT(x) cout << #x << " = " << (x) << " (L" << __LINE__ << ")" << endl

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

int gcd(int a, int b) {
  if (a < b) { swap(a, b); }
  if (b == 0) { return a; }
  return gcd(b, a % b);
}

bool prime(int n) {
  for (int i = 2; i <= sqrt(n); ++i) {
    if (n % i == 0) { return false; }
  }
  return n != 1;
}

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

int MSB(int n) {
  int r = -1;
  for (; n > 0; n >>= 1) {
    ++r;
  }
  return r;
}

int main(int argc, char** argv) {
  int N;
  cin >> N;

  if (!(N & N - 1)) { // N is 2 ** x
    cout << "No" << endl;
    return 0;
  }

  cout << "Yes" << endl;
  cout << 1 + N << " " << 3 + N << endl;
  for (int i = 2; i < N + 1; ++i) {
    if (N % 2 == 0 && i == N) {
      int t = 1 << MSB(N);
      cout << N << " " << t << endl;
      cout << N + N << " " << (t ^ N ^ 1) << endl;
    } else {
      cout << 1 << " " << i << endl;
      cout << i << " " << (i ^ 1) + N << endl;
    }
  }
}
