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

// d[u][v] .. The cost between u .. v.
vector< vector<int> > d;

int nex[305][305];

int main(int argc, char** argv) {
  int N, M, L;
  cin >> N >> M >> L;
  d.assign(N, vector<int>(N, INF));
  // For Debug
  // rep(i, N) {
  //   rep(j, N) {
  //     cout << d[i][j] << " ";
  //   }
  //   cout << endl;
  // }

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

  int Q;
  cin >> Q;
  vector<P> queries;
  rep(i, Q) {
    int s, t;
    cin >> s >> t;
    --s; -- t;
    queries.emplace_back(s, t);
  }

  // initialization of nex
  rep(i, N) {
    rep(j, N) {
      nex[i][j] = j;
    }
  }

  // warshal-floyd
  rep(k, N) {
    rep(i, N) {
      rep(j, N) {
        if (d[i][k] + d[k][j] < d[i][j]) {
          d[i][j] = d[i][k] + d[k][j];
          nex[i][j] = nex[i][k];
        }
      }
    }
  }

  // For Debug
  // rep(i, N) {
  //   rep(j, N) {
  //     cout << "dp["<<i<<"]["<<j<<"]: " << d[i][j] << endl;
  //   }
  // }

  rep(i, Q) {
    int s = queries[i].first;
    int t = queries[i].second;
    int dist = d[s][t];
    if (dist == INF) {
      cout << -1 << endl;
    } else {
      // Here, we can reach from s to t.
      // Clculate the count in the greedy way.
      int ans = 0;
      int e = L; // energy

      int cur;
      for (cur = s; cur != t; cur = nex[cur][t]) {
        int n = nex[cur][t];
        if (e >= d[cur][n]) {
          e -= d[cur][n];
        } else {
          e = L - d[cur][n];
          ++ans;
        }
      }
      cout << ans << endl;
    }
  }
}
