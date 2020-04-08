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

int dr[4] = { 1, -1, 0, 0 };
int dc[4] = { 0, 0, 1, -1 };

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll h, w, k;
  cin >> h >> w >> k;
  vector<string> mat(h);
  rep(r, h) {
    cin >> mat[r];
  }
  pair<ll, ll> s;
  rep(r, h) {
    rep(c, w) {
      if (mat[r][c] == 'S') {
        s.first = r;
        s.second = c;
      }
    }
  }

  // Here, we check all places from start by BFS
  ll ans = INF;
  queue<pair<P, ll>> q; // pair of <position, cnt>
  vector<vector<bool>> visited(h, vector<bool>(w));

  q.push(pair<P, ll>(s, 0));
  while (!q.empty()) {
    auto p = q.front(); q.pop();
    pair<ll, ll> pos = p.first;
    ll cnt = p.second;
    if (cnt > k) { continue; } // cnt is too large
    // Here, cnt <= k. It is valid.
    ll r = pos.first;  // row
    ll c = pos.second; // col
    if (r == 0 || r == h-1 || c == 0 || c == w-1) { // reached to edge
      cout << 1 << endl;
      return 0;
    }
    // Here, 0 < r < h-1, 0 < c < w-1

    chmin(ans, 1+(r      +(k-1))/k); // top    .. round up of (r) / k
    chmin(ans, 1+((h-1-r)+(k-1))/k); // bottom .. round up of (h-1-r) / k
    chmin(ans, 1+(c      +(k-1))/k); // left   .. round up of (c) / k
    chmin(ans, 1+((w-1-c)+(k-1))/k); // right  .. round up of (w-1-c) / k
    rep(i, 4) {
      int nextR = r + dr[i];
      int nextC = c + dc[i];
      // Here, we don't need to check the range of (nextR, nextC)
      if (mat[nextR][nextC] == '#') { continue; } // skip wall
      if (visited[nextR][nextC]) { continue; }
      visited[nextR][nextC] = true;

      // Here, nextR, nextC is valid and not visited.
      pair<ll, ll> nextPos(nextR, nextC);
      q.push(pair<P, ll>(nextPos, cnt + 1));
    }
  }

  cout << ans << endl;
}
