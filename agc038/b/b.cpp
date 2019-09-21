#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <unordered_map>
#include <vector>
#include <set>
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
  int N, K;
  cin >> N >> K;
  vector<int> P(N);
  rep(i, N) {
    cin >> P[i];
  }

  // Check sorted.
  int cnt = 1;
  vector<int> cnts(N);
  cnts[0] = 1;
  for (int i = 1; i < N; ++i) {
    if (P[i-1] < P[i]) {
      ++cnt;
      cnts[i] = cnt;
    } else {
      cnt = 1;
      cnts[i] = cnt;
    }
  }
  vector<bool> sorted(N); // [i..i+K-1] is sorted
  for (int i = 0; i + K - 1 < N; ++i) {
    sorted[i] = (cnts[i + K - 1] == K);
  }

  int ans = 1;
  bool taken_identical = false;
  if (sorted[0]) { taken_identical = true; }

  set<int> st; // for min and max of [i+1..i+K-1]. This is the intersection of [i..i+K-1] and [i+1..i+K].
  // At first, set [1..K-1]
  for (int i = 1; i <= K-1; ++i) {
    st.insert(P[i]);
  }
  for (int l = 0, r = K; r < N; ++l, ++r) {
    if (P[l] < *st.begin() && *st.rbegin() < P[r]) {
      // The order of [l-1..r-1] and [l..r] is same after operation. So, do not increment ans.
    } else {
      if (sorted[l+1]) {
        // Skip if identical is already taken.
        if (!taken_identical) {
          taken_identical = true;
          ++ans;
        }
      } else {
        ++ans;
      }
    }
    st.erase(P[l+1]);
    st.insert(P[r]);
  }

  cout << ans << endl;
}
