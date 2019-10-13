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

ll powmod(ll x, ll n) { // like pow(x, n)
  ll r = 1;
  while (n) {
    if (n & 1) {
      r = r * x % MOD;
    }
    x = x * x % MOD;
    n >>= 1;
  }
  return r;
}

int main(int argc, char** argv) {
  int H, W;
  cin >> H >> W;
  vector<string> S(H);
  rep(i, H) {
    cin >> S[i];
  }
  // First, we want to calculate the all distance in width and heights
  vector< vector<int> > w_blocks(H);
  vector< vector<int> > h_blocks(W);
  rep(i, H) {
    w_blocks[i].push_back(-1);
    rep(j, W) {
      if (S[i][j] == '#') {
        w_blocks[i].push_back(j);
      }
    }
    w_blocks[i].push_back(W);
  }
  rep(j, W) {
    h_blocks[j].push_back(-1);
    rep(i, H) {
      if (S[i][j] == '#') {
        h_blocks[j].push_back(i);
      }
    }
    h_blocks[j].push_back(H);
  }

  // For Debug
  // cout << "w_blocks" << endl;
  // rep(i, H) {
  //   cout << i << ": ";
  //   for (auto e : w_blocks[i]) {
  //     cout << e << ", ";
  //   }
  //   cout << endl;
  // }
  // cout << "h_blocks" << endl;
  // rep(i, W) {
  //   cout << i << ": ";
  //   for (auto e : h_blocks[i]) {
  //     cout << e << ", ";
  //   }
  //   cout << endl;
  // }

  // Now, each w_block and h_block is sorted.
  int ans = 0;
  rep(i, H) {
    rep(j, W) {
      if (S[i][j] == '#') { continue; }

      int w, h;
      {
        auto w_i = upper_bound(all(w_blocks[i]), j);
        int r = *w_i;
        --w_i;
        int l = *w_i;
        w = r - l - 1;
      }
      {
        auto h_i = upper_bound(all(h_blocks[j]), i);
        int r = *h_i;
        --h_i;
        int l = *h_i;
        h = r - l - 1;
      }

      ans = max(ans, h + w - 1);
    }
  }

  cout << ans << endl;
}
