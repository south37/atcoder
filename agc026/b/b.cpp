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

ll gcd(ll a, ll b) {
  if (a < b) { swap(a, b); }
  if (b == 0) { return a; }
  return gcd(b, a % b);
}

bool solve(ll A, ll B, ll C, ll D) {
  if (A < B) { return false; }
  if (D < B) { return false; }
  if (C >= B) { return true; }
  // Now, A >= B, D >= B, C < B
  // The count is changed by (D % B). We can consider counts in MOD B.
  // If g = gcd(B, D % B), then the count can be (A % g + g * k) % B (k = 0, 1, ...). It has cycle.
  // e.g. A = 1, B = 7, D = 10, then g = 1 and (count % B) can be [1, 4, 0, 3, 6, 2, 5, 1, ...].
  // e.g. A = 1, B = 8, D = 10, then g = 2 and (count % B) can be [1, 3, 5, 7, 1, ...].
  // The maximum value is B - g + (A % g). We should check it.
  ll g = gcd(B, D % B);
  ll maximum = B - g + (A%g);
  return (maximum <= C);
}

int main(int argc, char** argv) {
  ll T;
  cin >> T;
  rep(i, T) {
    ll A, B, C, D;
    cin >> A >> B >> C >> D;
    bool ans = solve(A, B, C, D);
    if (ans) {
      cout << "Yes" << endl;
    } else {
      cout << "No" << endl;
    }
  }
}
