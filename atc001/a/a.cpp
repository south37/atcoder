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

// Try [1, 0], [-1, 0], [0, 1], [0, -1]

int H, W;
vector<string> c;
vector< vector<bool> > visited;

void dfs(int x, int y) {
  if (x < 0 || W <= x || y < 0 || H <= y || c[y][x] == '#') { return; }
  if (visited[y][x]) return;

  visited[y][x] = true;

  dfs(x + 1, y);
  dfs(x - 1, y);
  dfs(x, y + 1);
  dfs(x, y - 1);
}

int main(int argc, char** argv) {
  cin >> H >> W;

  // For Debug
  // cout << H << endl;;
  // cout << W << endl;

  rep(i, H) {
    string s;
    cin >> s;
    c.push_back(s);
  }

  rep(i, H) {
    vector<bool> v(W, false);
    visited.push_back(v);
  }

  // For Debug
  // rep(i, H) {
  //   cout << c[i] << endl;
  // }

  int x, y;
  int g_x, g_y;
  rep(i, H) {
    rep(j, W) {
      if (c[i][j] == 's') {
        x = j;
        y = i;
      }
      if (c[i][j] == 'g') {
        g_x = j;
        g_y = i;
      }
    }
  }

  // cout << "s: " << x << ", " << y << endl;
  // cout << "g: " << g_x << ", " << g_y << endl;

  dfs(x, y);
  if (visited[g_y][g_x]) {
    cout << "Yes" << endl;
  } else {
    cout << "No" << endl;
  }
}
