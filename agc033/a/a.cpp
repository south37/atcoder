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

int dw[] = { 1, -1, 0, 0 };
int dh[] = { 0, 0, 1, -1 };

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

int main(int argc, char** argv) {
  int H, W;
  cin >> H >> W;
  vector<string> A(H);
  rep(i, H) {
    cin >> A[i];
  }

  // For Debug
  // rep(i, H) {
  //   cout << A[i] << endl;
  // }
  queue<triple> q;
  rep(h, H) {
    rep(w, W) {
      if (A[h][w] == '#') {
        q.emplace(h, w, 0);
      }
    }
  }

  int ans = 0;
  while (q.size() > 0) {
    int h, w, d;
    tie(h, w, d) = q.front(); q.pop();
    rep(i, 4) {
      int nh = h + dh[i];
      int nw = w + dw[i];

      if (nh < 0 || nh > H-1 || nw < 0 || nw > W-1) { continue; }
      if (A[nh][nw] == '#') { continue; }

      A[nh][nw] = '#';
      q.emplace(nh, nw, d + 1);
      ans = max(ans, d + 1);
    }
  }

  cout << ans << endl;
}
