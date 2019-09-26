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

int dx[] = { 1, -1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e9;
ll MOD;

// Mod int
// cf. https://www.youtube.com/watch?v=1Z6ofKN03_Y
struct mint {
  ll x;
  mint(ll x = 0) : x((x + MOD) % MOD) {}
  mint& operator+= (const mint a) {
    if ((x += a.x) >= MOD) x %= MOD;
    return *this;
  }
  mint operator+ (const mint a) const {
    mint res(*this);
    return res += a;
  }
  mint& operator-= (const mint a) {
    if ((x += MOD - a.x) >= MOD) x %= MOD;
    return *this;
  }
  mint operator- (const mint a) const {
    mint res(*this);
    return res -= a;
  }
  mint& operator*= (const mint a) {
    (x *= a.x) %= MOD;
    return *this;
  }
  mint operator* (const mint a) const {
    mint res(*this);
    return res *= a;
  }
  mint pow(ll t) const {
    if (!t) { return 1; }
    mint a = pow(t >> 1);
    a *= a;
    if (t & 1) a *= *this;
    return a;
  }

  // for prime mod
  mint inv() const {
    return pow(MOD-2);
  }
  mint& operator/= (const mint a) {
    return (*this) *= a.inv();
  }
  mint operator/ (const mint a) const {
    mint res(*this);
    return res /= a;
  }
};

// Combination mod prime.
// cf. https://www.youtube.com/watch?v=1Z6ofKN03_Y
struct Combination {
  vector<mint> fact, ifact;
  Combination(int n) : fact(n + 1), ifact(n + 1) {
    assert(n < MOD); // n must be lower than MOD.
    fact[0] = 1;
    for (int i = 1; i <= n; ++i) { fact[i] = fact[i-1] * i; }
    ifact[n] = fact[n].inv();
    for (int i = n; i >= 1; --i) { ifact[i-1] = ifact[i] * i; }
  }
  mint operator() (int n, int k) {
    if (k < 0 || k > n) { return 0; }
    return fact[n] * ifact[k] * ifact[n-k];
  }
};

int main(int argc, char** argv) {
  int p;
  cin >> p;
  MOD = p;

  vector<int> a(p);
  rep(i, p) {
    cin >> a[i];
  }

  Combination c(p-1);
  vector<mint> b(p);
  rep(i, p) {
    if (!a[i]) { continue; }
    // 1 - (x-i) ** (p-1) = b[p-1] * x ** (p-1) + b[p-2] * x ** (p-2) + ... + b[0]
    b[0] += 1;
    mint pw = 1; // pw = (-i) ** (p - 1 - j) in each step.
    for (int j = p - 1; j >= 0; --j) {
      b[j] -= pw * c(p-1, j);
      pw *= -i;
    }
  }
  rep(i, p) {
    cout << b[i].x;
    if (i != p-1) {
      cout << " ";
    }
  }
  cout << endl;
}
