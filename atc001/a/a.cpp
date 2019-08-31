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
int g_x, g_y;

bool dfs(int x, int y) {
  if ((x + 1 == g_x) && (y == g_y)) {
    return true;
  }
  if ((x - 1 == g_x) && (y == g_y)) {
    return true;
  }
  if ((x == g_x) && (y + 1 == g_y)) {
    return true;
  }
  if ((x == g_x) && (y - 1 == g_y)) {
    return true;
  }

  if ((x < W-1) && (c[y][x+1] == '.') && !visited[y][x+1]) {
    visited[y][x+1] = true;
    if (dfs(x+1, y)) { return true; }
  }
  if ((x > 0) && (c[y][x-1] == '.') && !visited[y][x-1]) {
    visited[y][x-1] = true;
    if (dfs(x-1, y)) { return true; }
  }
  if ((y < H-1) && (c[y+1][x] == '.') && !visited[y+1][x]) {
    visited[y+1][x] = true;
    if (dfs(x, y+1)) { return true; }
  }
  if ((y > 0) && (c[y-1][x] == '.') && !visited[y-1][x]) {
    visited[y-1][x] = true;
    if (dfs(x, y-1)) { return true; }
  }
  return false;
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

  visited[y][x] = true;
  bool r = dfs(x, y);
  if (r) {
    cout << "Yes" << endl;
  } else {
    cout << "No" << endl;
  }
}
