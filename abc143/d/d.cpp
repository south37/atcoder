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

// BIT (Fenwick Tree) with 0-indexed query
// https://youtu.be/lyHk98daDJo?t=7960
template<typename T>
struct BIT {
  int n;
  vector<T> d;
  BIT(int n=0) : n(n), d(n+1) {}
  void add(int i, T x=1) {
    i++; // 0-indexed to 1-indexed
    for (; i <= n; i += i&-i) {
      d[i] += x;
    }
  }
  T sum(int i) {
    i++; // 0-indexed to 1-indexed
    T x = 0;
    for (; i; i -= i&-i) {
      x += d[i];
    }
    return x;
  }
};

// int main(int argc, char** argv) {
//   int N;
//   cin >> N;
//   vector<int> v(N);
//   rep(i, N) {
//     cin >> v[i];
//   }
//
//   BIT<int> bit(N);
//   rep(i, N) {
//     bit.add(i, v[i]);
//   }
//
//   cout << bit.sum(4) << endl; // 24
//   cout << bit.sum(9) << endl; // 55
// }

int main(int argc, char** argv) {
  ll N;
  cin >> N;
  vector<ll> L(N);
  rep(i, N) {
    cin >> L[i];
  }
  sort(all(L)); // Now, L is sorted

  // For Debug
  // rep(i, N) {
  //   cout << L[i] << endl;
  // }

  // Here, we want to calculate the count of c < a + b. c is the largest number.
  // This is calculated by BIT.
  // add(a+b, 1).
  // sum(MAXA + MAXB) - sum(c).

  ll ans = 0;
  BIT<int> bit(2005);
  bit.add(L[0] + L[1], 1);
  for (int i = 2; i < N; ++i) {
    ll c = L[i];
    // For Debug
    // cout << "L["<<i<<"]: "<< L[i] << endl;
    // cout << bit.sum(2005) - bit.sum(c) << endl;

    ans += bit.sum(2005) - bit.sum(c); // The count of c < a + b
    rep(j, i) { // 0, 1, .. i-1.
      bit.add(L[j] + c, 1);
    }
  }

  cout << ans << endl;
}
