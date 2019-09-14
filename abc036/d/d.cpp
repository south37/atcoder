#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

int dx[] = { 1, -1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };

typedef long long ll;
typedef pair<ll, ll> P;
typedef tuple<int, int, int> triple;

int gcd(int a, int b) {
  if (a < b) { swap(a, b); }
  if (b == 0) { return a; }
  return gcd(b, a % b);
}

bool prime(int n) {
  for (int i = 2; i <= sqrt(n); i++) {
    if (n % i == 0) { return false; }
  }
  return n != 1;
}

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

ll powmod(ll x, ll y) {
  ll r = 1;
  while (y) {
    if (y & 1) {
      r = r * x % MOD;
    }
    x = x * x % MOD;
    y >>= 1;
  }
  return r;
}

ll fac[200010], facinv[200010];  // 200010 is Larger than 1e5 + 1e5.
void cominit() {
  fac[0] = facinv[0] = 1;
  ll c = 1;
  for (int i = 1; i < 200010; ++i) {
    c = c * i % MOD;
    fac[i] = c;
    facinv[i] = powmod(c, MOD-2);
  }
}

ll combination(ll n, ll k) {
  return (fac[n] * facinv[k] % MOD) * facinv[n-k] % MOD;
}

ll permutation(ll n, ll k) {
  return (fac[n] * facinv[k] % MOD);
}

vector< vector<int> > graph;

P rec(int before, int now) {
  ll w = 1, b = 1;
  for (auto x : graph[now]) {
    if (x == before) { continue; }

    P p = rec(now, x);
    w *= (p.first + p.second); // w + b
    w %= MOD;
    b *= p.first;              // w only
    b %= MOD;
  }
  return P{w, b};
}

int main(int argc, char** argv) {
  int N;
  cin >> N;
  graph.resize(N);
  rep(i, N-1) {
    int a, b;
    cin >> a >> b;
    --a; --b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  P p = rec(-1, 0);
  cout << (p.first + p.second) % MOD << endl;
}
