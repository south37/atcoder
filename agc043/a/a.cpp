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

int dr[2] = { 1, 0 };
int dc[2] = { 0, 1 };

int revDr[2] = { -1, 0 };
int revDc[2] = { 0, -1 };

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

  set<P> multiq; // multiple queue. in which, they are side of black.

  // At first, try reach from (0,0) to (h-1, w-1);
  {
    vector<vector<bool>> visited(h, vector<bool>(w));
    queue<P> q;
    q.emplace(0, 0);
    visited[0][0] = true;
    while (!q.empty()) {
      auto p = q.front(); q.pop();
      int r = p.first;
      int c = p.second;
      if (r == h-1 && c == w-1) { // reached to last.
        cout << 0 << endl;
        return 0;
      }
      bool isSideOfBlack = false;
      rep(i, 2) {
        int nextR = r + dr[i];
        int nextC = c + dc[i];
        if (nextR >= h || nextC >= w) { continue; } // reached to wall
        if (visited[nextR][nextC]) { continue; } // visited
        visited[nextR][nextC] = true;

        if (maze[nextR][nextC] == '#') { // reached to black.
          isSideOfBlack = true;
        } else {
          q.emplace(nextR, nextC);
        }
      }
      if (isSideOfBlack) {
        multiq.emplace(r, c);
      }
    }
  }

  // Here, we checked reachabelity from (0, 0).
  // we want to find the reachable locations from (w, h). Then check the min distance.

  set<P> targets;
  {
    vector<vector<bool>> visited(h, vector<bool>(w));
    queue<P> q;
    q.emplace(w-1, h-1);
    visited[w-1][h-1] = true;
    while (!q.empty()) {
      auto p = q.front(); q.pop();
      int r = p.first;
      int c = p.second;
      if (r == h-1 && c == w-1) { // reached to last.
        cout << 0 << endl;
        return 0;
      }
      bool isSideOfBlack = false;
      rep(i, 2) {
        int nextR = r + revDr[i];
        int nextC = c + revDc[i];
        if (nextR < 0 || nextR >= h || nextC < 0 || nextC >= w) { continue; } // reached to wall
        if (visited[nextR][nextC]) { continue; } // visited
        visited[nextR][nextC] = true;

        if (maze[nextR][nextC] == '#') { // reached to black.
          isSideOfBlack = true;
        } else {
          q.emplace(nextR, nextC);
        }
      }
      if (isSideOfBlack) {
        targets.insert({ r, c });
      }
    }
  }

  // Here, we want the min distance from "multiq" to "targets".
  {
    queue<pair<P, ll>> q;

    vector<vector<bool>> visited(h, vector<bool>(w));
    for (auto p : multiq) {
      visited[p.first][p.second] = true;
      q.emplace(p, 0);
    }
    while (!q.empty()) {
      auto p = q.front(); q.pop();
      auto pos = p.first;
      ll dist = p.second;
      int r = pos.first;
      int c = pos.second;
      if (targets.find(pos) != targets.end()) { // found
        cout << dist << endl;
        return 0;
      }
      rep(i, 2) {
        int nextR = r + dr[i];
        int nextC = c + dc[i];
        if (nextR < 0 || nextR >= h || nextC < 0 || nextC >= w) { continue; } // reached to wall
        if (visited[nextR][nextC]) { continue; } // visited
        visited[nextR][nextC] = true;

        q.emplace(P(nextR, nextC), dist + 1);
      }
    }
  }

  // must not reach here.
}
