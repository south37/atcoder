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

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

int main(int argc, char** argv) {
  int H, W, N;
  cin >> H >> W >> N;
  int sr, sc;
  cin >> sr >> sc;
  --sr; --sc;
  string S, T;
  cin >> S;
  cin >> T;

  // At first, check left-right.
  int left = 0, right = W-1;  // If piece is in [left, right] before the step, it is ok.
  if (S[N-1] == 'L') { ++left; }  // shrink
  if (S[N-1] == 'R') { --right; } // shrink
  // W >= 2, so it is ok here.
  for (int i = N - 2; i >= 0; --i) {
    if (T[i] == 'L') { right = min(right + 1, W-1); } // expand
    if (T[i] == 'R') { left = max(left - 1, 0); }   // expand
    if (S[i] == 'L') { ++left; }                    // shrink
    if (S[i] == 'R') { --right; }                   // shrink
    if (left > right) { // Bad
      cout << "NO" << endl;
      return 0;
    }
  }
  if (sc < left || right < sc) { // Bad
    cout << "NO" << endl;
    return 0;
  }

  // Next, check up-down.
  int up = 0, down = H-1;  // If piece is in [up, down] before the step, it is ok.
  if (S[N-1] == 'U') { ++up; }   // shrink
  if (S[N-1] == 'D') { --down; } // shrink
  // W >= 2, so it is ok here.
  for (int i = N - 2; i >= 0; --i) {
    if (T[i] == 'U') { down = min(down + 1, H-1); } // expand
    if (T[i] == 'D') { up = max(up - 1, 0); }     // expand
    if (S[i] == 'U') { ++up; }                    // shrink
    if (S[i] == 'D') { --down; }                  // shrink
    if (up > down) { // Bad
      cout << "NO" << endl;
      return 0;
    }
  }
  if (sr < up || down < sr) { // Bad
    cout << "NO" << endl;
    return 0;
  }

  cout << "YES" << endl;
}
