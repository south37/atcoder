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

int dx[] = { 1, -1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };

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

int main(int argc, char** argv) {
  int N, A, B, C, D;
  cin >> N >> A >> B >> C >> D;
  --A; --B; --C; --D;
  string S;
  cin >> S;

  // Check reachability of sunuke.
  for (int i = A; i < C; ++i) {
    if (S[i] == '#' && S[i+1] == '#') {
      cout << "No" << endl;
      return 0;
    }
  }
  // Check reachability of hunuke.
  for (int i = B; i < D; ++i) {
    if (S[i] == '#' && S[i+1] == '#') {
      cout << "No" << endl;
      return 0;
    }
  }

  // Now, sunuke and hunke can reach the goal if they are alone.
  if (D > C) {
    cout << "Yes" << endl;
    return 0;
  }

  // Here, sunuke must overtake hunuke.
  bool ans = false;
  for (int i = B; i <= D; ++i) {
    if (S[i-1] == '.' && S[i] == '.' && S[i+1] == '.') {
      ans = true;
      break;
    }
  }

  if (ans) {
    cout << "Yes" << endl;
  } else {
    cout << "No" << endl;
  }
}
