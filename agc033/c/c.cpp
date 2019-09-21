#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string.h>

using namespace std;

#define COUT(x) cout << #x << " = " << (x) << " (L" << __LINE__ << ")" << endl

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

int dx[] = { 1, -1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

int gcd(int a, int b) {
  if (a < b) { swap(a, b); }
  if (b == 0) { return a; }
  return gcd(b, a % b);
}

bool prime(int n) {
  for (int i = 2; i <= sqrt(n); ++i) {
    if (n % i == 0) { return false; }
  }
  return n != 1;
}

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

vector< vector<int> > tree;
vector<int> dst;  // distance
int r = 0;

void dfs(int now, int p) {
  for (auto x : tree[now]) {
    if (x == p) { continue; }
    dst[x] = dst[now] + 1;
    if (dst[x] > dst[r]) { r = x; }
    dfs(x, now);
  }
}

int main(int argc, char** argv) {
  int N;
  cin >> N;
  if (N == 1) { // If N is 1, first wins.
    cout << "First" << endl;
    return 0;
  }
  tree.resize(N);
  dst.resize(N);

  rep(i, N-1) {
    int a, b;
    cin >> a >> b;
    --a; --b;
    tree[a].push_back(b);
    tree[b].push_back(a);
  }

  // Double-Sweep for calculating the diameter of a tree.
  // cf. https://www.slideshare.net/chokudai/arc022 C
  dfs(0, -1);  // At first, start dfs from a random position.
  dst[r] = 0;
  dfs(r, -1);  // Next, start dfs from the farthest position.
  int diameter = dst[r];

  if (diameter % 3 == 1) {
    cout << "Second" << endl;
  } else {
    cout << "First" << endl;
  }
}
