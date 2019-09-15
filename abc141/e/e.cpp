#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

int dx[] = { 1, -1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };

typedef long long ll;
typedef pair<int, int> P;
typedef tuple<int, int, int> triple;

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

const int COM_MAX = 500010;
ll fac[COM_MAX], facinv[COM_MAX], inv[COM_MAX];
void COMinit() {
  fac[0] = fac[1] = 1;
  facinv[0] = facinv[1] = 1;
  inv[1] = 1;
  for(int i = 2; i < COM_MAX; ++i) {
    fac[i] = fac[i-1] * i % MOD;
    inv[i] = MOD - inv[MOD%i] * (MOD / i) % MOD;
    facinv[i] = facinv[i-1] * inv[i] % MOD;
  }
}

ll COM(ll n, ll k) {
  return (fac[n] * facinv[k] % MOD) * facinv[n-k] % MOD;
}

ll PERM(ll n, ll k) {
  return (fac[n] * facinv[k] % MOD);
}

string S;
vector< set<int> > chars(26);

int main(int argc, char** argv) {
  int N;
  cin >> N;

  cin >> S;

  // For Debug
  // cout << N << endl;
  // cout << S << endl;
  rep(i, N) {
    int c = S[i] - 'a';
    chars[c].insert(i);
  }

  // For Debug
  // rep(i, 26) {
  //   cout << char('a' + i) << ": ";
  //   for (auto e : chars[i]) {
  //     cout << e << " ";
  //   }
  //   cout << endl;
  // }

  vector<int> distance(N);

  // Try search
  rep(i, N) {
    // search(i);
    int c = S[i] - 'a';
    auto next_it = chars[c].upper_bound(i); // Here, we only check first one.
    if (next_it == chars[c].end()) {
      continue;
    }

    // NOTE: This is naive implementaion. O(N ^ 3).
    for (auto it = next_it; it != chars[c].end(); ++it) {
      int current_pos = i;
      // *it is the next position.
      int next_pos = *it;

      // cout << "current_pos: " << current_pos << endl;
      // cout << "next_pos: " << next_pos << endl;

      int dist = 1;  // Now, S[current_pos] and S[next_pos] is same, wo distance is 1.
      while ((next_pos + 1 < N) && (S[current_pos+1] == S[next_pos+1]) && (current_pos+1 < *it)) {
        ++current_pos;
        ++next_pos;
        ++dist;
      }
      // cout << "[end] current_pos: " << current_pos << endl;
      // cout << "[end] next_pos: " << next_pos << endl;
      distance[i] = max(distance[i], dist);
    }
  }

  // For Debug
  // rep(i, N) {
  //   cout << char('a' + i) << ": " << distance[i] << endl;
  // }
  int r = 0;
  rep(i, N) {
    r = max(r, distance[i]);
  }
  cout << r << endl;
}
