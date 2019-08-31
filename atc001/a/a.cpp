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

#define MAX_W 500
#define MAX_H 500

int H, W;
char c[MAX_W][MAX_H];  // c[x][y] is the char at (x, y)
bool visited[MAX_W][MAX_H];

void dfs(int x, int y) {
  if (x < 0 || W <= x || y < 0 || H <= y || c[x][y] == '#') { return; }
  if (visited[x][y]) return;

  visited[x][y] = true;

  dfs(x + 1, y);
  dfs(x - 1, y);
  dfs(x, y + 1);
  dfs(x, y - 1);
}

int main(int argc, char** argv) {
  cin >> H >> W;

  rep(i, H) {
    string s;
    cin >> s;
    rep(j, W) {
      c[j][i] = s[j];
    }
  }

  int x, y;
  int g_x, g_y;
  rep(i, W) {
    rep(j, H) {
      if (c[i][j] == 's') {
        x = i;
        y = j;
      }
      if (c[i][j] == 'g') {
        g_x = i;
        g_y = j;
      }
    }
  }

  // cout << "s: " << x << ", " << y << endl;
  // cout << "g: " << g_x << ", " << g_y << endl;

  dfs(x, y);
  if (visited[g_x][g_y]) {
    cout << "Yes" << endl;
  } else {
    cout << "No" << endl;
  }
}
