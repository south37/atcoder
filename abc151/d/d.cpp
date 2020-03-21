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

template<class T> void printvec(const vector<T>& v) {
  for (auto x : v) { cout << x << " "; }
  cout << endl;
}
template<class T> void printtree(const vector< vector<T> >& tree) {
  for (long long i = 0; i < tree.size(); ++i) {
    cout << i + 1 << ": "; printvec(tree[i]);
  }
}
template<class T, class U> void printmap(const map<T, U>& mp) {
  for (auto x : mp) { cout << x.first << "=>" << x.second << endl; }
}

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }

#define rep(i, n) for(ll i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()
#define fr first
#define sc second
#define mp make_pair
#define pb push_back

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

// int main(int argc, char** argv) {
//   ll N, M;
//   cin >> N >> M;
//
//   // d[u][v] .. The cost between u .. v.
//   vector< vector<ll> > d(N, vector<ll>(N, INF));
//
//   // initialization
//   rep(i, M) {
//     int a, b, c;
//     cin >> a >> b >> c;
//     --a; --b; // 0-indexed
//     d[a][b] = c;
//     d[b][a] = c;
//   }
//
//   // WarshalFloyd
//   rep(k, N) {
//     rep(i, N) {
//       rep(j, N) {
//         d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
//       }
//     }
//   }
//
//   cout << "d[0][1]: " << d[0][1] << endl;
//   cout << "d[0][2]: " << d[0][2] << endl;
// }

int dr[4] = { 1, -1, 0, 0 };
int dc[4] = { 0, 0, 1, -1 };

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll h, w;
  cin >> h >> w;
  vector<string> maze(h);
  rep(r, h) {
    cin >> maze[r];
  }

  // d[u][v] .. The cost between u .. v.
  // (r,c) == r*w + c.
  vector< vector<ll> > d(h*w, vector<ll>(h*w, INF));

  // initialization
  rep(r, h) {
    rep(c, w) {
      if (maze[r][c] == '#') { continue; } // skip wall
      rep(i, 4) {
        int nextR = r + dr[i];
        int nextC = c + dc[i];
        if (nextR < 0 || nextR >= h || nextC < 0 || nextC >= w) { continue; }
        if (maze[nextR][nextC] == '#') { continue; }
        // Here, (r,c) and (nextR, nextC) is connected
        d[r*w+c][nextR*w+nextC] = 1;
        d[nextR*w+nextC][r*w+c] = 1;
      }
    }
  }
  // printvec(d[0]);
  // printvec(d[1]);

  // WarshalFloyd
  rep(k, h*w) {
    rep(i, h*w) {
      rep(j, h*w) {
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
      }
    }
  }
  // printvec(d[0]);
  // printvec(d[1]);

  ll ans = 0;
  rep(i, h*w) {
    rep(j, h*w) {
      if (i == j) { continue; } // same location
      if (d[i][j] != INF) {
        ans = max(ans, d[i][j]);
      }
    }
  }

  cout << ans << endl;
}
