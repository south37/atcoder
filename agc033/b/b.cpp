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
  int sr, sl;
  cin >> sr >> sl;
  --sr; --sl;
  string S, T;
  cin >> S;
  cin >> T;

  vector<int> SR(N), SL(N), SU(N), SD(N); // Max values in each i.
  vector<int> TR(N), TL(N), TU(N), TD(N); // Max values in each i.
  rep(i, N) {
    if (i > 0) {
      SL[i] = SL[i-1];
      SR[i] = SR[i-1];
      SU[i] = SU[i-1];
      SD[i] = SD[i-1];

      TL[i] = TL[i-1];
      TR[i] = TR[i-1];
      TU[i] = TU[i-1];
      TD[i] = TD[i-1];
    }

    if (S[i] == 'L') {
      ++SL[i];
    }
    if (S[i] == 'R') {
      ++SR[i];
    }
    if (S[i] == 'U') {
      ++SU[i];
    }
    if (S[i] == 'D') {
      ++SD[i];
    }
    if (T[i] == 'L') {
      int base = sl + SR[i] - (i > 0 ? TL[i-1] : 0); // This is the base.
      if ((base - 1) >= 0) {
        ++TL[i];
      }
    }
    if (T[i] == 'R') {
      int base = sl - SL[i] + (i > 0 ? TR[i-1] : 0); // This is the base.
      if ((base + 1) <= W-1) {
        ++TR[i];
      }
    }
    if (T[i] == 'U') {
      int base = sr + SD[i] - (i > 0 ? TU[i-1] : 0); // This is the base.
      if ((base - 1) >= 0) {
        ++TU[i];
      }
    }
    if (T[i] == 'D') {
      int base = sr - SU[i] + (i > 0 ? TD[i-1] : 0); // This is the base.
      if ((base + 1) <= H-1) {
        ++TD[i];
      }
    }
  }

  int LimitR = (W-1) - sl; // ok if SR[i] - TL[i] <= LimitR
  int LimitL = sl;
  int LimitU = sr;
  int LimitD = (H-1) - sr;

  // // For Debug
  // cout << "H: " << H << ", W: " << W << endl;
  // // For Debug
  // cout << "s: " << sr << ", " << sl << endl;

  // // For Debug
  // cout << "LimitR: " << LimitR << endl;
  // // For Debug
  // cout << "LimitL: " << LimitL << endl;
  // // For Debug
  // cout << "LimitU: " << LimitU << endl;
  // // For Debug
  // cout << "LimitD: " << LimitD << endl;

  // // For Debug
  // cout << "SR: ";
  // rep(i, N) {
  //   cout << SR[i] << " ";
  // }
  // cout << endl;
  // // For Debug
  // cout << "TL: ";
  // rep(i, N) {
  //   cout << TL[i] << " ";
  // }
  // cout << endl;
  // // For Debug
  // cout << "SL: ";
  // rep(i, N) {
  //   cout << SL[i] << " ";
  // }
  // cout << endl;
  // // For Debug
  // cout << "TR: ";
  // rep(i, N) {
  //   cout << TR[i] << " ";
  // }
  // cout << endl;
  // // For Debug
  // cout << "SU: ";
  // rep(i, N) {
  //   cout << SU[i] << " ";
  // }
  // cout << endl;
  // // For Debug
  // cout << "TD: ";
  // rep(i, N) {
  //   cout << TD[i] << " ";
  // }
  // cout << endl;
  // // For Debug
  // cout << "SD: ";
  // rep(i, N) {
  //   cout << SD[i] << " ";
  // }
  // cout << endl;
  // // For Debug
  // cout << "TU: ";
  // rep(i, N) {
  //   cout << TU[i] << " ";
  // }
  // cout << endl;

  bool ans = true;

  for (int i = 1; i < N; ++i) {
    if (SR[i] - (i > 0 ? TL[i-1] : 0) > LimitR) {
      ans = false;
      break;
    }
    if (SL[i] - (i > 0 ? TR[i-1] : 0) > LimitL) {
      ans = false;
      break;
    }
    if (SU[i] - (i > 0 ? TD[i-1] : 0) > LimitU) {
      ans = false;
      break;
    }
    if (SD[i] - (i > 0 ? TU[i-1] : 0) > LimitD) {
      ans = false;
      break;
    }
  }

  if (ans) {
    cout << "YES" << endl;
  } else {
    cout << "NO" << endl;
  }
}
