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

const ll INF = 1e8;
const ll MOD = 1000000007;  // 1e9 + 7


int main(int argc, char** argv) {
  int N, M, L;
  cin >> N >> M >> L;
  // d[u][v] .. The cost between u .. v.
  vector< vector<int> > d(N, vector<int>(N, INF));

  rep(i, M) {
    int a, b, c;
    cin >> a >> b >> c;
    --a; --b;
    // cout << i << endl;
    // cout << a << ", " << b << endl;
    if (c <= L) {
      d[a][b] = c;
      d[b][a] = c;
    } else {
      d[a][b] = INF;
      d[b][a] = INF;
    }
  }

  // Warshal-Floyd
  rep(k, N) {
    rep(i, N) {
      rep(j, N) {
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
      }
    }
  }
  // For Debug
  // rep(i, N) {
  //   rep(j, N) {
  //     cout << "d["<<i<<"]["<<j<<"]: " << d[i][j] << endl;
  //   }
  // }

  // d2[u][v] .. The hopping cost between u .. v.
  // init: d2[u][v] = 1 if d[u][v] <= L.
  vector< vector<int> > d2(N, vector<int>(N, INF));
  rep(i, N) {
    rep(j, N) {
      if (d[i][j] <= L) {
        d2[i][j] = 1;
      }
    }
  }
  // Warshal-Floyd
  rep(k, N) {
    rep(i, N) {
      rep(j, N) {
        d2[i][j] = min(d2[i][j], d2[i][k] + d2[k][j]);
      }
    }
  }

  int Q;
  cin >> Q;
  rep(i, Q) {
    int s, t;
    cin >> s >> t;
    --s; -- t;
    if (d2[s][t] == INF) {
      cout << -1 << endl;
    } else {
      cout << d2[s][t] - 1 << endl;
    }
  }
}
