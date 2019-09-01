#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <cassert>

using namespace std;

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

int dx[] = { 1, -1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };

typedef pair<int, int> P;
typedef tuple<int, int, int> triple;

int main(int argc, char** argv) {
  int R, C;
  cin >> R >> C;
  int sy, sx, gy, gx;
  cin >> sy >> sx;
  cin >> gy >> gx;
  --sy; --sx; --gy; --gx;

  vector<string> Map(R);
  rep(i, R) {
    cin >> Map[i];
  }

  // For Debug
  // rep(i, R) {
  //   cout << Map[i] << endl;
  // }

  vector< vector<int> > D(R);
  rep(i, R) {
    vector<int> l(C, -1);
    D[i] = l;
  }

  queue<triple> q;
  q.push(triple(sx, sy, 0));
  while (q.size() > 0) {
    triple v = q.front(); q.pop();
    int x, y, dist;
    tie(x, y, dist) = v;
    if (D[y][x] != -1) { // Already visited
      continue;
    }
    D[y][x] = dist;

    rep(i, 4) {
      int nx = x + dx[i];
      int ny = y + dy[i];

      if ((nx < 0) || (nx > C - 1) || (ny < 0) || (ny > R - 1)) {
        continue;
      }
      if (D[ny][nx] != -1) {
        continue;
      }
      if (Map[ny][nx] != '.') {
        continue;
      }

      // For Debug
      // cout << "ny, nx, dist + 1: " << ny << ", " << nx << ", " << dist + 1 << endl;

      q.push(triple(nx, ny, dist + 1));
    }
  }

  cout << D[gy][gx] << endl;
}
